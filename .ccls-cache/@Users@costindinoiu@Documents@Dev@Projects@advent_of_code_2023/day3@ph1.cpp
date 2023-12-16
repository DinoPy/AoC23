#include <iostream>
#include <fstream>
#include <unordered_set>
#include "../split_custom.h"

using namespace std;

namespace std {
    template <>
    struct hash<std::vector<int>> {
        size_t operator()(const std::vector<int>& v) const {
            size_t hash_value = 0;
            for (int elem : v) {
                hash_value ^= std::hash<int>()(elem) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }
            return hash_value;
        }
    };

    bool operator==(const std::vector<int>& lhs, const std::vector<int>& rhs) {
        return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
}

void readFile (int argc, char *argv[], vector<string> &file) {
    if (argc != 2) {
        cerr << "Usage: ./program file_name" << endl;
    }

    fstream input;
    input.open(argv[1]);

    string line;
    while (getline(input, line)) {
        file.push_back(line);
    }
    input.close();
}

int sum (vector<int> n) {
    int total = 0;
    cout << "default initialized total is: " << total << endl;
    for (const int &i : n) {
        cout << i << endl;
        total += i;
    }
    return total;
}

vector <string> grid;
int main (int argc, char *argv[]) {
    readFile(argc, argv, grid);

    unordered_set<vector<int> > cs;
    for (int r = 0; r < grid.size(); ++r) {
        string row = grid[r];
        for (int c = 0; c < grid[r].size(); ++c) {
            char ch = row[c];

            if (isdigit(ch) || ch == '.')
                continue;
            printf("Symbol Coords: %i:%i \n", r, c);

            for (int cr = r - 1; cr <= r + 1; ++cr) {
                for (int cc = c - 1; cc <= c + 1; ++cc) {
                    cout << cr << ":" << cc << endl;
                    if (cr < 0 || cr >= grid.size() || cc < 0 || cc >= grid[cr].size() || !isdigit(grid[cr][cc]))
                        continue;
                    int cursor = cc;
                    while (cc > 0 && isdigit(grid[cr][cursor - 1]))
                        cursor -= 1;
                    cs.insert({cr,cursor});
                }
            }
        }
    }

    cout << "---------------------------------" << endl;

    vector <int> nums;
    for (const auto &i : cs) {
        int r = i[0], c = i[1];
        string s;
        while (c < grid[r].size() && isdigit(grid[r][c])) {
            s += grid[r][c];
            c += 1;
        }
        nums.push_back(stoi(s));
    }

    int total = sum(nums);
    cout << total << endl;


    return 0;
}


/*
592
617
467
598
755
633
35
664
*/
