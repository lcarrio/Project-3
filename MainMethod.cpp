#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

/*Take two files as input into a hash table
Hash table: key = string “name”
        Value = word object

Word object
    Double repub = 0;
    Double demo = 0;


Get inputted tweet

Calculate total tweet value
    For each word:
        Demo - repub
    Add up all word values
    if(negative) = more repub
    if(positive) = more demo
*/

class Word {
public:
    double demoValue = 0.00;
    double repubValue = 0.00;
};

unordered_map<string, Word> initializeMaps() {
    ifstream reader1("demowords.txt");
    ifstream reader2("repubwords.txt");
    unordered_map <string, Word> dictionary;
    string currentLine;
    string tempValue;
    string word;
    double totalRepubCount = 0.00;
    double totalDemoCount = 0.00;
    double value = 0.00;

    string userInput;
    double weight = 0.00;

    //Input the democratic words and values into the dictionary map
    if (reader1.is_open()) {
        //Store the total word count
        getline(reader1, tempValue);
        totalDemoCount = stod(tempValue);

        //get each word and its quantity, calculate value of word (wordCount / totalWordCount)
        while (getline(reader1, currentLine)) {
            stringstream ss(currentLine);
            getline(ss, word, ',');
            getline(ss, tempValue, ',');
            value = stod(tempValue);
            Word temp;
            temp.demoValue = value / totalDemoCount;
            dictionary.insert(pair<string, Word>(word, temp));
        }
        reader1.close();
    }

    //Input the republican words and values into the dictionary map
    if (reader2.is_open()) {
        //Store the total word count
        getline(reader2, tempValue);
        totalRepubCount = stod(tempValue);
        //get each word and its quantity, calculate value of word = (wordCount / totalWordCount)
        while (getline(reader2, currentLine)) {
            stringstream ss(currentLine);
            getline(ss, word, ',');
            getline(ss, tempValue, ',');
            value = stod(tempValue);
            Word temp;
            temp.repubValue = value / totalRepubCount;

            //If the word already exists in the map, just adjust its associated republican value
            if (dictionary.find(word) != dictionary.end()) {
                dictionary.at(word).repubValue = (value / totalRepubCount);
            }

            //If the word does not exist in the map, add it to the map
            else {
                dictionary.insert(pair<string, Word>(word, temp));
            }

        }
        reader2.close();
    }


    //This part is just for checking the contents of the dictionary
    /*map<string, Word>::iterator iter;
    for (iter = dictionary.begin(); iter != dictionary.end(); iter++) {
        cout << iter->first << " Demo: " << iter->second.demoValue << " Repub: " << iter->second.repubValue << endl;
    }*/

    return dictionary;

};


int getValue(unordered_map<string, Word> dictionary, string userInput) {
    string word = "";
    double weight = 0.00;

    //Put the tweet into a string stream
    stringstream inputParsing(userInput);

    //Split tweet into words, calculate party 
    while (getline(inputParsing, word, ' ')) {
        transform(word.begin(), word.end(), word.begin(), tolower);

        for (int i = 0; i < word.length(); i++) {
            if (!(word.at(i) >= 'A' && word.at(i) <= 'Z' || word.at(i) >= 'a' && word.at(i) <= 'z') && word.at(i) != '#' && word.at(i) != '@') {
                word.erase(i, 1);
                i -= 1;
            }
        }



        if (dictionary.find(word) != dictionary.end()) {
            //cout << endl << word << " " << dictionary.at(word).demoValue - dictionary.at(word).repubValue;
            weight += (dictionary.at(word).demoValue - dictionary.at(word).repubValue);
        }
        else continue;
    }

    //If weight is positive, return Democrat
    if (weight > 0) {
        return 1;
    }

    //If weight is negative, return Republican
    else if (weight < 0) {
        return 2;
    }

    //If weight is 0, return undetermined
    else {
        return 0;
    }

};

int main() {
    unordered_map<string, Word> dictionary = initializeMaps();
    string input = "";
    string userInput = "";
    bool cont = true;
    string temps = "";
    cout << "Input tweet: ";
    getline(cin, userInput);

    while (cont) {
        cout << endl;
        int temp = getValue(dictionary, userInput);
        switch (temp) {
        case 1: cout << "Democrat" << endl;
            break;
        case 2: cout << "Republican" << endl;
            break;
        default: cout << "Undetermined" << endl;
        }

        cout << "Continue? Type Y or N" << endl;
        cin >> input;
        if (input.at(0) == 'Y') {
            cout << "Input tweet: ";
            getline(cin, temps);
            getline(cin, userInput);

        }

        else break;
        
    }
    return 0;
}