#include <iostream>
#include "fstream"
#include "../split_custom.h"

using namespace std;

const int MAXRED = 12;
const int MAXGREEN = 13;
const int MAXBLUE = 14;


int main (int argc, char *argv[]) {
    fstream input;
    input.open("./input.txt", ios::in);

    string line;
    int total = 0, totalPowMin = 0;
    while(getline(input, line)) {
        bool isGamePossible = true;
       vector<string> splitStr =  split(line, ':');
       int minRed = 0, minGreen = 0, minBlue = 0;

       // parse game number
       string gameNum;
       for (const auto &c : splitStr[0]) {
            if (isdigit(c))
                gameNum += c;
       }
       int gameNumDigit = stoi(gameNum);

       // extract colors and digits
       vector<string> split2 = split(splitStr[1], ';');
        for (const string &str : split2) {
           vector<string> split3 = split(str, ',');
           for (const auto &val : split3) {
               // get the number of the roll
               string rollNumber;
               for (const auto &c : val) {
                    if (isdigit(c))
                        rollNumber += c;
               }
               int rollNumInt = stoi(rollNumber);
               // get the color of the roll
                vector<string> split4 = split(val, ' ');
                if ("red" == split4[2] && rollNumInt > MAXRED) {
                    isGamePossible = false;
                }
                if ("green" == split4[2] && rollNumInt > MAXGREEN) {
                    isGamePossible = false;
                }
                if ("blue" == split4[2] && rollNumInt > MAXBLUE) {
                    isGamePossible = false;
                }

                if ("red" == split4[2]) {
                    if (rollNumInt > minRed)
                        minRed = rollNumInt;
                }
                if ("green" == split4[2]) {
                    if (rollNumInt > minGreen)
                        minGreen = rollNumInt;
                }
                if ("blue" == split4[2]) {
                    if (rollNumInt > minBlue)
                        minBlue = rollNumInt;
                }

           }

        }

        if (isGamePossible) {
            total += gameNumDigit;
        }
        int prodMinRGB = minRed * minGreen * minBlue;
        totalPowMin += prodMinRGB;
        cout << "minRed " << minRed << " minGreen " << minGreen << " minBlue " << minBlue << " prod:  " << prodMinRGB <<  endl;

    }

    cout << total << endl;
    cout << totalPowMin << endl;
    return 0;
}
