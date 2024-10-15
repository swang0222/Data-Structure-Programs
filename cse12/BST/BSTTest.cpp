/*
 * Name: Niema Moshiri (modified by Qingyang for Spring 2022)
 * Email: niema@ucsd.edu
 *
 * Sources Used: None.
 *
 */


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_set>
#include "BST.h"
using namespace std;

/**
 * Define messages for use in the tester
 */
const string MESSAGE_SUCCESS = "Success";
const string MESSAGE_WRONG_SIZE = "Incorrect size";
const string MESSAGE_FALSE_NEGATIVE = "BST find returned false when element "
    "actually existed";
const string MESSAGE_FALSE_POSITIVE = "BST find returned true when element "
    "didn't actually exist";
const string MESSAGE_WRONG_INSERT_RETURN = "BST insert returned the wrong "
    "boolean";
const int TEST_SIZE = 100;
const int DATA_RANGE = 10000;
const int DATA_OFFSET = 5000;

/**
 * Test BST class using numbers from standard input
 */
int main() {
    // randomly sample a bunch of integers
    srand(time(NULL));
    unordered_set<int> nums;
    while(nums.size() < TEST_SIZE) {
        nums.insert((rand() % DATA_RANGE) - DATA_OFFSET);
    }

    // create BST and check initial size
    BST bst;
    if(bst.size() != 0) {
        cout << MESSAGE_WRONG_SIZE << endl;
        return 1;
    }
    bst.clear();
    if(bst.size() != 0) {
        cout << MESSAGE_WRONG_SIZE << endl;
        return 1;
    }

    // do basic tests
    if(bst.find(*(nums.begin()))) {
        cout << MESSAGE_FALSE_POSITIVE << endl;
        return 1;
    }
    if(!(bst.insert(*(nums.begin()))) || bst.insert(*(nums.begin()))) {
        cout << MESSAGE_WRONG_INSERT_RETURN << endl;
        return 1;
    }
    bst.clear();
    

    // populate BST
    unsigned int count = 0;
    for(int num : nums) {
        if(!bst.insert(num)) {
            cout << MESSAGE_WRONG_INSERT_RETURN << endl;
            return 1;
        }
        if(bst.insert(num)) {
            cout << MESSAGE_WRONG_INSERT_RETURN << endl;
            return 1;
        }
        if(bst.size() != ++count) {
            cout << MESSAGE_WRONG_SIZE << endl;
            return 1;
        }
    }

    // clear and repopulate BST
    bst.clear();
    count = 0;
    for(int num : nums) {
        bst.insert(num);
        if(bst.size() != ++count) {
            cout << MESSAGE_WRONG_SIZE << endl;
            return 1;
        }
    }

    // check if numbers exist
    for(int num : nums) {
        if(!bst.find(num)) {
            cout << MESSAGE_FALSE_NEGATIVE << endl;
            return 1;
        }
    }

    // check numbers that shouldn't exist
    for(int i = 0; i < TEST_SIZE; ++i) {
        int num = (rand() % DATA_RANGE) - DATA_OFFSET;
        while(nums.find(num) != nums.end()) {
            num = (rand() % DATA_RANGE) - DATA_OFFSET;
        }
        if(bst.find(num)) {
            cout << MESSAGE_FALSE_POSITIVE << endl;
            return 1;
        }
    }

    // if it didn't fail yet, success!
    cout << MESSAGE_SUCCESS << endl;
    return 0;
}
