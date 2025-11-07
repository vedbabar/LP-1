#include<bits/stdc++.h>
using namespace std;

struct Node{
    int page;
    Node* prev;
    Node* next;
    Node(int p){
        page=p;
        next=NULL;
        prev=NULL;
    }
};

class LRU{
public:
    int capacity;
    Node* head,*tail;
    unordered_map<int, Node*> mp;
    LRU(int cap){
        capacity=cap;
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
    }
    void removeNode(Node* node){
        Node *p = node->prev;
        Node *n = node->next;
        p->next = n;
        n->prev = p;
    }
    // function to move the node to head ( as recently used )
     void addToFront(Node* node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    void insertPage(int page){
        if(mp.count(page)){
            cout << "Page " << page << " -> HIT\n";
            Node* node = mp[page];
            removeNode(node);
            addToFront(node);
            return;
        }
        cout << "Page " << page << " -> MISS\n";
        if(mp.size() == capacity){
            Node* lru = tail->prev;
            cout << "Removing LRU page: " << lru->page << "\n";
            mp.erase(lru->page);
            removeNode(lru);
            delete lru;
        }
        Node* newNode = new Node(page);
        addToFront(newNode);
        mp[page] = newNode;
    }
    void display(){
        cout << "Frames: ";
        Node* temp = head->next;
        while(temp != tail){
            cout << temp->page << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

int main(){
    LRU lru(3);
    int arr[] = {1, 2, 3, 1, 4, 5};
    int n = 6;

    for(int i=0; i<n; i++){
        lru.insertPage(arr[i]);
        lru.display();
    }

    return 0;
}
