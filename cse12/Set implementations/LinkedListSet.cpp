#include "Set.h"

/**
 * Implement the LinkedListSet methods correctly
 */
unsigned int LinkedListSet::size() {
    return linked.size();
}

void LinkedListSet::insert(string s) {
    if (!find(s)) {
        linked.push_back(s);
    }
}

void LinkedListSet::remove(const string & s) {
    for (auto it = linked.begin(); it != linked.end(); ++it) {
        if (*it == s) {
            linked.erase(it);
            break;
        }
    }
}

bool LinkedListSet::find(const string & s) {
    for (string str: linked) {
        if (str == s) {
            return true;
        }
    }
    return false;
}
