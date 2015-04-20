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


template <typename V> 
class HashMap {
public:
	/**
	* Constructs an empty HashMap with minimum minBuckets buckets and
	* maxium maxBuckets buckets. These lower and upper bounds on the
	* number of buckets should be maintained at all times!
	* Expected complexity: O(minBuckets)
	*/
	HashMap(int minBuckets = 1, int maxBuckets = 1000000000) {
		if (minBuckets < 1 || maxBuckets < minBuckets)
			throw myEx;

		this->minBuckets = minBuckets;
		this->maxBuckets = maxBuckets;
		
		setDefaultValues();
	}

	/**
	* Destroys all values in the HashMap and the HashMap itself.
	* Expected complexity: O(N + B), where B is the number of buckets.
	*/
	~HashMap() {
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
	void resize(int numBuckets) {

		// Check fo valid value, if it`s less than 1, makes it 1...
		if (numBuckets < 1)
			numBuckets = 1;

		// Make the lower and upper bounds the given number of the size.
		this->minBuckets = this->maxBuckets = numBuckets;
	
		reizeWithoutBounds(numBuckets);
	}

	/**
	* Removes all existing values from the HashMap and leaves it empty.
	* Expected complexity: O(N + B)
	*/
	void clear() {

		// Deletes all buckets (vectors) and the vector for the current hash map.
		delete hashMap;

		// Set the default values, and the new hash map will have min buckets size (because the hashmap is empty now, we need to make some kind of valid load factor(min buckets)).
		setDefaultValues();
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
	bool contains(const std::string& key) const {

		return find(stringHash(key), key);
	}

	/**
	* Inserts a new (key, value) pair or replaces the current value with
	* another one, if the key is already present.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	void insert(const std::string& key, const V& value) {

		int hashCode = stringHash(key);

		for (int i = 0; i < (*hashMap)[hashCode].size(); ++i)
		{
			if (!(*hashMap)[hashCode][i].first.compare(key))
			{
				(*hashMap)[hashCode][i].second = value;
				return;
			}
		}

		++sizeValue;

		(*hashMap)[hashCode].push_back(pair<string, V>(key, value));

		if ((sizeValue + 1) > capacityValue )
		{
			reizeWithoutBounds(capacityValue * 4);
		}
	}

	/**
	* Removes a key and the associated with it value from the HashMap.
	* Expected complexity: O(H + 1), where O(H) is needed to hash the key.
	*/
	void erase(const std::string& key) {

	int hashCode = stringHash(key);

	for (int i = 0; i < (*hashMap)[hashCode].size(); ++i)
	{
		if (!(*hashMap)[hashCode][i].first.compare(key))
		{
			(*hashMap)[hashCode].erase((*hashMap)[hashCode].begin() + i);
			--sizeValue;

			// If the load factor is broken, make the the hash table smaller.
			if ((sizeValue + 1) * 4 > capacityValue)
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
	V& get(const std::string& key) {

		return getValueByString(key);
	}

	/**
	* Same as get().
	*/
	V& operator[] (const std::string& key) {

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

		MOD = numBuckets;

		vector<vector<pair<string, V>>> * temp = new vector<vector<pair<string, V>>>(numBuckets);

		for (int i = 0; i < capacityValue; ++i)
		{
			for (int j = 0; j < (*hashMap)[i].size(); ++j)
			{
				int hashCode = stringHash((*hashMap)[i][j].first);

				(*temp)[hashCode].push_back(pair<string, V>((*hashMap)[i][j].first, (*hashMap)[i][j].second));
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
		int hashCode = stringHash(key);

		for (int i = 0; i < (*hashMap)[hashCode].size(); ++i)
		{
			if (!(*hashMap)[hashCode][i].first.compare(key))
			{
				return (*hashMap)[hashCode][i].second;
			}
		}

		throw myEx;
	}

	/**
	* Returns true if the given string is in the hash map.
	*/
	bool find(int hashCode, const string& str) const
	{
		if (hashCode < 0 || hashCode > capacityValue)
			return false;

		for (int i = 0; i < (*hashMap)[hashCode].size() ; ++i)
		{
			if (!(*hashMap)[hashCode][i].first.compare(str))
				return true;
		}

		return false;
	}

	/**
	* Makes hash code for the given string.
	*/
	int stringHash(const string& str) const
	{
		int ret = 1;
		int strSize = (int)str.size();

		for (int i = 0; i < strSize; i++) {
			ret = ((long long)ret * BASE + str[i]) % MOD;
		}

		return ret;
	}

	/*
	* Assigns new hash map using the values of another existing instance. NOTE: does not deletes the existing one hash map!
	*/
	void copyFrom(const HashMap<V>& other)
	{
		BASE = other.BASE;
		MOD = other.MODE;
		minBuckets = other->minBuckets;
		maxBuckets = other->maxBuckets;
		sizeValue = other.sizeValue;
		capacityValue = other.capacityValue;

		hashMap = new vector<vector<pair<string, V>>>(other.capacityValue);

		for (int i = 0; i < other.hashMap->size(); ++i)
		{
			(*hashMap)[i] = other.(*hashMap)[i]; // Copies the whole vector of the bucket on i-th row. I can use and the copy constructor of the vector of the buckets but...
		}
	}

	/**
	* Sets the default values for the variables.
	*/
	void setDefaultValues()
	{
		BASE = 257;

		capacityValue = MOD = minBuckets;
		sizeValue = 0;

		hashMap = new vector<vector<pair<string, V>>>(capacityValue);
		// Make all vectors with capacity 0. Maybe by default they are, but in any case... (maybe not all compilators will be the same)
		for (int i = 0; i < capacityValue; ++i)
			(*hashMap)[i].resize(0);
	}
private:
	int BASE;
	int MOD;
	int minBuckets;
	int maxBuckets;
	int sizeValue;
	int capacityValue; // the capacity == MOD but for now let`s stay.

	vector<vector<pair<string, V>>> * hashMap;
};

#endif // #ifndef __HASHMAP_H__
