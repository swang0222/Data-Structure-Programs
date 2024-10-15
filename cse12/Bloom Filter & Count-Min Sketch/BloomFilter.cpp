#include "BloomFilter.h"
#include "HashFunctions.h"

/**
 * Implement insert() correctly
 */
void BloomFilter::insert(const string & s) {
    for (unsigned int i = 0; i < K; i++) {
        unsigned int hashVal = hash_functions[i](s) % M;
        bits[hashVal] = true;
    }
}

/**
 * Implement find() correctly
 */
bool BloomFilter::find(const string & s) {
    for (unsigned int i = 0; i < K; i++) {
        unsigned int hashVal = hash_functions[i](s) % M;
        if (!bits[hashVal]) {
            return false;
        }
    }
    return true;
}
