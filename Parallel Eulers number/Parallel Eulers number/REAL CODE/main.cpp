#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <string>
#include <gmp.h>

using namespace std::chrono;
using std::vector;
using std::thread;
using std::string;

struct calculateBlock
{
	/// Calculates the multiplications and save it in the second variable
	/// @hashTable[i+1] *= @hashTable[i]
	/// range [ @startIndex, @endIndex ) calculation
	void operator()(size_t startIndex, size_t endIndex)
	{
		for (size_t next = startIndex + 1; next < endIndex; startIndex += 2, next += 2)
		{
			//hashTable[next] = hashTable[startIndex] * hashTable[next];
			mpf_mul(hashTable[next], hashTable[startIndex], hashTable[next]);
		}
	}

	static mpf_t * hashTable;
};

mpf_t * calculateBlock::hashTable = NULL;

struct generateBlock
{
	void operator()(size_t startIndex, size_t endIndex)
	{
		for (; startIndex < endIndex; ++startIndex)
		{
			//hashTable[startIndex] = startIndex;
			mpf_init_set_ui(hashTable[startIndex], startIndex);
		}
	}

	static mpf_t * hashTable; // hashTable + 1 
};

mpf_t * generateBlock::hashTable = NULL;

struct divideBlock
{
	void operator()(size_t startIndex, size_t endIndex, size_t j)
	{
		for (; startIndex < endIndex; startIndex += 2)
		{
		//	results[j] += startIndex / (double)hashTable[startIndex]; // NOTE: I will modify the hash table!
			mpf_ui_div(hashTable[startIndex], startIndex, hashTable[startIndex]);
			mpf_add(results[j], results[j], hashTable[startIndex]);
		}
	}

	static mpf_t * hashTable;
	static mpf_t * results;
};

mpf_t * divideBlock::hashTable = NULL;
mpf_t * divideBlock::results = NULL;

class EulersConstant
{
public:
	/// Generates a hash table with the factorials till N (per 2) with offset of 2 elements ( starts with 1 1 1 2 6 24 120 720 ...)
	/// Why offset? to get the elements with index + 2 (index 3 contains 1!, index 3 contains 2!, index 5 contains 4!, index 7 contains 6!) without calculation
	EulersConstant(size_t n, size_t numberOfThreads)
	{
		//std::cout << mpf_get_default_prec() << std::endl;
		// Offset of 2 elements.
		capacity = n + 2;
		threads = numberOfThreads;
		mpf_set_default_prec(capacity*2);

		hashTable = new mpf_t[capacity]; // basically it calls the constructor for every element...
		results = new mpf_t[threads];

		for (unsigned long int i = 0; i < threads; ++i)
		{
			//results[i] = 0.0;
			mpf_init_set_ui(results[i], 0);
		}

		generateBlock::hashTable = hashTable + 1; // START FROM NEXT CELL.
		calculateBlock::hashTable = hashTable;
		divideBlock::hashTable = hashTable;
		divideBlock::results = results;
	}

	/// Generates the basic numbers.
	void generateTheStartingNumbers(size_t numberOfThreads)
	{
		//hashTable[0] = hashTable[1] = hashTable[2] = 1;

		mpf_init_set_ui(hashTable[0], 1);
		mpf_init_set_ui(hashTable[1], 1);
		mpf_init_set_ui(hashTable[2], 1);

		// In that case the threads will be more than the calculations...
		if (capacity < numberOfThreads && capacity >= 2)
			numberOfThreads = capacity - 2;

		// Launch one fewer thread than @numberOfThreads, because we already have one.
		size_t numberOfThreadsLessOne = numberOfThreads - 1;
		vector<thread> threads(numberOfThreadsLessOne);

		// Calculate the block size. Number of elements / number of threads but the result must be even.
		size_t blockSize = (capacity / numberOfThreads);

		// Launching the threads with a loop.
		size_t i = 2;

		for (size_t j = 0; j < numberOfThreadsLessOne; ++j)
		{
			// launch a new thread to accumulate the results for the block
			threads[j] = thread(generateBlock(), i, i + blockSize); // NOTE: std::ref for real references.
			i += blockSize;
		}

		// After the launch of all the threads,
		// this thread can then process the final block (the final block may be bigger from the other onces (bad :( )
		generateBlock()(i, capacity - 1);

		// Now we wait all threads to finish their job
		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
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
		vector<thread> threads(numberOfThreadsLessOne);

		// Calculate the block size. Number of elements / number of threads but the result must be even.
		size_t blockSize = (capacity / numberOfThreads);
		if ((blockSize & 1) != 0) // If it`s not even.
			++blockSize; // TO DO If the threads are more than the elements or twice to check, but fuck this shit...

		// Launching the threads with a loop.
		size_t i = 2;

		for (size_t j = 0; j < numberOfThreadsLessOne; ++j)
		{
			// launch a new thread to accumulate the results for the block
			threads[j] = thread(calculateBlock(), i, i + blockSize); // NOTE: std::ref for real references.
			i += blockSize;
		}

		// After the launch of all the threads,
		// this thread can then process the final block (the final block may be bigger from the other onces (bad :( )
		calculateBlock()(i, capacity);

		// Now we wait all threads to finish their job
		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

		for (size_t i = 5; i < capacity; i += 2)
		{
			//hashTable[i] *= hashTable[i - 2];
			mpf_mul(hashTable[i], hashTable[i], hashTable[i-2]);
		}
	}

