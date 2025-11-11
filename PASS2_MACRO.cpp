#include <bits/stdc++.h>
using namespace std;

// Utility: split tokens by space or comma
vector<string> split(string s) {
    vector<string> t;
    string temp="";
    for(char c : s) {
        if(c==' ' || c==',') {
            if(!temp.empty()) t.push_back(temp);
            temp="";
        } else temp+=c;
    }
    if(!temp.empty()) t.push_back(temp);
    return t;
}

int main() {

    // ---------------- INPUT MNT ----------------
    int m;
    cout << "Enter number of macros: ";
    cin >> m;

    vector<string> MNT_name(m);
    vector<int> MNT_pntab(m), MNT_kp(m), MNT_pp(m), MNT_mdtp(m), MNT_kpdtp(m);

    for(int i=0;i<m;i++){
        cout << "Enter MNT entry (name pp kp mdtp kpdtp): ";
        cin >> MNT_name[i] >> MNT_pp[i] >> MNT_kp[i] >> MNT_mdtp[i] >> MNT_kpdtp[i];
    }

    // ---------------- INPUT PNTAB ----------------
    int p;
    cout << "\nEnter PNTAB size: ";
    cin >> p;

    vector<string> PNTAB(p+1);
    cout << "Enter index and parameter name:\n";
    for(int i=1;i<=p;i++){
        int idx; string name;
        cin >> idx >> name;
        PNTAB[idx] = name;
    }

    // ---------------- INPUT KPDTAB ----------------
    int k;
    cout << "\nEnter KPDTAB size: ";
    cin >> k;

    vector<pair<string,string>> KPDTAB(k+1);
    cout << "Enter parameter and default value:\n";
    for(int i=1;i<=k;i++){
        cin >> KPDTAB[i].first >> KPDTAB[i].second;
    }

    // ---------------- INPUT MDT ----------------
    int mdtsize;
    cout << "\nEnter MDT size: ";
    cin >> mdtsize;

    cin.ignore();
    vector<string> MDT(mdtsize+1);
    cout << "Enter MDT lines:\n";
    for(int i=1;i<=mdtsize;i++){
        getline(cin, MDT[i]);
    }

    // ---------------- INPUT SOURCE PROGRAM ----------------
    cout << "\nEnter source code (type END to stop):\n";
    vector<string> source;
    while(true){
        string line;
        getline(cin,line);
        if(line=="END") break;
        if(line.size()>0) source.push_back(line);
    }

    cout << "\n======= EXPANDED OUTPUT =======\n";

    // ---------------- PROCESS SOURCE ----------------
    for(string line : source){

        vector<string> tokens = split(line);

        // If not macro call → print as-is
        bool isMacro = false;
        int mid = -1;

        for(int i=0;i<m;i++){
            if(tokens[0] == MNT_name[i]){
                isMacro = true;
                mid = i;
                break;
            }
        }

        if(!isMacro){
            cout << line << "\n";
            continue;
        }

        // ---------------- MACRO CALL FOUND ----------------
        int pp = MNT_pp[mid];
        int kp = MNT_kp[mid];
        int mdtp = MNT_mdtp[mid];
        int kpdtp = MNT_kpdtp[mid];

        vector<string> ALA(p+1, "");

        // fill positional parameters
        int ip = 1;
        for(int i=1;i<=pp;i++){
            ALA[i] = tokens[ip++];
        }

        // fill keyword parameters or defaults
        for(int i=1;i<=kp;i++){
            string pname = KPDTAB[kpdtp + i - 1].first;
            string defval = KPDTAB[kpdtp + i - 1].second;

            string value = defval;
            if(ip < tokens.size()){
                string t = tokens[ip++];
                if(t.find('=') != string::npos){
                    value = t.substr(t.find('=')+1);
                }
            }

            ALA[pp + i] = value;
        }

        // ----------- EXPAND FROM MDT -----------

        int idx = mdtp;
        while(MDT[idx] != "MEND"){
            string temp = MDT[idx];

            // replace (P,n)
            for(int i=1;i<=p;i++){
                string t = "(P," + to_string(i) + ")";
                size_t pos = temp.find(t);
                if(pos != string::npos){
                    temp.replace(pos, t.length(), ALA[i]);
                }
            }

            cout << temp << "\n";
            idx++;
        }
    }

    cout << "======= END =======\n";
}
