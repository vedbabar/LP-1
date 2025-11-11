#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> alive(n+1, 1);

    cout << "Enter failed coordinator ID: ";
    int failed;
    cin >> failed;
    alive[failed] = 0;

    cout << "Enter initiator process: ";
    int start;
    cin >> start;

    cout << "\nRING ELECTION ALGORITHM\n";

    vector<int> token;
    int current = start;

    do {
        if(alive[current])
            token.push_back(current);

        current++;
        if(current > n) current = 1;

    } while(current != start);

    cout << "Election token collected: ";
    for(int x : token) cout << x << " ";
    cout << endl;

    int coordinator = *max_element(token.begin(), token.end());
    cout << "New coordinator: " << coordinator << endl;

    cout << "Coordinator message circulated around ring.\n";
    return 0;
}
