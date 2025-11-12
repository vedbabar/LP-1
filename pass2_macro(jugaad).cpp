#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, k;
    cout << "Enter number of positional parameters: ";
    cin >> p;
    cout << "Enter number of keyword parameters: ";
    cin >> k;

    vector<string> PNTAB(p + k + 1);
    vector<pair<string, string>> KPDTAB(k + 1);
    vector<string> MDT;

    // ---------- Input PNTAB ----------
    cout << "\nEnter PNTAB (index name):\n";
    for (int i = 1; i <= p + k; i++) {
        int idx; string name;
        cin >> idx >> name;
        PNTAB[idx] = name;
    }

    // ---------- Input KPDTAB ----------
    cout << "\nEnter KPDTAB (param value):\n";
    for (int i = 1; i <= k; i++) {
        cin >> KPDTAB[i].first >> KPDTAB[i].second;
    }

    // ---------- Input MDT ----------
    cin.ignore();
    cout << "\nEnter MDT lines (end with MEND):\n";
    while (true) {
        string line;
        getline(cin, line);
        if (line == "MEND") break;
        MDT.push_back(line);
    }

    // ---------- Input macro call ----------
    string macroCall;
    cout << "\nEnter macro call (e.g. INCR A,B=5):\n";
    getline(cin, macroCall);

    // ---------- Extract actual arguments ----------
    vector<string> args;
    string temp = "";
    for (char c : macroCall) {
        if (c == ' ' || c == ',') {
            if (!temp.empty()) args.push_back(temp), temp = "";
        } else temp += c;
    }
    if (!temp.empty()) args.push_back(temp);

    string macroName = args[0];
    args.erase(args.begin());

    // ---------- Build ALA (Actual List Array) ----------
    map<string, string> ALA;
    int posIndex = 1;

    // positional args first
    for (int i = 0; i < args.size(); i++) {
        if (args[i].find('=') == string::npos) {
            ALA[PNTAB[posIndex++]] = args[i];
        }
    }

    // keyword args
    for (int i = 0; i < args.size(); i++) {
        if (args[i].find('=') != string::npos) {
            string name = args[i].substr(0, args[i].find('='));
            string val = args[i].substr(args[i].find('=') + 1);
            ALA[name] = val;
        }
    }

    // Fill default values if not provided
    for (int i = 1; i <= k; i++) {
        if (ALA.find(KPDTAB[i].first) == ALA.end()) {
            ALA[KPDTAB[i].first] = KPDTAB[i].second;
        }
    }

    // ---------- Macro Expansion ----------
    cout << "\nExpanded Macro Code:\n";
    for (string line : MDT) {
        for (int i = 1; i <= p + k; i++) {
            string token = "(P," + to_string(i) + ")";
            size_t pos = line.find(token);
            if (pos != string::npos) {
                line.replace(pos, token.size(), ALA[PNTAB[i]]);
            }
        }
        cout << line << "\n";
    }

    return 0;
}
