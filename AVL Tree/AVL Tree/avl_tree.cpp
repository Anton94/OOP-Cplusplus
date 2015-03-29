#include "test_avl_tree.h"
#include <iostream>
#include <cstdio>
#include <string> 
#include <set>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;


double avlTime;
bool executeTest(const string& testName, int numbers[], int size, int deletions[], int deletionsSize, bool checkTree)
{
	print("Executing test: '%s'", testName.c_str());
	double begin, end;
	avlTime = 0;
	double rbTime = 0, checkerTime = 0;
	begin = get_time();
	multiset<int> values;
	end = get_time();
	rbTime += (end - begin);
	begin = end;
	TestAVLTree<int> myTree;
	end = get_time();
	avlTime += (end - begin);
	begin = end;
	if (checkTree && !myTree.checkTree(values))
    {
    	return false;
    }
	end = get_time();
	checkerTime += (end - begin);
	int operationIndex = 0;
	int deletionIndex = 0;
	multiset<int>::iterator itr;
	for (int i = 0; i < size; i++)
	{
		operationIndex++;
		if (deletionIndex < deletionsSize && deletions[deletionIndex * 2] == operationIndex)
		{
			i--;
			if(deletions[deletionIndex * 2 + 1] < size)
			{
				begin = get_time();
				if ((itr = values.find(numbers[deletions[deletionIndex * 2 + 1]])) != values.end())
				{
					values.erase(itr);
				}
				end = get_time();
				rbTime += (end - begin);
				begin = end;
				myTree.deleteNode(numbers[deletions[deletionIndex * 2 + 1]]);
				end = get_time();
				avlTime += (end - begin);
			} else {
				begin = get_time();
				// -1 should be non-existing value
				myTree.deleteNode(-1);
				end = get_time();
				avlTime += (end - begin);
			}
		} else {
			begin = get_time();
			values.insert(numbers[i]);
			end = get_time();
			rbTime += (end - begin);
			begin = end;
			myTree.insertNode(numbers[i]);
			end = get_time();
			avlTime += (end - begin);
		}
		begin = get_time();
		if (checkTree && !myTree.checkTree(values) )
		{
			end = get_time();
			checkerTime += (end - begin);
			print("\nTimes taken: RB: %0.5lf AVL time %0.5lf Checker time  %0.5lf", rbTime, avlTime, checkerTime);
#ifdef MEASURE_TIME
			myTree.printTimes();
#endif
			print("\nTest failed\n\n");
			return false;
		}
		end = get_time();
		checkerTime += (end - begin);
	}
	print("\nTimes taken: RB: %0.5lf AVL time %0.5lf Checker time  %0.5lf", rbTime, avlTime, checkerTime);
#ifdef MEASURE_TIME
	myTree.printTimes();
#endif
	if (checkTree)
	{
		print("\nTest passed");
	}
	print("\n\n");
	
	return true;
}

bool randomTest(int numberCount, int deletionsCount, bool executeCheck)
{
	int * numbers = new int[numberCount];
	int * deletions = new int[deletionsCount * 2];
	for (int i = 0; i < numberCount; i++)
	{
		numbers[i] = rand();
	}
	for (int i = 0; i < deletionsCount; i++)
	{
		deletions[i * 2] = 5 + rand() % (numberCount - 5);
		deletions[i * 2 + 1] = rand() % (i + 1);
	}
	stringstream ss;
	ss << "Random test with " << numberCount << " numbers and " << deletionsCount << " deletions";
	bool result = executeTest(ss.str(), numbers, numberCount, deletions, deletionsCount, executeCheck);
	delete [] numbers;
	delete [] deletions;
	return result;
}

int testResultPrinter(string testLabel, bool testSuccessful, int successfulPoints, int failurePoints = 0)
{
	if (testSuccessful)
	{
		print("----- '%s' test PASSED-----\n", testLabel.c_str());
		if (successfulPoints != 0)
		{
			print("----- this adds %d points to your final score----\n", successfulPoints);
		}
		print("\n\n");
		return successfulPoints;
	} else {
		print("----- '%s' test FAILED----\n", testLabel.c_str());
		if (failurePoints != 0)
		{
			print("----- this subtracts %d points from your final score----\n", failurePoints);
		}
		print("\n\n");
		return -failurePoints;
	}
}

