#include <iostream>
#include <fstream>
#include "../split_custom.h"
#include "cmath"

using std::fstream;
using std::printf;
using std::cerr;
using std::stoi;

vector<int> parse_str_to_num (string str) {
    vector<int> numsInt;
    vector<string> numsStr = split(str, ' ');

    for (const string &s : numsStr) {
        if (s == "") {}
        else {
            numsInt.push_back(stoi(s));
        }
    }
    return numsInt;
}

struct card {
    unsigned number;
    unsigned instances;
    unsigned matches;
};

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./program file" << endl;
        return -1;
    }

    fstream input;
    input.open(argv[1]);

    string line;
    unsigned totalPoints;
    vector<int> matches;
    vector<card> cards;
    while (getline(input,line)) {
        vector<string> split0 = split(line, ':');
        //unsigned index = stoi(split(split0[0],' ')[1]);

        string points = split0[1];
        vector<string> split1 = split(points, '|');
        string winningNumStr = split1[0], possibleNumStr = split1[1];

        vector<int> winningNumInt = parse_str_to_num(winningNumStr);
        vector<int> possibleNumInt = parse_str_to_num(possibleNumStr);

        unsigned cardPoints = 0;
        int matchingCount = count_if(possibleNumInt.begin(), possibleNumInt.end(), [&winningNumInt](int i){
            return find(winningNumInt.begin(), winningNumInt.end(), i) != winningNumInt.end();
                });

        if(matchingCount > 0)
            cardPoints = pow(2, matchingCount-1);

        matches.push_back(matchingCount);
        totalPoints += cardPoints;

    }

    for(unsigned i = 0; i < matches.size(); ++i) {
        card c;
        c.matches = matches[i];
        c.number = i + 1;
        c.instances = 1;
        cards.push_back(c);
    }


    for(unsigned i = 0; i < cards.size(); ++i) {
        cout << "Card Number: " <<  cards[i].number << " | ";
        for (unsigned j = 0; j < cards[i].instances; ++j) {
            cout << "Instance number: " << j + 1 << " | ";
            for (unsigned k = cards[i].number; k < cards[i].matches + cards[i].number; k++) {
                cards[k].instances += 1;
                cout << "Updated card: " << cards[k].number << " & card instance " << cards[k].instances << "  |||  ";
            }
            cout << endl;
        }
        cout << endl;
    }

    unsigned n;
    for (const auto &c: cards) {
        n += c.instances;
    }

    cout << n << endl;

    return 0;
}


