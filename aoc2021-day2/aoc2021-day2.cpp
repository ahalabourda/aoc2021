// aoc2021-day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main()
{

    // this exists mainly because later i want to use a switch later when we're parsing all the commands. this if/else chain seems unavoidable but oh well
    enum Direction { Forward, Up, Down };

    // struct to store both parts of a submarine command! first part of a command is always a string "forward", "up", or "down" (never "back"); second part is a single number representing distance
    // i spent a while mucking about with maps and pairs and arrays trying to find a good way to store a direction and a distance but after realizing i wanted to do string->enum logic in the constructor, i figured a struct would be cool
    struct SubmarineCommand {

        Direction direction;
        int distance;

        SubmarineCommand(string dir, int dist)
        {
            
            if (dir == "forward") {

                // compiler complains here about Direction being a regular enum instead of enum class but at 1:30am i'm too lazy to change things up. maybe i revisit this later
                direction = Forward;

            }
            else if (dir == "down") {

                direction = Down;

            }
            else if (dir == "up") {

                direction = Up;

            }
            else {

                // not sure what best practice is here...
                // vs is mad at me if i don't guarantee that direction gets initialized, but invalid direction strings to a real value seems wrong.
                // another solution in my mind is to add a "None" or "Null" value to the enum but that seems.. also wrong.
                // none of these options are fantastic, but it also doesn't matter if we're *guaranteed* to never have bad inputs.. so this works for an AoC challenge but would never go into prod on a real thing
                direction = Forward;
            }

            distance = dist;
        }

    };

    vector<SubmarineCommand> allCommands;

    bool running = true;

    string input;

    // need flavour
    cout << "Welcome to Submarine Commander 2000! Direct your submarine by entering a direction (forward, down, up) and a single-digit number for distance, eg \"forward 6\" - best of luck out there! Oh also, type \"exit\" or \"done\" to quit playing.\r\n\r\n";

    // this solution is VERY dependent on our inputs being perfectly formed. i'm glad this is advent of code and not hackerrank. sheesh
    // this loop accepts user input in the form of "forward 5" - a word that is always forward/down/up, then one space, then one digit. 
    // this loop continues forever until the user types "exit"
    while (running) {

        cout << "What's the plan, cap'n?: ";

        // first attempt here was just "cin >> input" but that broke on spaces so this function appears to break on linebreaks! big iprovement.
        // the fact that we're passing it "cin" hints to me that there are other streams we could be passing instead... very curious!!
        getline(cin, input);

        if (input == "exit" || input == "done") {

            cout << "We're done!\r\n";

            running = false;

        } else {

            // okay this part is a bit ugly i think
            // we know the exact form that every input is gonna take so we're gonna iterate over each char manually to find the direction and then the distance, and then store a SubmarineCommand object with that data
            string directionFinder;
            int distanceFinder = 0;

            // simply looping over each character until we find a space and then storing the word we found, then storing the character after the space as an int (after subtracting 48 to translate from ascii value to actual int value)
            // TIL: visual complained that an "int i = 0" here was dangerous/undesirable because int is signed and input.size() returns an unsigned int, so comparisons might break. i assume that only happens at super huge values but still changed "int i" to "size_t i" to make vs happy. looking up "size_t" tells me that it's explicitly defined as the result of the "sizeof" operator which makes me feel like i shouldn't be using it for things other than that... hmm
            for (size_t i = 0; i < input.size(); i++) {
                
                if (input[i] == ' ') {
                    
                    distanceFinder = (int)(input[i + 1] - 48); // oh HELL yeah. we love to see manual ascii conversion
                    break;

                }

                // am i generating a billion strings in memory by doing this??? probably i think?? 
                // i googled "c++ stringbuilder" and found some stuff about stringstream that looks promising but it's 1:45am so i will investigate this further later
                // WAIT i found a stackoverflow comment saying that c++ strings ARE mutable, so regular concatenation is performant and fine...? okay! hmm
                // this does make me wonder if this whole thing should have just been a char array but i'd need advice on how best to handle the different lengths of inputs in that case
                directionFinder += input[i];

            }

            allCommands.push_back(SubmarineCommand(directionFinder, distanceFinder));
        }
    }

    int distance = 0;
    int depth = 0;

    // straightforward stuff
    for (unsigned int i = 0; i < allCommands.size(); i++) {
        
        switch (allCommands[i].direction) {
            case Forward:
                distance += allCommands[i].distance;
                break;
            case Down:
                depth += allCommands[i].distance;
                break;
            case Up:
                depth -= allCommands[i].distance;
                break;
        }

        //cout << "adding " << allCommands[i].distance << " to " << allCommands[i].direction << "\r\n";

    }

    // amazing
    cout << "We have completed our journey to a distance of " << distance << " and a depth of " << depth << ", which multiplied together equal: " << distance * depth << ". Amazing!\r\n";


}