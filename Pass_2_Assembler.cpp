#include <bits/stdc++.h>
using namespace std;

vector<string>split(string s){
    stringstream ss(s);
    string w;
    vector<string>out;
    while(ss>>w) out.push_back(w);
    return out;
}
int main() {
    // ✅ SYMTAB uses index → address
    map<string,int> SYMTAB;
    int n1=0;
    cout<<"Enter symbol table size: "<<endl;
    cin>>n1;
    for(int i=0;i<n1;i++){
        string ind;
        int add;
        cout<<"Enter symbol index and address: "<<endl;
        cin>>ind>>add;
        SYMTAB[ind]=add;
    }
    // ✅ LITTAB uses literal index → address
    map<string,int> LITTAB;
    int n2=0;
    cout<<"Enter literal table size: "<<endl;
    cin>>n2;
    for(int i=0;i<n2;i++){
        string ind;
        int add;
        cout<<"Enter literal index and address: "<<endl;
        cin>>ind>>add;
        LITTAB[ind]=add;
    }
    // vector<string> IC = {
    //     "IS,04 RG,1 S,X",
    //     "IS,01 RG,2 L,1",
    //     "DL,01 C,7",
    //     "AD,02"
    // };
        // ✅ Intermediate Code
    vector<string> IC;
    cout << "Enter Intermediate Code (type ENDIC to stop):\n";
    while (true) {
        string line;
        getline(cin, line);
        if (line == "ENDIC") break;  // stop IC input
        if (line.size() == 0) continue;
        IC.push_back(line);
    }
    cout << "\nFINAL MACHINE CODE:\n";
    for (string line : IC) {
        vector<string> t = split(line);
        if (t.empty()) continue;
        string out = "";
        if (t[0].substr(0,2) == "AD" || t[0].substr(0,2) == "DL") continue;
        for (string token : t) {
            int pos = token.find(',');
            string type = token.substr(0, pos);
            string val  = token.substr(pos+1);
            if (type == "IS" || type == "RG") {
                out += val + " ";
            }
            else if (type == "S") {
                out += to_string(SYMTAB[val]) + " ";
            }
            else if (type == "L") {
                out += to_string(LITTAB[val]) + " ";
            }
            else if (type == "C") {
                out += val + " ";
            }
        }
        cout << out << "\n";
    }
}
