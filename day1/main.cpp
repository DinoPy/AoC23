#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {
   fstream input;
   input.open("./input.txt", ios::in);
   if (!input) cout << "no file" << endl;

   string line;
   vector<vector<int> > arr;
   int index = 0;
   while (getline (input, line)) {
       vector<int> currNums;
       cout << line << endl;
       for (auto n : line) {
           if (isdigit(n))
               currNums.push_back(n - '0');
       }
       break;
       ++index;
       arr.push_back(currNums);
   }

   unsigned total = 0;
   for (auto i : arr) {
       cout << *(i.begin()) << "   " << *(i.end() - 1) << endl;
       total += (*(i.begin()) * 10 + *(i.end() - 1));
   }

   cout << total << endl;
    return 0;
}
