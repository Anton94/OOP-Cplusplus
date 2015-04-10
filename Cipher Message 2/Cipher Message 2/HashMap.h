#pragma once

#include <vector>

using std::vector;
using std::pair;

const int MAX = 8017;

const int BASE1 = 127;
const int BASE2 = 131;
const int BASE3 = 137;

const int MOD1 = 199999;
const int MOD2 = 7633579;
const int MOD3 = 7299251;

int basePower[3][MAX];


struct Hash {
	int len;
	int h1, h2, h3;

	Hash() {
		len = 0;
		h1 = h2 = h3 = 0;
	}
	bool operator == (const Hash& r) const {
		return len == r.len && h1 == r.h1 && h2 == r.h2 && h3 == r.h3;
	}

	void append(char ch) {
		len++;
		h1 = (h1 * BASE1 + ch) % MOD1;
		h2 = (h2 * BASE2 + ch) % MOD2;
		h3 = (h3 * BASE3 + ch) % MOD3;
	}

	void removeFront(char ch) {
		h1 -= (basePower[0][len - 1] * ch) % MOD1; if (h1 < 0) h1 += MOD1;
		h2 -= (basePower[1][len - 1] * ch) % MOD2; if (h2 < 0) h2 += MOD2;
		h3 -= (basePower[2][len - 1] * ch) % MOD3; if (h3 < 0) h3 += MOD3;
		len--;
	}
};

template <class T>
class HashMap
{
public:
	HashMap()
	{
		hashMap.resize(MOD1); // MOD1 because I will store the data by first hash code...
	}


	bool contains(const Hash& hash)
	{
		for (typename vector<pair<Hash, T>>::iterator it = hashMap[hash.h1].begin(); it != hashMap[hash.h1].end(); ++it)
		{
			if (hash == it->first)
				return true;
		}

		/*for (int i = 0; i < hashMap[hash.h1].size(); ++i)
		{
		if (hash == hashMap[hash.h1][i].first)
		return true;
		}*/

		return false;
	}


	T& get(const Hash& hash)
	{
		for (typename vector<pair<Hash, T>>::iterator it = hashMap[hash.h1].begin(); it != hashMap[hash.h1].end(); ++it)
		{
			if (hash == it->first)
				return it->second;
		}

		/*for (int i = 0; i < hashMap[hash.h1].size(); ++i)
		{
		if (hash == hashMap[hash.h1][i].first)
		return hashMap[hash.h1][i].second;
		}
		*/
		throw "No element to get!";
	}

	void insert(const Hash& hash, const T& value)
	{
		hashMap[hash.h1].push_back(pair<Hash, T>(hash, value));
	}

	void remove(const Hash& hash)
	{
		for (typename vector<pair<Hash, T>>::iterator it = hashMap[hash.h1].begin(); it != hashMap[hash.h1].end(); ++it)
		{
			if (hash == it->first)
			{
				hashMap[hash.h1].erase(it);
				return;
			}
		}
	}
private:

private:
	vector<vector<pair<Hash, T>>> hashMap; // Hash code(s) and the value.
};