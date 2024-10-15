#include <limits.h>
#include "CountMinSketch.h"
#include "HashFunctions.h"

/**
 * Implement increment() correctly
 */
void CountMinSketch::increment(const string & s) {
    for (unsigned int i = 0; i < K; i++) {
        unsigned int hashVal = hash_functions[i](s) % M;
        count[i][hashVal] ++ ;
    }
}

/**
 * Implement find() correctly
 */
unsigned int CountMinSketch::find(const string & s) {
    unsigned int min = INT_MAX;
    for (unsigned int i = 0; i < K; i++) {
        unsigned int hashVal = hash_functions[i](s) % M;
        if (count[i][hashVal] < min) {
            min = count[i][hashVal];
        }
    }
    return min;
}
