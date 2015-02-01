#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/// Maxa 'searched' string-a ot word-a i go dobavq kum singleAnswer kato go push-va i v vectora ot otgovori.
void editAnswer(string & word, string &singleAnswer, vector<string>& answers, string searched)
{
	std::string::size_type i = word.find(searched);

	if (i != std::string::npos) // ima go
		word.erase(i, searched.length());

	singleAnswer += " ";
	singleAnswer += word;

	answers.push_back(singleAnswer);
	singleAnswer = "";
}

int main()
{
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");

	if (!inFile)
	{
		cerr << "KUR BACE" << endl;
		return -1;
	}

	if (!outFile)
	{
		cerr << "KUR BACE 2" << endl;
		return -1;
	}

	string questionText;
	string singleAnswer;
	string word;
	int number;
	vector<string> answers;

	while (getline(inFile, word, ' '))
	{
		if (word.find("QUESTION:") != std::string::npos || word.find("Question:") != std::string::npos)
		{
			inFile >> number;
			outFile << "QUESTION: " << number;

			// Get question text.
			getline(inFile, questionText, '?');
			outFile << questionText << "?\n";

			getline(inFile, word, ' ');
		}
		else if (word.find("B.") != std::string::npos)
		{
			editAnswer(word, singleAnswer, answers, "B.");
		}
		else if (word.find("C.") != std::string::npos)
		{
			editAnswer(word, singleAnswer, answers, "C.");
		}
		else if (word.find("D.") != std::string::npos)
		{
			editAnswer(word, singleAnswer, answers, "D.");
		}
		else if (word.find("Answer:") != std::string::npos)
		{
			editAnswer(word, singleAnswer, answers, "Answer:");

			// Get the index.
			getline(inFile, word, '\n');
			int index = (char)word[0] - 'A';

			outFile << word << ". " << answers[index] << "\n";

			answers.clear();
		}
		else
		{
			singleAnswer += " ";
			singleAnswer += word;
		}
	}

	return 0;
}