	/// Divides x / x! where x = (2k) + 1 and x! = 2k!, iterates it by moving the counter with 2.
	void divide(size_t numberOfThreads)
	{
		// Launch one fewer thread than @numberOfThreads, because we already have one.
		size_t numberOfThreadsLessOne = numberOfThreads - 1;
		vector<thread> threads(numberOfThreadsLessOne);

		// Calculate the block size. Number of elements / number of threads but the result must be even.
		size_t blockSize = (capacity / numberOfThreads);
		if ((blockSize & 1) != 0) // If it`s not even.
			++blockSize; // TO DO If the threads are more than the elements or twice to check, but fuck this shit...

		// Launching the threads with a loop.
		size_t i = 1;

		for (size_t j = 0; j < numberOfThreadsLessOne; ++j)
		{
			// launch a new thread to accumulate the results for the block
			threads[j] = thread(divideBlock(), i, i + blockSize, j); // I pass the j value for faster arguments... (std::ref(resutls[j])
			i += blockSize;
		}

		// After the launch of all the threads,
		// this thread can then process the final block (the final block may be bigger from the other onces (bad :( )

		divideBlock()(i, capacity, numberOfThreadsLessOne);

		// Now we wait all threads to finish their job
		std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
		
		for (size_t i = 1; i < numberOfThreads; ++i) // Write all results in first box.
		{
			//results[0] += results[i];
			mpf_add(results[0], results[0], results[i]);
		}
	}

	~EulersConstant()
	{
		//        /// Maybe not needed.
		//        for (size_t i = 0; i < capacity; ++i)
		//        {
		//            mpf_clear(hashTable[i]);
		//        }

		delete[] hashTable;
		delete[] results;
	}

	void printFirstK(size_t k, FILE * out) const
	{
		if (k > capacity)
			k = capacity;

		for (size_t i = 1; i < k; i += 2)
		{
			std::cout << i - 1 << " factoriel is: ";
			mpf_out_str(out, 10, 30, hashTable[i]);
            std::cout << std::endl;
		}
	}

	void printE(FILE * out) const
	{
		mpf_out_str(out, 10, capacity / 2, results[0]);
        std::cout << std::endl;
	}
private:
	mpf_t * hashTable;
	mpf_t * nextPointer;
	mpf_t * results;
	size_t capacity;
	size_t threads;
};

struct Execute
{
	size_t k;
	size_t numberOfThreads;
	string outputFileName;
	bool quiet;
	// Sets the default values.
	Execute()
	{
		setDefaultValues();
	}

	void calculate() const
	{
		std::cout << "Test with " << 2 * k << " elements and " << numberOfThreads << " thread(s)\n";
		EulersConstant eulersConstant(2 * k, numberOfThreads);

		auto begin = high_resolution_clock::now();

		eulersConstant.generateTheStartingNumbers(numberOfThreads);
		eulersConstant.calculate(numberOfThreads);
		eulersConstant.divide(numberOfThreads);

		auto end = high_resolution_clock::now();

		auto ticks = duration_cast<microseconds>(end - begin);

		std::cout << "It took me " << ticks.count() << " microseconds. \n";

		if (!quiet)
		{
			FILE * pFile;
		   	pFile = fopen (outputFileName.c_str() , "w");

			eulersConstant.printE(pFile);
		}
	}

	// NOTE: does not make check for validation, I trust myself!
	void parseTheInputArguments(int argc, char**argv)
	{
		// Very stupid way to check for arguments.
		for (size_t i = 1; i < argc; ++i)
		{
			if (std::strlen(argv[i]) <= 1) // Fucked up input argument.
				return;

			switch (argv[i][1]) // First one is '-' 
			{
				case 'p': 
				{
					k = (size_t) atoi(argv[i + 1]);
					++i;
					break;
				}
				case 'q':
				{
					quiet = true;
					break;
				}
				case 't':
				{
					numberOfThreads = (size_t) atoi(argv[i + 1]);
					++i;
					break;
				}
				case 'o':
				{
					outputFileName = argv[i + 1]; // cast to string..
					++i;
					break;
				}
				default:
					return;
			}
		}
	}
private:
	void setDefaultValues()
	{
		k = 10000;
		numberOfThreads = 1;
		outputFileName = "output.txt";
		quiet = false;
	}
};

int main(int argc, char**argv)
{
	Execute execute;

	execute.parseTheInputArguments(argc, argv);
	execute.calculate();

	return 0;
}
