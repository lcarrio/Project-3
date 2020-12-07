
#pragma once
#include <string>
#include <iostream>
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
#include <locale>
using namespace std;
class Word {
public:
    double demoValue = 0.00;
    double repubValue = 0.00;
};

unordered_map<string, Word> initializeMaps() {
    ifstream reader1("demowords.txt");
    if(reader1.is_open()){
        cout<< "yes";
    }
    ifstream reader2("repubwords.txt");
    unordered_map <string, Word> dictionary;
    string currentLine;
    string tempValue;
    string word;
    double totalRepubCount = 0.00;
    double totalDemoCount = 0.00;
    double value = 0.00;

    string userInput;
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
    unordered_map<string, Word>::iterator iter;
    cout << "hi";
    for (iter = dictionary.begin(); iter != dictionary.end(); iter++) {
        cout << iter->first << " Demo: " << iter->second.demoValue << " Repub: " << iter->second.repubValue << endl;
    }

    return dictionary;

};


int getValue(unordered_map<string, Word> dictionary, string userInput) {
    string word = "";
    double weight = 0.00;

    //Put the tweet into a string stream
    stringstream inputParsing(userInput);

    //Split tweet into words, calculate party
    while (getline(inputParsing, word, ' ')) {
        
   // transform(word.begin(), word.end(), word.begin(), tolower);

        for (int i = 0; i < word.length(); i++) {
            tolower(word[i]);
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
/*
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
    return 0; */
class MainContentComponent   : public juce::Component
{
    // Sets the background color for the panel
    void paint (juce::Graphics& panel) override
    {
        panel.fillAll (juce::Colours::black);
    }
public:
    juce::Label twitterPartyCalculator;
    juce::Label enterTweet;
    juce::Label inputText;
    juce::Label output;
    juce::Label outputText;
    juce::Label passOnText;
    juce::Label orderedMapTime;
    juce::Label unorderedMapTime;
    juce::Label fastestTime;
    juce::Label mapText;
    juce::Label hashText;
    
    MainContentComponent()
    {
        orderedMapTime.setText("Time for execution using ordered map:", juce::dontSendNotification);
        orderedMapTime.setColour(juce::Label::textColourId, juce::Colours::lightblue);
        orderedMapTime.attachToComponent(&mapText,true);
        addAndMakeVisible(orderedMapTime);
        orderedMapTime.setJustificationType (juce::Justification::left);
        addAndMakeVisible(mapText);
        
        unorderedMapTime.setText("Time for execution using hash table: ",juce::dontSendNotification);
        unorderedMapTime.setColour(juce::Label::textColourId, juce::Colours::lightblue);
        unorderedMapTime.attachToComponent(&hashText,true);
        addAndMakeVisible(unorderedMapTime);
        unorderedMapTime.setJustificationType(juce::Justification::left);
        addAndMakeVisible(hashText);
        
       //Sets the text at the top of the input box
        twitterPartyCalculator.setText ("Please click on the box to enter your tweet",juce::dontSendNotification);
        //Sets the color of the text to lightblue
        twitterPartyCalculator.setColour (juce::Label::textColourId, juce::Colours::lightblue);
        addAndMakeVisible (twitterPartyCalculator);
        
        // Creates the label next to the input text editor
        enterTweet.setText ("Tweet Entered:", juce::dontSendNotification);
        // Attach it to the input text component so that i only have to manipulate enterTweet
        enterTweet.attachToComponent (&inputText, true);
        enterTweet.setColour (juce::Label::textColourId, juce::Colours::lightblue);
        enterTweet.setJustificationType (juce::Justification::right);
        addAndMakeVisible (enterTweet);

        // Creates the output label
        addAndMakeVisible (output);
        output.setText ("Party:", juce::dontSendNotification);
        //Attach it to the output text component so that I only have to manipulate outputText
        output.attachToComponent (&outputText, true);
        output.setColour (juce::Label::textColourId, juce::Colours::lightblue);
        output.setJustificationType (juce::Justification::right);
        addAndMakeVisible (outputText);
        outputText.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
        addAndMakeVisible (inputText);
        // Sets the inputText to be an editor where the user can insert text.
        inputText.setEditable (true);
        inputText.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
        // Even that triggers whenever the input text editor is changed.
        inputText.onTextChange = [this]{
            // Set passOnText equal to whatever the input text is.
         passOnText.setText(inputText.getText(), juce::dontSendNotification);
            // Stores the text inputed by the user and creates a string out of it.
                auto j = passOnText.getText();
                string tweet;
                for(int i = 0; i < j.length(); i++){
                    char c = j[i]; // J is a Juce::String which is why we needed to do this.
                    tweet += c;
                }
            juce::String mapTimeSeconds = "5 ms";
            juce::String hashTextSeconds = "5 ms";
            mapText.setText(mapTimeSeconds,juce::dontSendNotification);
            hashText.setText(hashTextSeconds,juce::dontSendNotification);
            unordered_map<string, Word> dictionary = initializeMaps();
            int output = getValue(dictionary, tweet);
            if(output == 0){
                outputText.setText("Neither",juce::dontSendNotification);
            }
            if(output == 1){
                outputText.setText("Democrat",juce::dontSendNotification);
            }
            if(output == 2){
                outputText.setText("Republican",juce::dontSendNotification);
            }
            
            };
        setSize (500, 350);
    }
    // Function to set the location of the text labels
    void resized() override
    {
        orderedMapTime.setBounds(0,210,getWidth()-20,30);
        unorderedMapTime.setBounds(0,240,getWidth()-20,30);
        hashText.setBounds(300,240,getWidth()-20,30);
        mapText.setBounds(300,210,getWidth()-20,30);
        twitterPartyCalculator.setBounds (5,  30, getWidth() - 20,  30);
        inputText.setBounds (100, 70, getWidth() - 110, 20);
        outputText.setBounds (100, 140, getWidth() - 110, 20);
    }
};

