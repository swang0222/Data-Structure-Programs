#include "Set.h"

/**
 * Implement the MultiwayTrieSet constructor
 */
MultiwayTrieSet::MultiwayTrieSet() {
    root = new Node();
    numElements = 0;
}

void removeChildren(MultiwayTrieSet::Node* node) {
    for (auto child: node->children) {
        removeChildren(child.second);
    }
    delete node;
}

/**
 * Implement the MultiwayTrieSet destructor
 */
MultiwayTrieSet::~MultiwayTrieSet() {
    removeChildren(root);
}

/**
 * Implement the MultiwayTrieSet methods correctly
 */
unsigned int MultiwayTrieSet::size() {
    return numElements;
}

void MultiwayTrieSet::insert(string s) {
    Node* curr = root;
    for (char ch : s) {
        if (!curr->children.count(ch)) {
            curr->children[ch] = new Node();
        }
        curr = curr->children[ch];
    }
    if (!curr->isWord) {
        curr->isWord = true;
        numElements ++;
    }
}

void MultiwayTrieSet::remove(const string & s) {
    if (find(s)) {
        Node* curr = root;
        for (char ch : s) {
            curr = curr->children[ch];
        }
        curr->isWord = false;
        numElements --;
    }
}

bool MultiwayTrieSet::find(const string & s) {
    Node* curr = root;
    for (char ch : s) {
        if (curr->children.count(ch) == 0) {
            return false;
        }
        curr = curr->children[ch];
    }
    return curr->isWord;
}
