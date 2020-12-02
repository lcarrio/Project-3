#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string cutExtra(string word) {

	if (word.length() == 0 || word.length() == 1) return word;

	int length = word.length() - 1;

	if (word.at(0) == '\"' || word.at(0) == ',' || word.at(0) == '.' || word.at(0) == ':' || word.at(0) == ';' || word.at(0) == '!' || word.at(0) == '?' || word.at(0) == ' ' || word.at(0) == '&' || word.at(0) == '#' || word.at(0) == '@' || word.at(0) == '\'' || word.at(0) == '(' || word.at(0) == ')' || word.at(0) == '/”') {
		word = word.substr(1, length);
		word = cutExtra(word);
		length = word.length() - 1;
	}
	
	if ((word.length() != 0 && word.length() != 1) && (word.at(length) == '\"' || word.at(length) == ',' || word.at(length) == '.' || word.at(length) == ':' || word.at(length) == ';' || word.at(length) == '!' || word.at(length) == '?' || word.at(length) == ' ' || word.at(length) == '&' || word.at(length) == '#' || word.at(length) == '@' || word.at(length) == '\'' || word.at(length) == '(' || word.at(length) == ')' || word.at(0) == '/”')) {
		word = word.substr(0, length);
		word = cutExtra(word);
		length = word.length() - 1;
	}

	return word;
}

int main() {
	bool runAgain = true;
	while (runAgain) {
		map<string, long int> words;
		long long int wordCount = 0;
		string currentLine;
		string word;

		string inputFileName = "";
		string outputFileName = "";

		cout << "Input name of file to read: ";
		cin >> inputFileName;
		cout << endl << "Input name of file to write: ";
		cin >> outputFileName;
		cout << endl;

		ifstream reader(inputFileName);

		if (reader.is_open()) {
			while (getline(reader, currentLine)) {

				stringstream ss(currentLine);

				while (getline(ss, word, ' ')) {

					string currentWord = word;
					if (word.length() > 1) currentWord = cutExtra(currentWord);
					if (word.length() == 0) continue;

					cout << currentWord;

					if (words.find(currentWord) != words.end()) {
						words.at(currentWord)++;
					}

					else {
						words.insert(pair<string, long int>(currentWord, 1));
					}

					wordCount++;

					cout << " " << wordCount << endl;
				}
			}

			reader.close();

		}

		map<string, long int>::iterator iter;

		ofstream writter(outputFileName);

		for (iter = words.begin(); iter != words.end(); iter++) {
			double hold = iter->second;
			double ratio = (hold / wordCount);
			writter << iter->first << "," << ratio << "," << endl;
		}

		cout << endl << "Run again? Type Y or N: ";
		string run = "";
		cin >> run;
		cout << endl;
		if (run.at(0) == 'Y') continue;
		else break;
	}

	return 0;
}