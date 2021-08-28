#include<bits/stdc++.h>
using namespace std;
int main(){
    int num_T,num_N;
        vector<pair<string,set<vector<string>>>> productions;
        unordered_map<string,unordered_set<string>> firstSets;
        unordered_map<string,unordered_set<string>> followSets;
        unordered_map<string,int> N_idx;
        unordered_map<int,string> idx_N;
        unordered_map<int,string> idx_T;
        unordered_map<string,int> T_idx;
        ifstream infile( "GrammarLL.txt" );
        string str;
        infile>>str;
        num_N = stoi(str);
        for(int i=0;i<num_N;i++){
            infile>>str;
            N_idx[str] = i;
            idx_N[i] = str;
        }
        infile>>str;
        num_T = stoi(str);
        for(int i=-0;i<num_T;i++){
            infile>>str;
            T_idx[str] = i;
            idx_T[i] = str;
        }
        T_idx["$"] = num_T;
        idx_T[num_T] = "$";
        T_idx["#"] = num_T+1;
        idx_T[num_T+1] = "#";
        for(int i=0;i<num_N;i++){
            infile>>str;
            pair<string,set<vector<string>>> p;
            //cout<<(str)<<endl;
            p.first = str;
            int t;
            infile>>str;
            t = stoi(str);
            while(t--){
                int t1;
                infile>>str;
                t1 = stoi(str);
                vector<string> t1_v;
                while(t1--){
                    infile>>str;
                    t1_v.push_back(str);
                }
                p.second.insert(t1_v);
            }
            productions.push_back(p);
        }
        cout<<"--------------------"<<endl;
        for(int i=0;i<num_N;i++){
            cout<<productions[i].first<<"->";
            for(auto itr:productions[i].second){
                for(auto itr1:(itr)){
                    cout<<(itr1);
                }cout<<"|";
            }cout<<endl;
        }
        cout<<"--------------------"<<endl;
        for(auto x: idx_T){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"--------------------"<<endl;
        for(auto x: idx_N){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"--------------------"<<endl;
        for(auto x: T_idx){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"--------------------"<<endl;
        for(auto x: N_idx){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"--------------------"<<endl;
        ifstream infile2("First-Follow.txt");
        for(int i=0;i<num_N;i++){
           string A;
           infile2>>A;
           firstSets[A]={};
           int t;
           infile2>>str;
           t = stoi(str);
           while(t--){
               infile2>>str;
               firstSets[A].insert(str);
           }
        }
        for(int i=0;i<num_N+num_T+1;i++){
           string A;
           infile2>>A;
           followSets[A]={};
           int t;
           infile2>>str;
           t = stoi(str);
           while(t--){
               infile2>>str;
               followSets[A].insert(str);
           }
        }
        for(auto x: firstSets){
            cout<<x.first<<" ";
            for(auto y:x.second){
                cout<<y<<" ";
            }cout<<endl;
        }
        cout<<"--------------------"<<endl;
        for(auto x: followSets){
            cout<<x.first<<" ";
            for(auto y:x.second){
                cout<<y<<" ";
            }cout<<endl;
        }
        cout<<"--------------------"<<endl;
}