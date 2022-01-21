// Wordle Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"

using namespace std;

int CheckArguments(int argc,char *argv[], string &badLetters, string &PossibleLetters, nlohmann::json &KnownLetters) {
    int i;
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "\033[2J\033[1;1H";
            printf("\nThis is to determine possible words for Wordle.\n");
            printf("You will need to use the following arguments:\n");
            printf("\t-b:\t List of \"Bad lettters\"\n");
            printf("\t-k:\t Known Letters, Seperated by an understore__K__\n");
            printf("\t-p:\t List of letters that are in the word but the position is unknown\n\n");
            return 0;
        }
        if (strcmp(argv[i], "-b") == 0) {
            badLetters = argv[i + 1];  
        }
        if (strcmp(argv[i], "-k") == 0) {
            int j = 0;
            for (j; j < strlen(argv[i + 1]); j++) {
                char* a = argv[i + 1];
                KnownLetters[j] = a[j];
            }
        }
        if (strcmp(argv[i], "-p") == 0) {
            PossibleLetters = argv[i + 1];
            /*int j = 0;
            for (j; j < PossibleLetters.length(); j++) {
                cout << PossibleLetters[j] << "\n";
            }*/
        }
    }
    return 0;
}

void PopulateVector(vector<string>& Wordbase) {
    string line;
    ifstream myfile("words.txt");
    if (myfile.is_open())
     {
         while (getline (myfile,line) )
         {
             Wordbase.push_back(line);
         }
         myfile.close();
     }else cout << "Unable to open file";
}

void CleanVector(vector<string>& Wordbase, string& badLetters, string& PossibleLetters, nlohmann::json& Known_Positions) {
    string temp;

    //Remove words with "Bad" Letters from the wordlist
     for (char i : badLetters) {
         for (auto it = Wordbase.begin(); it != Wordbase.end(); it++) {
             temp = *it;
             if (temp.find((char)toupper(i)) != std::string::npos) {
                 Wordbase.erase(it--);
             }
         }
     }
    
     //Remove Words that don't have the possible letters from wordlist
     for (char i : PossibleLetters) {
         for (auto it = Wordbase.begin(); it != Wordbase.end(); it++) {
             temp = *it;
             if (temp.find((char)toupper(i)) == std::string::npos) {
                 Wordbase.erase(it--);
             }
         }
     }

     //Remove Words that don't have the right letters in the right positions
     for (int i = 0; i < Known_Positions.size(); i++) {
         cout << PossibleLetters[i] << '\n';
     }
}


int main(int argc, char* argv[]) {
    vector<string> Wordbase;
    string badLetters;
    string PossibleLetters;
    nlohmann::json Known_Positions;

    CheckArguments(argc, argv, badLetters, PossibleLetters, Known_Positions);
    cout << Known_Positions << '\n';
    PopulateVector(Wordbase);
    CleanVector(Wordbase, badLetters, PossibleLetters, Known_Positions);
  /*  for (string i : Wordbase) {
        cout << i << '\n';
    }*/

    return 0;
}
