#include <bits/stdc++.h>
using namespace std;

// Split a line by space or comma
vector<string> split(string s) {
    string temp = "";
    vector<string> res;
    for (char c : s) {
        if (c == ' ' || c == '\t' || c == ',') {
            if (!temp.empty()) res.push_back(temp);
            temp = "";
        } else temp += c;
    }
    if (!temp.empty()) res.push_back(temp);
    return res;
}

int main() {

    // MOT: mnemonics with size
    map<string, pair<string,int>> MOT = {
        {"ADD", {"IS", 1}},
        {"SUB", {"IS", 1}},
        {"MOVER", {"IS", 1}},
        {"MOVEM", {"IS", 1}},
        {"MULT", {"IS", 2}},
        {"COMP", {"IS", 1}},
        {"BC", {"IS", 1}},
        {"DIV", {"IS", 1}},
        {"READ", {"IS", 1}},
        {"PRINT", {"IS", 1}}
    };

    // POT: pseudo ops (AD)
    set<string> AD = {"START","END","LTORG","ORIGIN","EQU"};

    // DS / DC
    set<string> DL = {"DS","DC"};

    map<string,int> SYMTAB;
    vector<pair<string,int>> LITTAB;   // literal & assigned address
    vector<int> POOLTAB;
    POOLTAB.push_back(0);

    vector<string> IC;

    int LC = 0;
    string line;

    cout << "Enter assembly program (type END to stop):\n";

    while (true) {
        getline(cin, line);
        if (line.size() == 0) continue;

        vector<string> t = split(line);

        if (t[0] == "END") {
            // assign literals at end
            for (int i = POOLTAB.back(); i < LITTAB.size(); i++) {
                LITTAB[i].second = LC++;
            }
            break;
        }

        int idx = 0;

        // ---------- LABEL ----------
        if (t.size() > 1 && MOT.find(t[0]) == MOT.end() &&
            AD.find(t[0]) == AD.end() && DL.find(t[0]) == DL.end()) 
        {
            SYMTAB[t[0]] = LC;
            idx = 1;
        }

        // ---------- START ----------
        if (t[idx] == "START") {
            LC = stoi(t[idx+1]);
            IC.push_back("(AD,01) (C," + t[idx+1] + ")");
            continue;
        }

        // ---------- ORIGIN ----------
        // if (t[idx] == "ORIGIN") {
        //     LC = stoi(t[idx+1]);
        //     IC.push_back("(AD,03) (C," + t[idx+1] + ")");
        //     continue;
        // }
        if (t[idx] == "ORIGIN") {
            string expr = t[idx+1];

            size_t plus = expr.find('+');
            size_t minus = expr.find('-');

            if (plus != string::npos) {
                string symbol = expr.substr(0, plus);
                int offset = stoi(expr.substr(plus+1));
                LC = SYMTAB[symbol] + offset;
            }
            else if (minus != string::npos) {
                string symbol = expr.substr(0, minus);
                int offset = stoi(expr.substr(minus+1));
                LC = SYMTAB[symbol] - offset;
            }
            else {
                LC = stoi(expr);
            }

            continue;
        }


        // ---------- EQU ----------
        if (t[idx] == "EQU") {
            SYMTAB[t[0]] = SYMTAB[t[idx+1]];
            continue;
        }

        // ---------- LTORG ----------
        if (t[idx] == "LTORG") {
            for (int i = POOLTAB.back(); i < LITTAB.size(); i++) {
                LITTAB[i].second = LC++;
            }
            POOLTAB.push_back(LITTAB.size());
            IC.push_back("(AD,05)");
            continue;
        }

        // ---------- DS ----------
        if (t[idx] == "DS") {
            SYMTAB[t[0]] = LC;
            IC.push_back("(DL,02) (C," + t[idx+1] + ")");
            LC += stoi(t[idx+1]);
            continue;
        }

        // ---------- DC ----------
        if (t[idx] == "DC") {
            SYMTAB[t[0]] = LC;
            IC.push_back("(DL,01) (C," + t[idx+1] + ")");
            LC++;
            continue;
        }

        // ---------- Instruction (IS) ----------
        if (MOT.count(t[idx])) {
            string mnem = t[idx];

            string ic = "(IS," + MOT[mnem].first + ") ";

            // operand 1
            string op1 = t[idx+1];

            if (op1[0] == '=') {
                LITTAB.push_back({op1, -1});
                ic += "(L," + to_string(LITTAB.size()) + ") ";
            }
            else if (SYMTAB.count(op1)) {
                ic += "(S," + to_string(SYMTAB[op1]) + ") ";
            }

            // operand 2 (if exists)
            if (t.size() > idx+2) {
                string op2 = t[idx+2];
                if (op2[0] == '=') {
                    LITTAB.push_back({op2, -1});
                    ic += "(L," + to_string(LITTAB.size()) + ")";
                }
                else if (SYMTAB.count(op2)) {
                    ic += "(S," + to_string(SYMTAB[op2]) + ")";
                }
            }

            IC.push_back(ic);
            LC += MOT[mnem].second;
        }
    }

    // ---------------- PRINT TABLES ----------------

    cout << "\n======================= SYMBOL TABLE =======================\n";
    for (auto &x : SYMTAB)
        cout << x.first << " = " << x.second << "\n";

    cout << "\n======================= LITERAL TABLE ======================\n";
    for (int i = 0; i < LITTAB.size(); i++)
        cout << i+1 << " : " << LITTAB[i].first << " = " << LITTAB[i].second << "\n";

    cout << "\n======================= POOL TABLE =========================\n";
    for (int i : POOLTAB)
        cout << i << "\n";

    cout << "\n======================= INTERMEDIATE CODE ==================\n";
    for (string s : IC)
        cout << s << "\n";

    return 0;
}
