#include<bits/stdc++.h>
using namespace std;

struct Process{
    int at,wt,ct,bt,tat,pid,pr;
};

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<Process>p(n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        cout<<"Enter arrival time: ";
        cin>>p[i].at;
        cout<<"Enter burst time: ";
        cin>>p[i].bt;
        cout<<"Enter priority: (lower number is higher priority)";
        cin>>p[i].pr;
    }
    vector<bool>done(n,false);
    int completed=0;
    int time=0;
    sort(p.begin(),p.end(),[](Process a,Process b){
        return a.at < b.at;
    });
    while(completed<n){
        int priority=INT_MAX;
        int idx=-1;
        for(int i=0;i<n;i++){
            if(!done[i] && p[i].at<=time){
                if(p[i].pr<priority){
                    priority=p[i].pr;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            time++;
            continue;
        }
        time+=p[idx].bt;
        p[idx].ct=time;
        p[idx].tat=p[idx].ct-p[idx].at;
        p[idx].wt=p[idx].tat-p[idx].bt;
        done[idx]=true;
        completed++;
    }
    sort(p.begin(), p.end(), [](Process a, Process b){
        return a.pid < b.pid; // print in original ID order
    });
    cout<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n";
    for(int i=0;i<n;i++){
        cout<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
    }
}
