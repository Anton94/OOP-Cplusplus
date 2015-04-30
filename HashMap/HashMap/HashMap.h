/**
*
*
* It will be better to use some kind of log complexity data structure for the buckets, but for this homework the task is more for the hash map, not to implement log complexity data structure.
*
* HashMap implementation in C++
* @author:
* @keywords: Data Structures, Map, Hashing
* @modified: Anton Dudov #71488
*
* Implement an unordered map with STL string keys.
* Use load factor ((number of elements + 1) / number of buckets) of at least 0.25.
*
* (optional): Make it also work for integers (int) as keys.
* (optional): Make it also work for arbitrary objects as keys.
*
*
*
*   Github repository for the Chipher message 2 task: https://github.com/Anton94/OOP-Cplusplus/tree/master/Cipher%20Message%202
*   Github repository for the HashMap homework:		  https://github.com/Anton94/OOP-Cplusplus/tree/master/HashMap
*
*
*   The definition of the static variables for the Hash struct is in the Soruce.cpp file :(
*
*
*/

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <string>
#include <exception>
#include <vector>

using std::vector;
using std::pair;
using std::string;


class myException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Hash map went wrong...";
	}
} myEx; // Very basic exeption, just to pass some message


struct Hash
{
	static int BASE1;
	static int BASE2;
	static int BASE3;

	static int MOD1;
	static int MOD2;
	static int MOD3;

	int len;
	int h1, h2, h3;

	Hash() 
	{
		len = 0;
		h1 = h2 = h3 = 1;
	}

	Hash(const string& str) 
	{
		len = 0;
		h1 = h2 = h3 = 1;

		stringHash(str);
	}

	bool operator == (const Hash& r) const
	{
		return len == r.len && h1 == r.h1 && h2 == r.h2 && h3 == r.h3;
	}

	void stringHash(const string& str)
	{
		int strSize = (int)str.size();

		for (int i = 0; i < strSize; i++) 
		{
			h1 = ((long long)h1 * BASE1 + str[i]) % MOD1;
			h2 = ((long long)h2 * BASE2 + str[i]) % MOD2;
			h3 = ((long long)h3 * BASE3 + str[i]) % MOD3;
		}
	}

};

template <typename V>
class HashMap {
public:
	/**
	* Constructs an empty HashMap with minimum minBuckets buckets and
	* maxium maxBuckets buckets. These lower and upper bounds on the
	* number of buckets should be maintained at all times!
	* Expected complexity: O(minBuckets)
	*/
	HashMap(int minBuckets = 1, int maxBuckets = 1000000000) 
	{
		if (minBuckets < 1 || maxBuckets < minBuckets)
			throw myEx; // throw std::exeption("msg??");

		this->minBuckets = minBuckets;
		this->maxBuckets = maxBuckets;

		capacityValue = minBuckets;
		sizeValue = 0;
		
		// Make the hash table with capacity value empty buckets.
		hashMap = new vector<vector<pair<Hash, V>>>(capacityValue);
	}

	/**
	* Destroys all values in the HashMap and the HashMap itself.
	* Expected complexity: O(N + B), where B is the number of buckets.
	*/
	~HashMap() 
	{
		delete hashMap;
	}

	/**
	* Creates a new HashMap using the values of already existing instance.
	* Expected complexity: O(N' + B'), where N' and B' are the number of
	* elements and the number of buckets, respectively, in the existing
	* instance.
	* Note: optional
	*/
	HashMap(const HashMap<V>& other)
	{
		copyFrom(other);
	}

	/**
	* Destroys all current values and assigns new ones using the values
	* of another existing instance.
	* Expected complexity: O(N + N' + B + B'), where N' and B' are the
	* number of elements and the number of buckets, respectively, in the
	* existing instance.
	* Note: optional
	*/
	HashMap<V>& operator = (const HashMap<V>& other)
	{
		if (this != &other)
		{
			delete hashMap;
			copyFrom(other);
		}

		return *this;
	}

	/**
	* Resizes the HashMap so it has at least numBuckets slots (buckets).
	* Re-hashes the current values if needed.
	* Expected time complexity: O(N + numBuckets)
	*/
	//void resize(int numBuckets) {

	//	// Check fo valid value, if it`s less than 1, makes it 1...
	//	if (numBuckets < 1)
	//		numBuckets = 1;

	//	// Make the lower and upper bounds the given number of the size.
	//	this->minBuckets = this->maxBuckets = numBuckets;
	//
	//	reizeWithoutBounds(numBuckets);
	//}

	/**
	* Removes all existing values from the HashMap and leaves it empty.
	* Expected complexity: O(N + B)
	*/
	void clear()
	{
		// Make the size of the vectors 0, that way I will remove all stored keys.
		// I can remove only the values for the keys, but I don`t know if that what the function had to make.
		for (int i = 0; i < capacityValue; ++i)
		{
			(*hashMap)[i].resize(0);
		}

		sizeValue = 0;
	}

