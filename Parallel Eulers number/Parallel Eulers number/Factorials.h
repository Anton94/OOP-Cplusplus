#ifndef FACTORIALS_H_INCLUDED
#define FACTORIALS_H_INCLUDED

#include <gmp.h>
#include <gmpxx.h>

class Factorials
{
public:
    // Generates a hash table with the factoriels till N (per 2) with offset of 2 elements ( starts with 1 1 1 2 6 24 120 720 ...)
    // Why offset? to get the elements with index + 2 (index 3 contains 1!, index 3 conatins 2!, index 5 conatins 4!, index 7 contains 6!) without calculation
    Factorials(size_t n)
    {
        // Offset of 2 elements.
        capacity = n + 2;
        hashTable = new mpf_t[capacity]; // basically it calls the constructor for every element...
    }

    // Does not make any checks for the index validation!
    mpf_t& operator[](int index)
    {
        return hashTable[index];
    }

    ~Factorials()
    {
        for (size_t i = 0; i < capacity)
        {
            mpf_clear(hashTable[i]);
        }

        delete [] hashTable;
    }
private:
    mpf_t * hashTable;
    size_t capacity;
};

#endif // FACTORIALS_H_INCLUDED
