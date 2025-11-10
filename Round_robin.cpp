#include<bits/stdc++.h>
using namespace std;

struct Process{
    int at,wt,ct,bt,tat,pid,remaining;
};

int main(){
    int n;
    cout<<"Enter number of processes: "<<endl;
    cin>>n;
    int tq;
    cout<<"Enter time quantum: "<<endl;
    cin>>tq;
    vector<Process>p(n);
    vector<bool>inq(n,false);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        cout<<"Enter arrival time: "<<endl;
        cin>>p[i].at;
        cout<<"Enter burst time: "<<endl;
        cin>>p[i].bt;
        p[i].remaining=p[i].bt;
    }
    int completed=0;
    int time=0;
    queue<int>q;
    while(completed<n){
        for(int i=0;i<n;i++){
            if(!inq[i] && p[i].at<=time && p[i].remaining>0){
                q.push(i);
                inq[i]=true;
            }
        }
        if(q.empty()){
            time++;
            continue;
        }
        int idx=q.front();
        q.pop();
        int execution_time=min(tq,p[idx].remaining);
        time+=execution_time;
        p[idx].remaining-=execution_time;
        for(int i=0;i<n;i++){
            if(!inq[i] && p[i].at<=time && p[i].remaining>0){
                q.push(i);
                inq[i]=true;
            }
        }
        if(p[idx].remaining==0){
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            completed++;
        }
        else{
            q.push(idx);
        }
    }
    cout<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n";
    for(int i=0;i<n;i++){
        cout<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
    }
}
