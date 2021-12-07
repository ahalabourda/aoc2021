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
//const int LINE_LENGTH = 12;
// for test input
const int LINE_LENGTH = 5;

bitset<LINE_LENGTH> FindOxygenGeneratorRatingFromValues(istream& inputFile);

int main()
{

    ifstream inputFile;

    // wanted to define this value at runtime so that my bitsets and vector would be line length agnostic but there doesn't appear to be a way to do that at runtime with regular bitsets
    // saw a post about Boost::dynamic_bitset but using a dynamic data type seems to be defeating the purpose
    // just gonna sadly hardcode this. oh well. gg
     
     //inputFile.open("real-input1.txt");
    inputFile.open("test-input1.txt");
    

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
    epsilonBits = gammaBits.flip();
    gammaBits.flip();

    cout << "Gamma bits: " << gammaBits << "\r\n";

    cout << "Final gamma int: " << (int)gammaBits.to_ulong() << " - " << "Final gamma int: " << (int)epsilonBits.to_ulong() << " which when multiplied together gives " << (int)gammaBits.to_ulong() * (int) epsilonBits.to_ulong() << "\r\n------\r\n";

    FindOxygenGeneratorRatingFromValues(inputFile);

}


bitset<LINE_LENGTH> FindOxygenGeneratorRatingFromValues(istream &input) {

    // reset our position to the start of the file
    input.clear();
    input.seekg(0);

    bitset<LINE_LENGTH> finalResult;

    string singleLine;

    int values[LINE_LENGTH] = {};

    vector<bitset<LINE_LENGTH>> lines;

    while (getline(input, singleLine)) {

        lines.push_back(bitset<LINE_LENGTH>(singleLine));
        
    }
    
    bool desiredValue;    
    
    for (int i = 0; i < LINE_LENGTH; i++) {

        int tracker = 0;

        for (int j = 0; j < lines.size() / lines[0].size(); j++) {

            cout << "doing J " << j << "\r\n";

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
        
        // this linesDeleted business is definitely terrible and i think i should learn to use iterators to prevent it in the future
        int linesDeleted = 0;

        for (int k = 0; k < (lines.size() / lines[0].size()) - linesDeleted; k++) {

            if (lines[k - linesDeleted][0] != desiredValue) {
                cout << "removeing line " << k - linesDeleted << "\r\n";
                lines.erase(lines.begin() + k - linesDeleted);
                linesDeleted++;
            }

        }

    }

    cout << "there's no way this works right? vector size is: " << lines.size() / lines[0].size() << " and our 0th value is " << lines[0] << "\r\n";

    return finalResult;

}

bitset<LINE_LENGTH> FindCarbonDioxideScrubberRatingFromValues(istream &input) {
    
    bitset<LINE_LENGTH> finalResult;
    return finalResult;

}