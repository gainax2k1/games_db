#include "hash.h"




unsigned int hash(const char *str, unsigned int size) {
    unsigned long hash = 5381; // Start with a prime number for classic "djb2 algorithm"
    int c;
    
    // Iterate through each character in the string
    while ((c = *str++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }
    
    // Ensure the hash is within bounds of our table size
    return hash % size;
}