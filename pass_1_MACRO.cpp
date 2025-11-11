#include <bits/stdc++.h>
using namespace std;

//function for splitting a line into words , based on space ' ' or ,
vector<string> split(string s) {
    vector<string> t;
    string temp = "";
    for (char c : s) {
        if (c == ' ' || c == ',') {
            if (!temp.empty()) t.push_back(temp);
            temp = "";
        } else temp += c;
    }
    if (!temp.empty()) t.push_back(temp);
    return t;
}

int main() {
    struct MNT_Entry {
        string name;
        int pntab_index;        // starting index in PNTAB
        int kp_count;           // number of keyword parameters
        int pp_count;           // number of positional parameters
        int mdt_index;          // starting MDT index
        int kpdt_index;         // starting KPDTAB index
    };

    vector<MNT_Entry> MNT;
    vector<string> PNTAB;
    vector<pair<string,string>> KPDTAB; // pair<pname, default_value>
    vector<string> MDT;

    int MAC_COUNT;
    cout << "Enter number of macros: ";
    cin >> MAC_COUNT;
    cin.ignore();

    for (int m = 0; m < MAC_COUNT; m++) {
        cout << "\nEnter MACRO definition " << m+1 << ":\n";
        string line;

        getline(cin, line); // MACRO line
        getline(cin, line); // prototype

        vector<string> head = split(line);

        string macroName = head[0];

        int pntab_start = PNTAB.size();
        int kpdt_start = KPDTAB.size();
        int pp_count = 0, kp_count = 0;

        // ---------------- Process Parameters ----------------
        for (int i = 1; i < head.size(); i++) {
            string p = head[i];
            size_t eq = p.find('=');

            if (eq == string::npos) {
                // positional
                PNTAB.push_back(p.substr(1));
                pp_count++;
            }
            else {
                string pname = p.substr(1, eq - 1);
                string defval = p.substr(eq + 1);
                PNTAB.push_back(pname);
                KPDTAB.push_back({pname, defval});
                kp_count++;
            }
        }

        int mdt_start = MDT.size();

        // ---------------- Read MDT ----------------
        while (true) {
            getline(cin, line);
            MDT.push_back(line);
            if (line == "MEND") break;
        }

        // ---------------- Insert into MNT ----------------
        MNT.push_back({ macroName, pntab_start, kp_count, pp_count, mdt_start, kpdt_start });
    }
    // -------------------- PRINT FINAL TABLES (Single) --------------------
    cout << "\n=============== MNT TABLE ===============\n";
    cout << "Index  Name    PP  KP  MDT_Idx  KPDT_Idx\n";
    for (int i = 0; i < MNT.size(); i++) {
        auto &x = MNT[i];
        cout << i+1 << "      " << x.name << "      "
             << x.pp_count << "   " << x.kp_count << "     "
             << x.mdt_index+1 << "        " << x.kpdt_index+1 << "\n";
    }

    cout << "\n=============== PNTAB ===============\n";
    for (int i = 0; i < PNTAB.size(); i++)
        cout << i+1 << " : " << PNTAB[i] << "\n";

    cout << "\n=============== KPDTAB ===============\n";
    for (int i = 0; i < KPDTAB.size(); i++)
        cout << i+1 << " : " << KPDTAB[i].first << " = " << KPDTAB[i].second << "\n";

    cout << "\n=============== MDT ===============\n";
    for (int i = 0; i < MDT.size(); i++)
        cout << i+1 << " : " << MDT[i] << "\n";

    return 0;
}
