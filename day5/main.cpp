#include "../split_custom.h"
#include <fstream>
#include <iostream>
#include <sstream>

using std::cerr;
using std::fstream;

typedef vector<int> seeds;

struct map {
    unsigned long destination;
    unsigned long source;
    unsigned long range;
};

struct mapping {
    vector<map> sts; // seed to soil
    vector<map> stf; // soil to fertilizer
    vector<map> ftw; // fertilizer to water
    vector<map> wtl; // water to light
    vector<map> ltt; // light to temperature
    vector<map> tth; // temperature to humidity
    vector<map> htl; // humidity to location
};

vector<int> parseNumStr(string s) {
    vector<string> seedNums = split(s, ' ');
    vector<int> i;
    for (const auto &n : seedNums) {
        i.push_back(stoi(n));
    }
    return i;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./program file" << endl;
        return -1;
    }

    fstream file;
    file.open(argv[1]);

    std::stringstream s;
    s << file.rdbuf();
    string inputString = s.str();
    vector<string> blocks = split(inputString, "\n\n");

    string seed = blocks[0];
    string seedNums = split(seed, ": ")[1];
    vector<int> seeds = parseNumStr(seedNums);

    vector<string> mappings = slice(blocks, blocks.size(), 1);
    vector<vector<string>> mapNums;
    vector<int> n;
    for (const string &s : mappings) {
        vector<string> vs = split(s, '\n');
        vector<string> vm = slice(vs, vs.size(), 1);
        mapNums.push_back(vm);

        for (const int &i : seeds) {
            for (const auto &range : mapNums) {
                for (const auto &vs : range) {
                    vector<string> s = split(vs, ' ');
                    long a = stoi(s[0]), b = stoi(s[1]), c = stoi(s[2]);
                    printf("a: %ld, b: %ld, c: %ld\n", a, b, c);
                    if (b <= i && i < b + c) {
                        n.push_back(i - b + a);
                        goto br;
                    }
                }
            }
            br: {
                n.push_back(i);
           }
        }
    }

    long total = 999999999999999999;
    for (const long &x : n) {
        if (total > x)
            total = x;
    }
    cout << total << endl;
    return 0;
}
