#include "BinaryTree.h"

/**
 * Implement balanceFactors() correctly
 */
 int calcHeight(BinaryTree::Node* node) {
    if (node == nullptr) {
        return 0;
    }
    
    int rightHeight = calcHeight(node->rightChild);
    int leftHeight = calcHeight(node->leftChild);

    if (rightHeight > leftHeight) {
        return 1 + rightHeight;
    } else {
        return 1 + leftHeight;
    }
}

int calcBF(BinaryTree::Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = calcHeight(node->leftChild);
    int rightHeight = calcHeight(node->rightChild);

    return rightHeight - leftHeight;
}

void in_order_insert(BinaryTree::Node* node, unordered_map<int,int>& map) {
    if (node == nullptr) {
        return;
    }

    in_order_insert(node->leftChild, map);
    map.insert({node->label, calcBF(node)});
    in_order_insert(node->rightChild, map);
}


unordered_map<int,int> BinaryTree::balanceFactors() {
    unordered_map<int, int> result;
    in_order_insert(this->root, result);
    return result;
}
