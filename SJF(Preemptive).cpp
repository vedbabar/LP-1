#include<bits/stdc++.h>
using namespace std;


struct Process{
    int pid,wt,bt,at,tat,ct,rt;
};

int main(){
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival time for P" << i+1 << ": ";
        cin >> p[i].at;
        cout << "Burst time for P" << i+1 << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
    }
    sort(p.begin(),p.end(),[](Process a,Process b){
        return a.at<b.at;
    });
    vector<bool>done(n,false);
    int completed=0;
    int time=0;
    while(completed<n){
        int mini=INT_MAX;
        int idx=-1;
        for(int i=0;i<n;i++){
            if(!done[i] && p[i].at<=time){
                if(p[i].rt<mini){
                    mini=p[i].rt;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            time++;
            continue;
        }
        p[idx].rt--;
        time++;
        if(p[idx].rt==0){
            completed++;
            done[idx]=true;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
        }
    }
    sort(p.begin(), p.end(), [](Process a, Process b){
        return a.pid < b.pid; // print in original ID order
    });
    cout<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n";
    for(int i=0;i<n;i++){
        cout<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
    }
}
