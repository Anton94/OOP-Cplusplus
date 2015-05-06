#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "IntervalTree.h"

const int MAX_IDX = 100000;

const int NUM_QUERIES = 1000000;
const int QUERY = 0;
const int UPDATE = 1;

struct Query {
	int x1, x2;
	int val, type;
};

int n;
int init[MAX_IDX]; // Initial values
Query a[NUM_QUERIES]; // Save queries
int ans1[NUM_QUERIES], ans2[NUM_QUERIES]; // Save answers

void solveTrees() {
	IntervalTree <int> tree(vector<int>(init, init + MAX_IDX));
	for (int i = 0; i < n; i++) {
		if (a[i].type == QUERY)
			ans1[i] = tree.query(a[i].x1, a[i].x2);
		else {
			ans1[i] = -1;
			tree.update(a[i].x1, a[i].x2, a[i].val);
		}
	}
}

int dummy[MAX_IDX];
void dummyUpdate(int x1, int x2, int val) {
	for (int x = x1; x <= x2; x++)
		dummy[x] += val;
}

int dummyQuery(int x1, int x2) {
	int ret = -2100000000;
	for (int x = x1; x <= x2; x++)
		ret = max(ret, dummy[x]);
	return ret;
}

void solveDummy() {
	for (int i = 0; i < MAX_IDX; i++)
		dummy[i] = init[i];
	for (int i = 0; i < n; i++) {
		if (a[i].type == QUERY)
			ans2[i] = dummyQuery(a[i].x1, a[i].x2);
		else {
			ans2[i] = -1;
			dummyUpdate(a[i].x1, a[i].x2, a[i].val);
		}
	}
}


int rand30() {
	return (((rand() & (((1 << 10) - 1) << 3)) >> 3) << 0) |
		(((rand() & (((1 << 10) - 1) << 3)) >> 3) << 10) |
		(((rand() & (((1 << 10) - 1) << 3)) >> 3) << 20);
}


class Point
{

};
int main(void) {
	// Generate test;
	//srand(42);

	//for (int i = 0; i < MAX_IDX; i++)
	//	init[i] = rand30() % 2000001 - 1000000;

	//n = NUM_QUERIES; // Set number of queries
	//for (int i = 0; i < n; i++) {
	//	a[i].x1 = rand30() % MAX_IDX; a[i].x2 = rand30() % MAX_IDX;
	//	if (a[i].x1 > a[i].x2)
	//		std::swap(a[i].x1, a[i].x2);

	//	a[i].val = rand30() % 20001 - 10000;
	//	a[i].type = rand30() % 2 ? QUERY : UPDATE;
	//}

	//unsigned startTime;
	//// Solve with interval trees
	//startTime = clock();
	//solveTrees();
	//fprintf(stdout, "Interval trees execution time: %.3lfs\n",
	//	(double)(clock() - startTime) / (double)CLOCKS_PER_SEC);

	//// Check by dummy
	//startTime = clock();
	//solveDummy();
	//fprintf(stdout, "Dummy solution execution time: %.3lfs\n",
	//	(double)(clock() - startTime) / (double)CLOCKS_PER_SEC);

	//int correct = 1;
	//for (int i = 0; i < n; i++) {
	//	if (a[i].type == QUERY) {
	//		if (ans1[i] != ans2[i]) {
	//			correct = 0;
	//			break;
	//		}
	//	}
	//}
	//fprintf(stdout, "Solution is %s.\n", correct ? "correct" : "incorect");

	vector<int> v;
	for (int i = 0; i < 7; ++i)
		v.push_back(i);

	v[3] = 21;

	IntervalTree<int> intTree(v);

	std::cout << intTree.query(0, 6) << endl;
	intTree.update(0, 4, 5);

	std::cout << intTree.query(0, 6) << endl;
	return 0;
}