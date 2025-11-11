#include <bits/stdc++.h>
using namespace std;

// Function to find the page to replace using Optimal strategy
int findOptimalIndex(vector<int> &frames, vector<int> &pages, int currentPos) {
    int farthest = -1;
    int indexToReplace = -1;

    for(int i = 0; i < frames.size(); i++) {
        int j;
        for(j = currentPos + 1; j < pages.size(); j++) {
            if(frames[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }

        // Page not found in future → best to replace now
        if(j == pages.size()) return i;
    }
    return indexToReplace;
}

int main() {
    int n, capacity;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for(int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> capacity;
    vector<int> frames;   // current pages in frames
    int pageFaults = 0;
    for(int i = 0; i < n; i++) {
        int page = pages[i];
        // Check if page already in frames (HIT)
        if(find(frames.begin(), frames.end(), page) != frames.end()) {
            cout << "Page " << page << " -> HIT\n";
        }
        else {
            cout << "Page " << page << " -> MISS\n";
            pageFaults++;

            if(frames.size() < capacity) {
                frames.push_back(page);
            }
            else {
                int idx = findOptimalIndex(frames, pages, i);
                cout << "Replacing: " << frames[idx] << "\n";
                frames[idx] = page;
            }
        }
        // Display current frames
        cout << "Frames: ";
        for(int f : frames) cout << f << " ";
        cout << "\n\n";
    }
    cout << "Total Page Faults = " << pageFaults << endl;
    return 0;
}
