#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;


class WordFind {
private:
    void checkWord(const string &tmp, int i, int j, unordered_map<string, pair<int, int>> &dict) const {
        if(dict.find(tmp) == dict.end()) {
                dict[tmp] = make_pair(i, j);
        } else {
            pair<int, int> tmpTuple = dict[tmp];
            int key = tmpTuple.first, value = tmpTuple.second;

            if(i < key)
                dict[tmp] = make_pair(i, j);
            else if(i == key) {
                if(j < value)
                    dict[tmp] = make_pair(i, j);
            }
        }
    }

    void findMatch(vector<string> grid, int i, int j, unordered_map<string, pair<int, int>> &dict) {
        auto wordSize = grid[i].size();
        string tmp;

        for(int cur = j; cur < wordSize; cur++) {
            tmp = grid[i].substr(static_cast<unsigned long>(j), static_cast<unsigned long>(cur - j + 1));
            checkWord(tmp, i, j, dict);
        }

        tmp = "";
        for(int cur = i; cur < grid.size(); cur++) {
            tmp += grid[cur][j];
            checkWord(tmp, i, j, dict);
        }

        tmp = "";
        for(int row = i, col = j; row < grid.size() && col < wordSize; row++, col++) {
            tmp += grid[row][col];
            checkWord(tmp, i, j, dict);
        }

    }

public:
    vector<string> findWords(vector<string> grid, vector<string> wordList) {
        vector<string> results;
        unordered_map<string, pair<int, int>> dict;

        // iterate over each string of the vector
        for (int i = 0; i < grid.size(); i++) {
            // iterate over char of the string
            for(int j = 0; j < grid[i].size(); j++) {
                findMatch(grid, i, j, dict);
            }
        }

        for (const auto &i : wordList) {
            if(dict.find(i) == dict.end()) {
                results.emplace_back("");
            } else {
                pair<int, int> val = dict[i];
                results.emplace_back(to_string(val.first) + " " + to_string(val.second));
            }
        }

        return results;
    }
};