#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    string line, word;
    int totalWords = 0;
    map<string, int> wordsCount;
    map<string, int>::iterator mapIt;

    ifstream input("republicans.csv");
    ofstream output("republicansOutput.txt");
    
    while (getline(input, line)) {
        stringstream ss(line);
        while (getline(ss, word, ' ')) {
            //Used to ignore words containing the UTF-8 "…" character as to avoid chopped off words in the file
            if (word.find(u8"…") == string::npos) {
                //Filtering out all chars that are not alphabetic and are not #'s or @'s
                for (int i = 0; i < word.length(); i++) {
                    if (!(word.at(i) >= 'A' && word.at(i) <= 'Z' || word.at(i) >= 'a' && word.at(i) <= 'z') && word.at(i) != '#' && word.at(i) != '@') {
                        word.erase(i, 1);
                        i -= 1;
                    }
                }

                //Makes the entire word lowercase
                transform(word.begin(), word.end(), word.begin(), tolower);

                /*
                * Deletes the word if its a link, or if theres a link at the end of the word, gets the word before the link
                * i.e. "https://link.co" gets deleted and "wordhtts://link.co" becomes "word"
                */
                if (word.find("http") != string::npos) {
                    word = word.substr(0, word.find("http"));
                }

                /*
                * Used to account for #'s and @'s that are attached to words. Does not affect solitary #'s and @'s
                * i.e. "word#one@two" becomes "word", "#one", and "@two"
                */
                if (word.find("#") != string::npos || word.find("@") != string::npos) {
                    for (int i = word.length() - 1; i > -1; i--) {
                        if (word.at(i) == '#' || word.at(i) == '@') {
                            wordsCount[word.substr(i, word.length())]++;
                            word = word.substr(0, i);
                            totalWords++;
                        }
                    }
                }

                //Prevents the program from adding empty strings to the map
                if (word != "") {
                    wordsCount[word]++;
                    totalWords++;
                }
            }
        }
    }

    //Prints out all of the words stored in the map along with their word count and ratio of uses to total words found
    output << "Total words: " << totalWords << '\n';
    for (mapIt = wordsCount.begin(); mapIt != wordsCount.end(); mapIt++) {
        output << mapIt->first << ", " << mapIt->second << '\n';
    }
    return 0;
}