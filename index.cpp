#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

long long convertToDecimal(const string& value, int base) {
    long long result = 0;
    for (char ch : value) {
        int digit;
        if (isdigit(ch)) digit = ch - '0';
        else digit = tolower(ch) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

struct Share {
    int x;
    long long y;
};

long long lagrangeInterpolation(const vector<Share>& shares, int k) {
    long long secret = 0;
    for (int i = 0; i < k; ++i) {
        long double term = shares[i].y;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0.0 - shares[j].x) / (shares[i].x - shares[j].x);
            }
        }
        secret += term;
    }
    return round(secret);
}

int main() {
    ifstream file("data.json");
    string line;
    map<int, Share> shareMap;
    int n = 0, k = 0;

    while (getline(file, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        if (line.find("\"n\":") != string::npos) {
            n = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("\"k\":") != string::npos) {
            k = stoi(line.substr(line.find(":") + 1));
        } else {
            for (int i = 1; i <= 10; ++i) {
                string id = to_string(i);
                if (line.find("\"" + id + "\":") != string::npos) {
                    Share s;
                    s.x = i;
                    string baseStr, valueStr;
                    getline(file, line);
                    baseStr = line.substr(line.find(":\"") + 2);
                    baseStr = baseStr.substr(0, baseStr.find("\""));
                    getline(file, line);
                    valueStr = line.substr(line.find(":\"") + 2);
                    valueStr = valueStr.substr(0, valueStr.find("\""));

                    int base = stoi(baseStr);
                    s.y = convertToDecimal(valueStr, base);
                    shareMap[i] = s;
                }
            }
        }
    }

    vector<Share> shares;
    for (int i = 1; i <= k; ++i) {
        shares.push_back(shareMap[i]);
    }

    cout << "Parsed " << k << " shares:\n";
    for (const auto& s : shares) {
        cout << "x: " << s.x << ", y: " << s.y << endl;
    }

    long long secret = lagrangeInterpolation(shares, k);
    cout << "\nRecovered Secret: " << secret << endl;

    return 0;
}