int testInsertSmall()
{
	bool successfulTest = true;
	int smallTest1[] = {5, 3, 7, 2, 11, 18};
	int emptyDeletions[] = {3, 50};
	int smallTest2[] = {134, 41, 876, 124, 23, 47, 13, 55, 7, 101, 68, 45, 75, 61, 31, 34, 62, 90, 17, 42};
	successfulTest = successfulTest && executeTest("First small test", smallTest1, sizeof(smallTest1) / sizeof(int), emptyDeletions, 0, true);
	successfulTest = successfulTest && executeTest("Second small test", smallTest2, sizeof(smallTest2) / sizeof(int), emptyDeletions, 1, true);
	return testResultPrinter("Small insert", successfulTest, 1);
}

int testDeleteSmall()
{
	bool successfulTest = true;
	int smallTest2[] = {134, 41, 876, 124, 23, 47, 13, 55, 7, 101, 68, 45, 75, 61, 31, 34, 62, 90, 17, 42};
	int deletions1[] = {5, 2, 14, 5, 15, 6};
	successfulTest = successfulTest && executeTest("First small test with deletions", smallTest2, sizeof(smallTest2) / sizeof(int), deletions1, (sizeof(deletions1) / sizeof(int)) / 2, true);
	successfulTest = successfulTest && randomTest(22, 4, true);
	successfulTest = successfulTest && randomTest(22, 4, true);
	return testResultPrinter("Small delete", successfulTest, 1);
}

int testInsertBig()
{
	bool successfulTest = true;
	successfulTest = successfulTest && randomTest(91, 0, true);
	successfulTest = successfulTest && randomTest(265, 0, true);
	successfulTest = successfulTest && randomTest(310, 0, true);
	successfulTest = successfulTest && randomTest(2654, 0, true);
	successfulTest = successfulTest && randomTest(4213, 0, true);
	successfulTest = successfulTest && randomTest(12000, 0, true);
	return testResultPrinter("Big insert", successfulTest, 1);
}

int testDeleteBig()
{
	bool successfulTest = true;
	int smallTest2[] = {134, 41, 876, 124, 23, 47, 13, 55, 7, 101, 68, 45, 75, 61, 31, 34, 62, 90, 17, 42};
	int deletions2[] = {7, 5, 8, 4, 9, 3, 10, 2, 11, 1, 12, 0};
	successfulTest = successfulTest && executeTest("Testing deleting all numbers", smallTest2, sizeof(smallTest2) / sizeof(int), deletions2, (sizeof(deletions2) / sizeof(int)) / 2, true);
	successfulTest = successfulTest && randomTest(91, 21, true);
	successfulTest = successfulTest && randomTest(265, 42, true);
	successfulTest = successfulTest && randomTest(310, 63, true);
	successfulTest = successfulTest && randomTest(2654, 403, true);
	successfulTest = successfulTest && randomTest(4213, 702, true);
	successfulTest = successfulTest && randomTest(12000, 2000, true);
	return testResultPrinter("Big delete", successfulTest, 1);
}

int testComplexity()
{
	randomTest(1200000, 200000, false);
	double avlTime1 = avlTime;
	randomTest(12000000, 2000000, false);
	double avlTime2 = avlTime;
	bool complexityCorrect = (avlTime2 < 20.0 * log(10.0) * avlTime1);
	return testResultPrinter("Asymptotic complexity", complexityCorrect, 0, 2);
}

int main()
{
	int result = 0; 
	result += testInsertSmall();
	result += testInsertBig();
	result += testDeleteSmall();
	result += testDeleteBig();
	result += testComplexity();
	print("\n\nPreliminary result: %d points from this homework\n", max(result, 0));
	print("For the user: %s with moodle name: %s and fn: %s\n\n", getName().c_str(), getMoodleName().c_str(), getFacultyNumber().c_str());

	
	return 0;
}