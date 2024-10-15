#include "BST.h"
#include <vector>

BST::BST() { 
    /* YOUR CODE HERE */
    // Initialize a null root
    root = nullptr;
    numElements = 0;
}

BST::~BST() {
    /* YOUR CODE HERE */
    clear();
}

void postOrderRemoval(BST::Node* node) {
    if (node == nullptr) {
        return;
    }
    //run a post-order traversal with the given node
    postOrderRemoval(node->leftChild);
    postOrderRemoval(node->rightChild);
    delete node;
}

unsigned int BST::size() const {
    /* YOUR CODE HERE */
    return numElements;
}

void BST::clear() {
    postOrderRemoval(root);
    root = nullptr;
    numElements = 0;
}

bool BST::insert(int element) {
    /* YOUR CODE HERE */
    if (root == nullptr) {
        root = new Node(element);
        numElements ++;
        return true;
    }
    Node* curr = root;
    while (curr != nullptr) {
        //Check for duplicates
        if (curr->data == element) {
            return false;
        }
        //Traverse through the tree to find the position of insertion
        if (element < curr->data) {
            if (curr->leftChild != nullptr) {
                curr = curr->leftChild;
            } else {
                curr->leftChild = new Node(element);
                curr->leftChild->parent = curr;
                numElements++;
                return true;
            }
        } else {
            if (curr->rightChild != nullptr) {
                curr = curr->rightChild;
            } else {
                curr->rightChild = new Node(element);
                curr->rightChild->parent = curr;
                numElements++;
                return true;
            }
        }
    }
    return false;
}

bool BST::find(const int & query) const {
    /* YOUR CODE HERE */
    Node* curr = root;
    if (curr == nullptr) {
        return false;
    }
    while (curr != nullptr) {
        if (curr->data == query) {
            return true;
        } else {
            if (query < curr->data) {
                curr = curr->leftChild;
            } else {
                curr = curr->rightChild;
            }
        }
    }
    return false;
}

BST::Node* BST::getLeftMostNode() {
    /* YOUR CODE HERE */
    Node* curr = root;
    if (curr == nullptr) {
        return curr;
    }
    while (curr->leftChild != nullptr) {
        curr = curr->leftChild;
    }
    return curr;
}

BST::Node* BST::Node::successor() {
    /* YOUR CODE HERE */
    /*
        if the node has right child, the successor would be the 
        leftmost node of the right child.
    */
    if (this->rightChild != nullptr) {
        Node* curr = this->rightChild;
        while (curr->leftChild != nullptr) {
            curr=curr->leftChild;
        }
        return curr;
        
    } 
    /*
        if the node has no right child
    */
    else {
        Node* parent = this->parent;
        Node* curr = this;
        /*
            While curr node is greater than its parent node
        */
        while (parent != nullptr && curr == parent->rightChild) {
            curr = parent;
            parent = parent->parent;
        }
        /*
            Up until the parent node is greater
            than the curr node, return parent
        */
        return parent;
    }
}
