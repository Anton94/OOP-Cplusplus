

/**
* Functionality tester for HashMap class.
*/

// <!-- insert HashMap implementation or include here -->

#include <map>
#include <algorithm>
#include <cassert>
#include "HashMap.h"
using namespace std;

/**
* These methods provides basic testing of the expected functionality.
* It is by all means not complete and does not stress-test the implementation
* for efficiency. It just checks if every part of the expected interface is
* implemented and includes some simple sanity check.
*/


int Hash::BASE1 = 257;
int Hash::BASE2 = 263;
int Hash::BASE3 = 271;

int Hash::MOD1 = 1000000007;
int Hash::MOD2 = 1000000021;
int Hash::MOD3 = 1000000181;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789"
" `~!@#$%^&*()-_=+{}[]|\\'\",.<>/?:;";

string randomString() {
	string str;
	int len = 3 + rand() % 8;
	for (int c = 0; c < len; c++)
		str += alphabet[rand() % alphabet.size()];
	return str;
}

void testInitialCapacity(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testInitialCapacity()\n");

	assert(hmap.size() == 0);
	assert(tmap.size() == 0u);
	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testInsert(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testInsert()\n");

	hmap.insert("espr1t", 42);
	tmap.insert(make_pair("espr1t", 42));

	assert(hmap.size() == 1);
	assert(tmap.size() == 1);
	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testContainsAndGet(HashMap<int>& hmap, map<string, int>& tmap) {
	fprintf(stderr, "In testContainsAndGet()\n");

	assert(hmap.contains("espr1t"));
	assert(tmap.find("espr1t") != tmap.end());

	assert(hmap.get("espr1t") == 42);
	assert(hmap["espr1t"] == 42);

	assert(!hmap.contains("ThinkCreative"));
	assert(tmap.find("ThinkCreative") == tmap.end());
}

void testMoreOperations(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testMoreOperations()\n");

	hmap.insert("exod40", 13);
	tmap.insert(make_pair("exod40", 13));
	assert(hmap.size() == 2);
	assert(tmap.size() == 2u);

	hmap.insert("espr1t", 666);
	tmap.insert(make_pair("espr1t", 666));
	assert(hmap.size() == 2);
	assert(tmap.size() == 2u);

	assert(hmap["espr1t"] == 666);
	assert(hmap.get("espr1t") == 666);
	assert(hmap["exod40"] == 13);
	assert(hmap.get("exod40") == 13);

	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testClear(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testClear()\n");

	hmap.clear();
	tmap.clear();
	assert(hmap.size() == 0);
	assert(tmap.size() == 0u);

	assert(!hmap.contains("espr1t"));
	assert(!hmap.contains("exod40"));

	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testAddingAfterClear(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testAddingAfterClear()\n");

	vector < pair <string, int> > rating = {
		make_pair("Petr", 3792),
		make_pair("tourist", 3758),
		make_pair("Egor", 3427),
		make_pair("peter50216", 3346),
		make_pair("bmerry", 3332),
		make_pair("ACRush", 3298),
		make_pair("wata", 3279),
		make_pair("tomek", 3204),
		make_pair("WJMZBMR", 3189),
		make_pair("lyrically", 3151)
	};

	for (int i = 0; i < (int)rating.size(); i++) {
		hmap.insert(rating[i].first, rating[i].second);
		tmap[rating[i].first] = rating[i].second;
	}

	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testChangingAValue(HashMap<int> hmap, map<string, int>& tmap) {
	fprintf(stderr, "In testChangingAValue()\n");

	assert(hmap.size() == (int)tmap.size());
	assert(hmap.get("tomek") == 3204);
	hmap.get("tomek") = 1337;
	assert(hmap.get("tomek") == 1337);
	hmap["tomek"] = 3204;
}

void testErase(HashMap<int>& hmap, map<string, int>& tmap) {
	fprintf(stderr, "In testErase()\n");

	hmap.erase("peter50216");
	tmap.erase(tmap.find("peter50216"));

	assert(hmap.size() == (int)tmap.size());
	hmap.erase("not existing");
	assert(hmap.size() == (int)tmap.size());

	hmap.erase("ACRush");
	tmap.erase(tmap.find("ACRush"));
	assert(hmap.size() == 8);
}

void testOverwrite(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testOverwrite()\n");

	vector < pair <string, int> > rating = {
		make_pair("Petr", 3792),
		make_pair("tourist", 3758),
		make_pair("Egor", 3427),
		make_pair("peter50216", 3346),
		make_pair("bmerry", 3332),
		make_pair("ACRush", 3298),
		make_pair("wata", 3279),
		make_pair("tomek", 3204),
		make_pair("WJMZBMR", 3189),
		make_pair("lyrically", 3151)
	};

	// Overwrite to see if the load factor remains okay
	for (int i = 0; i < (int)rating.size(); i++) {
		hmap.insert(rating[i].first, rating[i].second);
		tmap[rating[i].first] = rating[i].second;
	}

	assert(hmap.size() == 10);
	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));

	hmap.insert("espr1t", 42);
	tmap["espr1t"] = 42;
	hmap.insert("exod40", 1337);
	tmap["exod40"] = 1337;
	assert(hmap.size() == 12);
	assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
}

void testAccessingInvalidKey(HashMap<int>& hmap, map<string, int>& tmap) {
	fprintf(stderr, "In testAccessingInvalidKey()\n");

	assert(tmap.find("non existing") == tmap.end());

	bool errorThrown = false;
	try {
		hmap["non existing"] = 42;
	}
	catch (exception e) {
		errorThrown = true;
	}
	assert(errorThrown);
}

void testAutomaticResizing(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testAutomaticResizing()\n");

	// Test automatic resizing
	for (int i = 0; i < 10000; i++) {
		string str = randomString();
		int value = rand() % 1000000007;
		hmap.insert(str, value);
		tmap[str] = value;
		assert(hmap.size() == (int)tmap.size());
		assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
	}

	// Check maps consistency
	assert(hmap.size() == (int)tmap.size());
	for (map <string, int> ::iterator it = tmap.begin(); it != tmap.end(); it++) {
		if (it->second != hmap[it->first])
			fprintf(stderr, "  -- for string %s: %d vs %d\n",
			it->first.c_str(), it->second, hmap[it->first]);
		assert(it->second == hmap[it->first]);
	}
}

void testMaintainingLoadFactor(HashMap<int>& hmap, map<string, int>& tmap, int minCap, int maxCap) {
	fprintf(stderr, "In testMaintainingLoadFactor()\n");

	while (hmap.size() > 0) {
		string str = randomString();
		if (rand() % 10 == 0) {
			hmap.erase(str);
			if (tmap.find(str) != tmap.end())
				tmap.erase(str);
		}
		else {
			map <string, int> ::iterator it = tmap.lower_bound(str);
			if (it == tmap.end())
				it--;
			hmap.erase(it->first);
			tmap.erase(it);
		}
		assert(hmap.capacity() <= min(max((hmap.size() + 1) * 4, minCap), maxCap));
	}
}

void funcTest(HashMap<int>& hmap, map<string, int>& tmap,
	int minCapacity = 0, int maxCapacity = 1000000000) {
	fprintf(stderr, "Starting functional test with capacity range [%d, %d].\n",
		minCapacity, maxCapacity);

	srand(42);
	testInitialCapacity(hmap, tmap, minCapacity, maxCapacity);
	testInsert(hmap, tmap, minCapacity, maxCapacity);
	testContainsAndGet(hmap, tmap);
	testMoreOperations(hmap, tmap, minCapacity, maxCapacity);
	testClear(hmap, tmap, minCapacity, maxCapacity);
	testAddingAfterClear(hmap, tmap, minCapacity, maxCapacity);
	testChangingAValue(hmap, tmap);
	testErase(hmap, tmap);
	testOverwrite(hmap, tmap, minCapacity, maxCapacity);
	testAccessingInvalidKey(hmap, tmap);
	testAutomaticResizing(hmap, tmap, minCapacity, maxCapacity);
	testMaintainingLoadFactor(hmap, tmap, minCapacity, maxCapacity);
}


void simpleTest() {
	// Default constructor
	HashMap<int> hmap1;
	map <string, int> tmap1;
	funcTest(hmap1, tmap1);

	// Constructor with fixed lower number of buckets
	HashMap<int> hmap2(1337);
	map <string, int> tmap2;
	funcTest(hmap2, tmap2, 1337);

	// Constructor with fixed lower and upper number of buckets
	HashMap<int> hmap3(1337, 42000);
	map <string, int> tmap3;
	funcTest(hmap3, tmap3, 1337, 42000);
}

int main(void) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		simpleTest();
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		fprintf(stderr, "Memory leak detected!\n");
		_CrtMemDumpStatistics(&s3);
	}
	else
	{
		fprintf(stderr, "Everything with the memory is OK!\n");
	}

	return 0;
}