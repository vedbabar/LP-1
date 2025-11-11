#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> alive(n+1, 1); // 1 = alive, 0 = dead

    cout << "Enter ID of coordinator: ";
    int coordinator;
    cin >> coordinator;

    cout << "Enter ID of process detecting failure: ";
    int initiator;
    cin >> initiator;

    alive[coordinator] = 0; // coordinator dead

    cout << "\nBULLY ALGORITHM\n";
    cout << "Process " << initiator << " starts election\n";

    int winner = initiator;

    for(int i = initiator + 1; i <= n; i++){
        if(alive[i]) {
            cout << "Process " << initiator 
                 << " -> Election message -> Process " << i << endl;
            cout << "Process " << i << " responds OK\n";
            winner = i; // higher ID wins
        }
    }

    cout << "\nFinal Coordinator Elected: Process " << winner << endl;
    return 0;
}

