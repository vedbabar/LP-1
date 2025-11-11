#include <bits/stdc++.h>
using namespace std;

map<string, pair<string, int>> MOT = {
    {"MOVER", {"IS", 4}}, {"MOVEM", {"IS", 5}}, {"ADD", {"IS", 1}},
    {"SUB", {"IS", 2}}, {"MULT", {"IS", 3}}, {"BC", {"IS", 7}},
    {"STOP", {"IS", 0}}
};
map<string, pair<string, int>> POT = {
    {"START", {"AD", 1}}, {"END", {"AD", 2}}, {"LTORG", {"AD", 5}},
    {"DS", {"DL", 2}}, {"DC", {"DL", 1}}
};
map<string, int> REG = {{"AREG",1}, {"BREG",2}, {"CREG",3}, {"DREG",4}};
map<string, int> CC = {{"LT",1},{"LE",2},{"EQ",3},{"GT",4},{"GE",5},{"ANY",6}};

map<string,int> SYMTAB;
map<string,int> LITTAB_temp;
vector<pair<string,int>> LITTAB;

int LC = 0;

void processLine(const string &line, ofstream &icFile) {

    if(line.empty()) return;

    // convert to uppercase
    stringstream ss(line);
    vector<string> tokens;
    string word;
    while(ss >> word){
        for(char &c:word) c = toupper(c);
        tokens.push_back(word);
    }

    string label="", opcode="";
    vector<string> operands;

    // Whether first token is opcode or label
    if(POT.count(tokens[0]) || MOT.count(tokens[0])){
        opcode = tokens[0];
        for(int i=1;i<tokens.size();i++) operands.push_back(tokens[i]);
    } else {
        label = tokens[0];
        if(tokens.size()>1){
            opcode = tokens[1];
            for(int i=2;i<tokens.size();i++) operands.push_back(tokens[i]);
        }
    }

    // START
    if(opcode=="START"){
        LC = stoi(operands[0]);
        icFile << "    (AD,01) (C," << LC << ")\n";
        return;
    }

    // END
    if(opcode=="END"){
        icFile << "    (AD,02)\n";
        for(auto &it:LITTAB_temp){
            LITTAB.push_back({it.first,LC});
            string num = it.first.substr(2, it.first.size()-3);
            icFile << LC << " (DL,01) (C," << num << ")\n";
            LC++;
        }
        return;
    }

    // LTORG
    if(opcode=="LTORG"){
        icFile << "    (AD,05)\n";
        for(auto &it:LITTAB_temp){
            LITTAB.push_back({it.first,LC});
            string num = it.first.substr(2, it.first.size()-3);
            icFile << LC << " (DL,01) (C," << num << ")\n";
            LC++;
        }
        LITTAB_temp.clear();
        return;
    }

    // Label
    if(!label.empty()){
        SYMTAB[label] = LC;
    }

    string icLine = "";

    if(MOT.count(opcode))
        icLine += "(IS," + to_string(MOT[opcode].second) + ")";
    else if(POT.count(opcode))
        icLine += "(" + POT[opcode].first + "," + to_string(POT[opcode].second) + ")";

    for(auto &op : operands){
        if(op.find("='") != string::npos){
            if(LITTAB_temp.find(op)==LITTAB_temp.end())
                LITTAB_temp[op] = -1;
            icLine += " (L," + to_string(LITTAB_temp.size()) + ")";
        }
        else if(REG.count(op))
            icLine += " (R," + to_string(REG[op]) + ")";
        else if(CC.count(op))
            icLine += " (CC," + to_string(CC[op]) + ")";
        else{
            if(SYMTAB.find(op)==SYMTAB.end()) SYMTAB[op] = -1;
            int idx = distance(SYMTAB.begin(), SYMTAB.find(op)) + 1;
            icLine += " (S," + to_string(idx) + ")";
        }
    }

    icFile << LC << " " << icLine << "\n";

    if(opcode=="DS") LC += stoi(operands[0]);
    else LC++;
}

int main(){
    vector<string> input_lines;
    cout << "Enter assembly program (type END on its own line to finish):\n";

    string line;
    while(true){
        getline(cin, line);
        if(line.size()==0) continue;
        input_lines.push_back(line);
        if(line == "END" || line=="end" || line=="End") break;
    }

    ofstream icFile("ic.txt");
    ofstream symFile("symbols.txt");
    ofstream litFile("literals.txt");

    for(string &ln : input_lines)
        processLine(ln, icFile);

    symFile << "Symbol\tAddress\n";
    for(auto &s : SYMTAB)
        symFile << s.first << "\t" << s.second << "\n";

    litFile << "Literal\tAddress\n";
    for(auto &l : LITTAB)
        litFile << l.first << "\t" << l.second << "\n";

    cout << "\n✅ Assembler Pass-1 Completed.\n";
    cout << "✅ Generated files: ic.txt, symbols.txt, literals.txt\n";

    return 0;
}
