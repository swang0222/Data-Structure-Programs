#include "Set.h"

/**
 * Implement the ArrayListSet methods correctly
 */
unsigned int ArrayListSet::size() {
    return arr.size();
}

void ArrayListSet::insert(string s) {
    if (!find(s)) {
        arr.push_back(s);
    }
}

void ArrayListSet::remove(const string & s) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        if (arr[i] == s) {
            arr.erase(arr.begin() + i);
        }
    }
}

bool ArrayListSet::find(const string & s) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        if (arr[i] == s) {
            return true;
        }
    }
    return false;
}
