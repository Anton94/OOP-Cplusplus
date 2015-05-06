/**
* Interval Tree implementation in C++
* @author:
* @keywords: Data Structures, Dynamic RMQ, Interaval update and query
* @modified: 71488 Anton Dudov
*
* Implement a dynamic RMQ with interval query and update. The update should
* add a certain value to all cells in a given interval, while the query should
* return the maximum value inside an interval.
*
*
*
*
*
*
*
*           I use numeric_limits for the minimum value , I don`t know if thats a good practice...
*/

#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


template <typename T> 
class IntervalTree 
{
public:

	/**
	* Creates a new interval tree with initial values given in values.
	* Each update and query should allow indices [0, values.size() - 1].
	*/
	IntervalTree(const vector<T>& values) 
	{
		infinity = std::numeric_limits<T>::min();
		size = nearestToThePowerOfTwo((int)values.size());
		allocateTheMemoryForTheArrays(size);

		generateTheArrays(values);
		createQueryTree(1); // From the root

		for (int i = 1; i < size * 2; ++i)
		{
			std::cout << queryTree[i] << " ";
		}

		std::cout << std::endl;

		for (int i = 1; i < size * 2; ++i)
		{
			std::cout << updateTree[i] << " ";
		}

		std::cout << std::endl;
	}

	/**
	* Adds the value add to each element in the interval [idx1, idx2].
	*/
	void update(int idx1, int idx2, T add) {
		idx1 += this->size;
		idx2 += this->size;

		/*if (idx1 == idx2)
		{
			updateTree[idx1] += add;
			return;
		}

		updateTree[idx1] += add;
		updateTree[idx2] += add;
		bool flag1 = !(idx1 & 1);
		idx1 /= 2;
		bool flag2 = (idx2 & 1);
		idx2 /= 2;

		while (idx1 != idx2)
		{
			if (flag1)
				updateTree[(idx1 * 2) + 1] += add;
			if (flag2)
				updateTree[(idx2 * 2)] += add;

			flag1 = !(idx1 & 1);
			idx1 /= 2;
			flag2 = (idx2 & 1);
			idx2 /= 2;
		}*/


		if (idx1 == idx2)
		{
			updateTree[idx1] += add;
			return;
		}

		updateTree[idx1] += add;
		updateTree[idx2] += add;
		bool flag1 = !(idx1 & 1);
		idx1 /= 2;
		bool flag2 = (idx2 & 1);
		idx2 /= 2;

		while (idx1 != idx2)
		{
			if (flag1)
				updateTree[(idx1 * 2) + 1] += add;
			if (flag2)
				updateTree[(idx2 * 2)] += add;

			flag1 = !(idx1 & 1);
			idx1 /= 2;
			flag2 = (idx2 & 1);
			idx2 /= 2;
		}
		

		for (int i = 1; i < size * 2; ++i)
		{
			std::cout << queryTree[i] << " ";
		}

		std::cout << std::endl;
	}

	/**
	* Returns the maximum value in the interval [idx1, idx2].
	*/
	T query(int idx1, int idx2) 
	{
		idx1 += this->size;
		idx2 += this->size;
		
		if (idx1 == idx2)
			//return queryTree[idx1] + updateTree[idx1];
			return queryTree[idx1];

		//T result = max(queryTree[idx1] + updateTree[idx1], queryTree[idx2] + updateTree[idx2]);
		T result = max(queryTree[idx1], queryTree[idx2]);
		bool flag1 = !(idx1 & 1);
		idx1 /= 2;
		bool flag2 = (idx2 & 1);
		idx2 /= 2;

		while (idx1 != idx2)
		{
			if (flag1)
				result = max(result, queryTree[(idx1 * 2) + 1]);
			if (flag2)
				result = max(result, queryTree[(idx2 * 2)]);

		/*	if (flag1)
				result = max(result, queryTree[(idx1 * 2) + 1] + updateTree[(idx1 * 2) + 1]);
			if (flag2)
				result = max(result, queryTree[(idx2 * 2)] + updateTree[(idx2 * 2)]);*/

			flag1 = !(idx1 & 1);
			idx1 /= 2;
			flag2 = (idx2 & 1);
			idx2 /= 2;
		}

		return result;
	}

	/**
	* Deletes the allocated memory.
	*/
	~IntervalTree()
	{
		delete[] queryTree;
		delete[] updateTree;
	}
private:
	void allocateTheMemoryForTheArrays(int size)
	{
		size *= 2; // 2*N

		queryTree = NULL;
		updateTree = NULL;

		try
		{
			queryTree = new T[size];
			updateTree = new T[size];
		}
		catch (std::bad_alloc& ba) // If the first allocation fails I will deletes it`s memory...
		{
			delete[] queryTree;
			delete[] updateTree;
		}
	}

	/*
	* Initialize the leafs and calculates the maximum values for the query array(interval tree).
	*/
	void generateTheArrays(const vector<T>& values)
	{
		// All not-leaf nodes in update array has values 0.
		for (int i = 0; i < size; ++i)
		{
			updateTree[i] = 0;
		}

		// Make all leaf nodes in the bouth arrays.
		for (int i = 0, j = size; i < values.size(); ++i, j++)
		{
			queryTree[j] = values[i];
			updateTree[j] = values[i];
		}

		// Set the 'extra' space with factual values.
		for (int i = size + values.size(); i < 2 * size; ++i)
		{
			queryTree[i] = infinity;
			updateTree[i] = 0;
		}



		// TO DO check

		for (int i = 0; i < 2 * size; ++i)
			updateTree[i] = 0;
	}

	/**
	* Goes from the root to the leafs and calculates the maximum values.
	*/
	void createQueryTree(int cur)
	{
		int leftChild = cur * 2,
			rightChild = cur * 2 + 1;

		if (rightChild > this->size * 2)
			return; // if the nodes are leafs...

		createQueryTree(leftChild); // Init left subtree
		createQueryTree(rightChild); // Init right subtree

		queryTree[cur] = max(queryTree[leftChild], queryTree[rightChild]); // Init root value with the maximum of the child subtrees.
	}

	/**
	* Returns a number (power of two), which is nearest to the given one(@size).
	* TO DO with bitwise operations...
	*/
	int nearestToThePowerOfTwo(int size)
	{
		int power = 2;
		while (size > power)
		{
			power *= 2;
		}

		return power;
	}
private:
	T * queryTree;
	T * updateTree;
	T infinity;
	int size;
};

#endif // #ifndef __INTERVAL_TREE_H__