
// NTP - Network time protocol
#include <bits/stdc++.h>
using namespace std;

int main() {
    double t1, t2, t3, t4;

    cout << "Enter t1 (client sends request): ";
    cin >> t1;

    cout << "Enter t2 (server receives request): ";
    cin >> t2;

    cout << "Enter t3 (server sends reply): ";
    cin >> t3;

    cout << "Enter t4 (client receives reply): ";
    cin >> t4;

    double offset = ((t2 - t1) + (t3 - t4)) / 2.0;
    double delay  = (t4 - t1) - (t3 - t2);

    cout << "\nClock Offset: " << offset << " ms";
    cout << "\nRound Trip Delay: " << delay << " ms\n";

    return 0;
}





// Lamport clock

#include <bits/stdc++.h>
using namespace std;

// Increment on local event
void localEvent(int &clock) {
    clock++;
    cout << "Local event -> Clock: " << clock << "\n";
}

// Send event
int sendEvent(int &clock) {
    clock++;
    cout << "Send message -> Clock: " << clock << "\n";
    return clock; // timestamp sent inside message
}

// Receive event
void receiveEvent(int &clock, int msg_ts) {
    clock = max(clock, msg_ts) + 1;
    cout << "Receive message -> Updated Clock: " << clock << "\n";
}

int main() {
    int clockA = 0, clockB = 0;

    cout << "Process A local event:\n";
    localEvent(clockA);

    cout << "\nProcess A sends message to B:\n";
    int ts = sendEvent(clockA);

    cout << "\nProcess B receives message:\n";
    receiveEvent(clockB, ts);

    cout << "\nProcess B local event:\n";
    localEvent(clockB);

    cout << "\nFinal Clocks:\n";
    cout << "Clock A = " << clockA << "\n";
    cout << "Clock B = " << clockB << "\n";

    return 0;
}