	/**
	* Returns the number of elements in the HashMap.
	* Expected complexity: O(1)
	*/
	int size() const {
		return sizeValue;
	}

	/**
	* Returns the number of allocated buckets in the HashMap.
	* Expected complexity: O(1)
	*/
	int capacity() const {
		return capacityValue;
	}

	/**
	* Checks if a value is already associated with a certain key.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	bool contains(const std::string& key) const 
	{
		Hash hash(key);

		int indexVectorSize = hash.h1 % capacityValue;

		for (int i = 0; i < (*hashMap)[indexVectorSize].size(); ++i)
		{
			if ((*hashMap)[indexVectorSize][i].first == hash)
				return true;
		}

		return false;
	}

	/**
	* Inserts a new (key, value) pair or replaces the current value with
	* another one, if the key is already present.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	void insert(const std::string& key, const V& value) 
	{
		Hash hash(key);

		int indexVectorSize = hash.h1 % capacityValue;

		for (int i = 0; i < (*hashMap)[indexVectorSize].size(); ++i)
		{
			if ((*hashMap)[indexVectorSize][i].first == hash)
			{
				(*hashMap)[indexVectorSize][i].second = value;
				return;
			}
		}

		++sizeValue;

		(*hashMap)[indexVectorSize].push_back(pair<Hash, V>(hash, value));

		// If the elements are more than 75% , makes the table 1.5 bigger and they will be 50% of the table.
		if ((double)(sizeValue + 1) >= (0.75) * (double)capacityValue)
		{
			reizeWithoutBounds((double)capacityValue * 1.5);
		}
	}

	/**
	* Removes a key and the associated with it value from the HashMap.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	void erase(const std::string& key)
	{
		Hash hash(key);

		int indexVectorSize = hash.h1 % capacityValue;

		for (int i = 0; i < (*hashMap)[indexVectorSize].size(); ++i)
		{
			if ((*hashMap)[indexVectorSize][i].first == hash)
			{
				(*hashMap)[indexVectorSize].erase((*hashMap)[indexVectorSize].begin() + i);
				--sizeValue;

				// If the load factor is broken, make the the hash table smaller. (if the elements are below 25%, makes the table half and they will be ~50%)
				if ((sizeValue + 1) * 4 < capacityValue)
				{
					reizeWithoutBounds(capacityValue / 2);
				}

				return;
			}
		}
	}

	/**
	* Returns a reference to the value, associated with a certain key.
	* If the key is not present in the HashMap, throw an error or fail
	* by assertion.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	V& get(const std::string& key)
	{
		return getValueByString(key);
	}

	/**
	* Same as get().
	*/
	V& operator[] (const std::string& key) 
	{
		return getValueByString(key);
	}
private:
	/**
	* Resize the hash map but don`t change the min and max buckets bounds.
	*/
	void reizeWithoutBounds(int numBuckets)
	{
		// Check if the numBuckets has valid value. If not-make it valid one.
		if (numBuckets > maxBuckets)
			numBuckets = maxBuckets;
		if (numBuckets < minBuckets)
			numBuckets = minBuckets;

		// Check if the hash map has same size as the new needed size and if so - returns
		if (numBuckets == capacityValue)
			return;

		vector<vector<pair<Hash, V>>> * temp = new vector<vector<pair<Hash, V>>>(numBuckets);

		for (int i = 0; i < capacityValue; ++i)
		{
			for (int j = 0; j < (*hashMap)[i].size(); ++j)
			{
				(*temp)[(*hashMap)[i][j].first.h1 % numBuckets].push_back((*hashMap)[i][j]);
			}
		}

		capacityValue = numBuckets;

		delete hashMap;

		hashMap = temp;
	}

	/**
	* Returns a reference to the value, associated with a certain key.
	* If the key is not present in the HashMap, throw an error or fail
	* by assertion.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	V& getValueByString(const std::string& key)
	{
		Hash hash(key);

		int indexVectorSize = hash.h1 % capacityValue; // The bucket index.

		for (int i = 0; i < (*hashMap)[indexVectorSize].size(); ++i)
		{
			if ((*hashMap)[indexVectorSize][i].first == hash)
			{
				return (*hashMap)[indexVectorSize][i].second;
			}
		}

		throw myEx; // throw std::exeption("msg??");
	}

	/*
	* Assigns new hash map using the values of another existing instance. NOTE: does not deletes the existing one hash map!
	*/
	void copyFrom(const HashMap<V>& other)
	{
		minBuckets = other.minBuckets;
		maxBuckets = other.maxBuckets;
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;

		hashMap = new vector<vector<pair<Hash, V>>>(other.capacityValue);

		for (int i = 0; i < other.capacityValue; ++i)
		{
			(*hashMap)[i] = (*other.hashMap)[i]; // Copy the bucket vectors(I can copy the vector of vectors even, but..)
		}
	}
private:
	int minBuckets;
	int maxBuckets;
	int sizeValue;
	int capacityValue;
	vector<vector<pair<Hash, V>>> * hashMap;
};

#endif // #ifndef __HASHMAP_H__
