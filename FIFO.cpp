#include<bits/stdc++.h>
using namespace std;

class FIFO{
public:
    int capacity;
    queue<int>q;
    unordered_set<int>st;
    FIFO(int cap){
        capacity=cap;
    }
    void insertPage(int page){
        if(st.find(page)!=st.end()){
            cout<<"Page "<<page<<" -> HIT"<<endl;
            return;
        }
        cout<<"Page "<<page<<" -> MISS"<<endl;
        if(st.size()==capacity){
            int removed=q.front();
            q.pop();
            st.erase(removed);
            cout<<"Removed oldest page: "<<removed<<endl;
        }
        q.push(page);
        st.insert(page);
    }
    void display(){
        queue<int>temp=q;
        cout<<"Frames: "<<endl;
        while(!temp.empty()){
            cout<<temp.front()<<" ";
            temp.pop();
        }
        cout<<endl;
    }
};

int main() {
    FIFO fifo(3);

    int pages[] = {1, 2, 3, 1, 4, 5};
    int n = 6;

    for(int i = 0; i < n; i++) {
        fifo.insertPage(pages[i]);
        fifo.display();
    }

    return 0;
}
