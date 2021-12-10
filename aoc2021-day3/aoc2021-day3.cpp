// aoc2021-day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

// for the real input
const int LINE_LENGTH = 12;
// for test input
//const int LINE_LENGTH = 5;

bitset<LINE_LENGTH> FindOxygenGeneratorRatingFromValues(istream& inputFile);
bitset<LINE_LENGTH> FindCarbonDioxideScrubberRatingFromValues(istream& inputFile);

int main()
{

    ifstream inputFile;

    // wanted to define this value at runtime so that my bitsets and vector would be line length agnostic but there doesn't appear to be a way to do that at runtime with regular bitsets
    // saw a post about Boost::dynamic_bitset but using a dynamic data type seems to be defeating the purpose
    // just gonna sadly hardcode this. oh well. gg
     
    inputFile.open("real-input1.txt");
    //inputFile.open("test-input1.txt");
    
    if (!inputFile) {
        cerr << "Unable to open input file";
        exit(1);
    }
   
    string singleLine;

    // doesn't work :[ sadge
    //getline(inputFile, singleLine);
    //const int LINE_LENGTH = singleLine.size();
    //inputFile.seekg(0);

    // see comment below about hardcoded 
    int values[LINE_LENGTH] = {};

    while (getline(inputFile, singleLine)) {

        
        for (int i = 0; i < LINE_LENGTH; i++) {
            
            if (singleLine[i] == '1') {
                values[i]++;
            }
            else {
                values[i]--;
            }
            
        }

    }

    bitset<LINE_LENGTH> gammaBits;
    bitset<LINE_LENGTH> epsilonBits;

    for (int i = 0; i < LINE_LENGTH; i++) {
        
        gammaBits[LINE_LENGTH - 1 - i] = values[i] > 0;

    }

    // can i not do this without requiring the second flip..?
    // seems pretty weird for .flip() to do something in-place AND return a value. hoping there's a neater way to do this even if this seems like it's still pretty fast
    //epsilonBits = gammaBits.flip();
    //gammaBits.flip();

    // haha i figured it out. woot
    epsilonBits = ~gammaBits;

    cout << "Gamma bits: " << gammaBits << "\r\n";

    cout << "Final gamma int: " << (int)gammaBits.to_ulong() << " - " << "Final gamma int: " << (int)epsilonBits.to_ulong() << " which when multiplied together gives " << (int)gammaBits.to_ulong() * (int) epsilonBits.to_ulong() << "\r\n------\r\n";

    cout << "Behold our answer: " << (int)FindOxygenGeneratorRatingFromValues(inputFile).to_ulong() << " for the first thing and " << (int)FindCarbonDioxideScrubberRatingFromValues(inputFile).to_ulong() << " for the second thing! If we multiply these together we get: " << (int)FindOxygenGeneratorRatingFromValues(inputFile).to_ulong() * (int)FindCarbonDioxideScrubberRatingFromValues(inputFile).to_ulong() << "\r\n";
    //cout << "Behold our answer: " << FindOxygenGeneratorRatingFromValues(inputFile) << " for the first thing and " << " nothing " << " for the second thing!\r\n";

}


bitset<LINE_LENGTH> FindOxygenGeneratorRatingFromValues(istream &input) {

    // reset our position to the start of the file
    input.clear();
    input.seekg(0);

    string singleLine;

    int values[LINE_LENGTH] = {};

    vector<bitset<LINE_LENGTH>> lines;

    while (getline(input, singleLine)) {

        lines.push_back(bitset<LINE_LENGTH>(singleLine));
        
    }
    
    bool desiredValue;
    
    // loop over each column of the inputs
    for (int i = LINE_LENGTH - 1; i >= 0; i--) {

        int tracker = 0;

        // check the whole column to find its most popular option
        for (int j = 0; j < lines.size(); j++) {

            if (lines[j][i] == 1) {
                tracker++;
            }
            else {
                tracker--;
            }

        }

        if (tracker >= 0) {
            desiredValue = 1;
        }
        else {
            desiredValue = 0;
        }
        
        vector<bitset<LINE_LENGTH>>::iterator it = lines.begin();

        while (it != lines.end()) {

            if ((*it)[i] != desiredValue) {

                it = lines.erase(it);
                
            }
            else {
                ++it;
            }

        }

    }

    return lines[0];

}

bitset<LINE_LENGTH> FindCarbonDioxideScrubberRatingFromValues(istream &input) {
    
    // reset our position to the start of the file
    input.clear();
    input.seekg(0);

    string singleLine;

    int values[LINE_LENGTH] = {};

    vector<bitset<LINE_LENGTH>> lines;

    while (getline(input, singleLine)) {

        lines.push_back(bitset<LINE_LENGTH>(singleLine));

    }

    bool desiredValue;

    // loop over each column of the inputs
    for (int i = LINE_LENGTH - 1; i >= 0; i--) {

        int tracker = 0;

        // check the whole column to find its most popular option
        for (int j = 0; j < lines.size(); j++) {

            if (lines[j][i] == 1) {
                tracker++;
            }
            else {
                tracker--;
            }

        }

        if (tracker >= 0) {
            desiredValue = 0;
        }
        else {
            desiredValue = 1;
        }

        vector<bitset<LINE_LENGTH>>::iterator it = lines.begin();

        while (it != lines.end() && lines.size() != 1) {

            if ((*it)[i] != desiredValue) {

                it = lines.erase(it);

            }
            else {
                ++it;
            }

        }

    }

    return lines[0];

}