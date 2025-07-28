#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Share {
    int x;
    string word;
    int y;
};

void trimLine(string& line) {
    line.erase(remove(line.begin(), line.end(), '"'), line.end());
    line.erase(remove(line.begin(), line.end(), ','), line.end());
    line.erase(remove(line.begin(), line.end(), '{'), line.end());
    line.erase(remove(line.begin(), line.end(), '}'), line.end());
    line.erase(remove(line.begin(), line.end(), '['), line.end());
    line.erase(remove(line.begin(), line.end(), ']'), line.end());
}

vector<Share> parseJSON(const string& filename) {
    ifstream file(filename);
    vector<Share> shares;
    string line;
    Share current;

    while (getline(file, line)) {
        trimLine(line);
        stringstream ss(line);
        string key, value;

        while (getline(ss, key, ':') && getline(ss, value)) {
            if (key.find("x") != string::npos) {
                current.x = stoi(value);
            } else if (key.find("word") != string::npos) {
                current.word = value;
            } else if (key.find("y") != string::npos) {
                current.y = stoi(value);
                shares.push_back(current); // Once x, word, y are filled
            }
        }
    }

    return shares;
}

void printShares(const vector<Share>& shares) {
    for (const auto& s : shares) {
        cout << "x: " << s.x << ", word: " << s.word << ", y: " << s.y << endl;
    }
}

int main() {
    string filename = "data.json";
    vector<Share> shares = parseJSON(filename);
    printShares(shares);
    return 0;
}
