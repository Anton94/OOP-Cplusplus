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

void testInitialCapacity(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "In testInitialCapacity()\n");

	assert(hmap.size() == 0);
	assert(tmap.size() == 0u);
	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
}

void testInsert(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "In testInsert()\n");

	hmap.insert("espr1t", 42);
	tmap.insert(make_pair("espr1t", 42));

	assert(hmap.size() == 1);
	assert(tmap.size() == 1);
	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
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

void testMoreOperations(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
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

	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
}

void testClear(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "In testClear()\n");

	hmap.clear();
	tmap.clear();
	assert(hmap.size() == 0);
	assert(tmap.size() == 0u);

	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));

	assert(!hmap.contains("espr1t"));
	assert(!hmap.contains("exod40"));
}

void testAddingAfterClear(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
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

	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
}

void testChangingAValue(HashMap<int>& hmap, map<string, int>& tmap) {
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

void testOverwrite(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
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
	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));

	hmap.insert("espr1t", 42);
	tmap["espr1t"] = 42;
	hmap.insert("exod40", 1337);
	tmap["exod40"] = 1337;
	assert(hmap.size() == 12);
	assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
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

void testAutomaticResizing(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "In testAutomaticResizing()\n");

	// Test automatic resizing
	for (int i = 0; i < 10000; i++) {
		string str = randomString();
		int value = rand() % 1000000007;
		hmap.insert(str, value);
		tmap[str] = value;
		assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
		assert(hmap.size() == (int)tmap.size());
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

void testManualResizing(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "In testManualResizing()\n");

	hmap.resize(hmap.capacity() * 5);
	// Check rehashed values
	for (map <string, int> ::iterator it = tmap.begin(); it != tmap.end(); it++) {
		if (it->second != hmap[it->first])
			fprintf(stderr, "  -- for string %s: %d vs %d\n",
			it->first.c_str(), it->second, hmap[it->first]);
		assert(it->second == hmap[it->first]);
	}

	minCapacity = hmap.capacity();
	// Add some more values
	for (int i = 0; i < 2000; i++) {
		string str = randomString();
		int value = rand() % 1000000007;
		hmap.insert(str, value);
		tmap[str] = value;
		assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
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

void testMaintainingLoadFactor(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
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
		assert(hmap.capacity() <= max((hmap.size() + 1) * 4, minCapacity));
	}
}

void funcTest(HashMap<int>& hmap, map<string, int>& tmap, int minCapacity) {
	fprintf(stderr, "Starting functional test with initial capacity %d.\n",
		minCapacity);

	srand(42);
	testInitialCapacity(hmap, tmap, minCapacity);
	testInsert(hmap, tmap, minCapacity);
	testContainsAndGet(hmap, tmap);
	testMoreOperations(hmap, tmap, minCapacity);
	testClear(hmap, tmap, minCapacity);
	testAddingAfterClear(hmap, tmap, minCapacity);
	testChangingAValue(hmap, tmap);
	testErase(hmap, tmap);
	testOverwrite(hmap, tmap, minCapacity);
	testAccessingInvalidKey(hmap, tmap);
	testAutomaticResizing(hmap, tmap, minCapacity);
	testMaintainingLoadFactor(hmap, tmap, minCapacity);
	testManualResizing(hmap, tmap, minCapacity);
}


void simpleTest() {
	// Default constructor
	HashMap<int> hmap1;
	map <string, int> tmap1;
	funcTest(hmap1, tmap1, 0);

	// Constructor with fixed number of buckets
	HashMap<int> hmap2(1337);
	map <string, int> tmap2;
	funcTest(hmap2, tmap2, 1337);
}

int main(void) {
	simpleTest();

	return 0;
}