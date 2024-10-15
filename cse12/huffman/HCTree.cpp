#include "HCTree.hpp"
#include <stack>

void postOrderRemoval(HCNode* node) {
    if (node == nullptr) {
        return;
    }
    //run a post-order removal
    postOrderRemoval(node->c0);
    postOrderRemoval(node->c1);
    delete node;
}

HCTree::~HCTree() {
    postOrderRemoval(root);
}

void HCTree::build(const vector<int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    for (unsigned int i = 0; i < freqs.size(); i++) {
        if (freqs[i] > 0) {
            HCNode* newNode = new HCNode(freqs[i], (unsigned char)i);
            leaves[i] = newNode;
            pq.push(newNode);
            cout << newNode->symbol << endl;
        }
    }

    while(pq.size() > 1) {
        HCNode* left = pq.top();
        pq.pop();
        HCNode* right = pq.top();
        pq.pop();

        HCNode* parent = new HCNode(left->count + right->count, 0);
        parent->c0 = left;
        parent->c1 = right;
        left->p = parent;
        right->p = parent;

        pq.push(parent);
    }

    if (!pq.empty()) {
        root = pq.top();
    }
}

unsigned char HCTree::decode(FancyInputStream & in) const {
    HCNode* curr = root;

    while (curr->c0 != nullptr || curr->c1 != nullptr) {
        int bit = in.read_bit();
        if (bit == -1) {
            return 0;
        }
        if (bit == 0) {
            curr = curr->c0;
        } else {
            curr = curr->c1;
        }
    }
    return curr->symbol;
}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const {
    stack<int> path;

    HCNode* curr = leaves[symbol];

    while(curr != root) {
        if (curr == curr->p->c0) {
            path.push(0);
        } else {
            path.push(1);
        }
        curr = curr->p;
    }

    while (!path.empty()) {
        out.write_bit(path.top());
        path.pop();
    }
}
