#ifndef FACTORIALS_H_INCLUDED
#define FACTORIALS_H_INCLUDED

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;
using std::vector;

struct calculateBlock
{
    /// Calculates the multiplications and save it in the second variable
    /// @hashTable[i+1] *= @hashTable[i]
    /// range [ @startIndex, @endIndex ) calculation
	void operator()(size_t startIndex, size_t endIndex, mpf_t * hashTable)
	{
		for (size_t next = startIndex + 1; startIndex < endIndex; startIndex += 2, next += 2)
        {
            mpf_mul(hashTable[next], hashTable[startIndex], hashTable[next]);
        }
	}
};


class Factorials
{
public:
    /// Generates a hash table with the factorials till N (per 2) with offset of 2 elements ( starts with 1 1 1 2 6 24 120 720 ...)
    /// Why offset? to get the elements with index + 2 (index 3 contains 1!, index 3 contains 2!, index 5 contains 4!, index 7 contains 6!) without calculation
    Factorials(size_t n)
    {
        // Offset of 2 elements.
        capacity = n + 2;
        hashTable = new mpf_t[capacity]; // basically it calls the constructor for every element...

        // Initialize the values for now not parallel
        mpf_init_set_ui(hashTable[0], 1);
        mpf_init_set_ui(hashTable[1], 1);

        // Make unsigned long int variables, so does not need to make cast...
        unsigned long int cap = capacity;
        for (unsigned long int i = 2; i < cap; ++i)
        {
            mpf_init_set_ui(hashTable[i], i);
        }
    }

    /// Does not make any checks for the index validation!
    mpf_t& operator[](int index)
    {
        return hashTable[index];
    }

    /// Calculates the factorials with the given amount of threads.
    void calculate(size_t numberOfThreads)
    {
        // In that case the threads will be more than the calculations...
        if (capacity < numberOfThreads && capacity >= 2)
            numberOfThreads = capacity - 2;

        // Launch one fewer thread than @numberOfThreads, because we already have one.
        size_t numberOfThreadsLessOne = numberOfThreads - 1;
        vector<std::thread> threads(numberOfThreadsLessOne);

        // Calculate the block size. Number of elements / number of threads but the result must be even.
        size_t blockSize = (capacity / numberOfThreads);
        if ((blocksSize & 1) != 0) // If it`s not even.
            --blocksSize; // TO DO checking...

        // Launching the threads with a loop.
        size_t i = 0;
        size_t lastBlockUpperBound = number

        for(size_t j = 0 ; i < numberOfThreadsLessOne; ++j)
        {
            // launch a new thread to accumulate the results for the block
            threads[j] = thread(calculateBlock(), i, i += blockSize, hashTable); // NOTE: std::ref for real references.
        }

        // After the launch of all the threads,
        // this thread can then process the final block (the final block may be bigger from the other onces (bad :( )
        calculateBlock()(i, capacity, hashTable);
    }

    ~Factorials()
    {
//        /// Maybe not needed.
//        for (size_t i = 0; i < capacity; ++i)
//        {
//            mpf_clear(hashTable[i]);
//        }

        delete [] hashTable;
    }
private:
    mpf_t * hashTable;
    size_t capacity;
};

#endif // FACTORIALS_H_INCLUDED
