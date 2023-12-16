#ifndef CUSTOM_FUNCS
#include <iostream>
#include <string>
#include <vector>
#define CUSTOM_FUNCS
#endif

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> split(string str, char separator) {
    vector<string> splits;
    unsigned lastLocatedSeparatorIndex = 0;
    for (unsigned i = 0; i < str.size(); ++i) {
        if (str[i] == separator) {
            string split = str.substr(lastLocatedSeparatorIndex,
                                      i - lastLocatedSeparatorIndex);
            splits.push_back(split);
            lastLocatedSeparatorIndex = i + 1;
        }
    }

    if (lastLocatedSeparatorIndex != str.size())
        splits.push_back(str.substr(lastLocatedSeparatorIndex, str.size()));

    return splits;
}

vector<string> split(string str, string separator) {
    vector<string> splits;
    unsigned lastLocatedSeparatorIndex = 0;
    for (unsigned i = 0; i < str.size(); ++i) {
        for (unsigned j = 0; j < separator.size(); ++j) {
            if (str[i + j] != separator[j])
                goto outerLoop;
            if (j == separator.size() - 1) {
                string split = str.substr(lastLocatedSeparatorIndex,
                                          i + j - lastLocatedSeparatorIndex);
                splits.push_back(split);
                lastLocatedSeparatorIndex = i + j + 1;
            }
        }
    outerLoop:
        continue;
    }

    if (lastLocatedSeparatorIndex != str.size())
        splits.push_back(str.substr(lastLocatedSeparatorIndex, str.size()));

    return splits;
}

template <typename T>
void testSplit(vector<T> splStr, string testValue = "") {
    for (const auto &s : splStr)
        cout << s << testValue << endl;
}

template <typename T>
vector<T> slice(const vector<T> &v, size_t e, size_t s = 0) {
    if (s > v.size() || e > v.size())
        throw std::out_of_range("start or end are larger than the vector");

    return vector<T>(v.begin() + s, v.begin() + e);
}
