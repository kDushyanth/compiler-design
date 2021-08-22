#include<bits/stdc++.h>
using namespace std;
int steps = 0;
//cd lab4/18CS01009_dushyanth/q1
//pretty print the grammar
void print(unordered_map<char,vector<string>> productions){
    cout<<"--------start-------"<<endl;
    for(auto itr = productions.begin();itr!=productions.end();itr++){
        cout<<(itr->first)<<"->";
        for(int i=0;i<(itr->second).size();i++){
            if(i!=(itr->second).size()-1)cout<<(itr->second)[i]<<" | ";
            else{
                cout<<(itr->second)[i]<<endl;
            }
        }
    }
    cout<<"---------end--------"<<endl;
}
//prints two vectors x1,x2
void printOKs(vector<string> x1,vector<string> x2){
    for(auto x:x1){
        cout<<x<<"..";
    }cout<<endl;
    for(auto x:x2){
        cout<<x<<"..";
    }cout<<endl;
}
int main(){
    //grammar
    unordered_map<char,vector<string>> productions;
    cout<<"Input Format:\nNon-terminal must be b/w 'A and Z'\nTerminals must be b/w 'a and z'\nEpsilon is denoted by '$'\n"
          "grammar:\nA->A+B|B\nB->B*C|C\nC->(A)|x\n"
          "corresponding input:\n3\nA 2 A+B B\nB 2 B*C C\nC 2 (A) x\n------------------------------------------------------\n";
    cout<<"enter #productions:";
    int n;cin>>n;
    cout<<"enter productions\n";
    for(int i=0;i<n;i++){
        char lhs;cin>>lhs;
        productions[lhs] = {};
        int k;cin>>k;
        for(int j=0;j<k;j++){
            string rhs;cin>>rhs;
            productions[lhs].push_back(rhs);
        } 
    }
    //grammar without left recursion
    unordered_map<char,vector<string>> newProductions;
    //int xy=0;
    for(auto i = productions.begin();i!=productions.end();i++){  
        //cout<<(i->first)<<endl;
        vector<string> rhs((i->second).begin(),(i->second).end());
        vector<string> newRhs;
        //step-I
        for(int p=0;p<rhs.size();p++){
            if(newProductions.find(rhs[p][0])!=newProductions.end()){
                string str = rhs[p];
                string sub_str = str.substr(1);
                for(auto x=newProductions[str[0]].begin();x!=newProductions[str[0]].end();x++){
                    if((*x)[0]!='$')  {
                        rhs.push_back((*x)+sub_str);
                    }else{
                        rhs.push_back(sub_str);
                    }
                }
            }else{
               newRhs.push_back(rhs[p]); 
            }
        }
        //step-II
        char curr = i->first;
        (i->second) = newRhs;
        vector<string> ok;
        vector<string> notOk;
        
        for(string x:(i->second)){
            if(curr==x[0]){
                notOk.push_back(x.substr(1));
            }else{
                ok.push_back(x);
            }
        }
        if(notOk.size()==0){
            //no left recursion
            newProductions[curr] = ok;
        }else{
            //left recursion present
            char newT = 'Z'-steps;
            for(int j=0;j<ok.size();j++){
                if(ok[j][0]=='$')ok[j] = string(1,newT);
                else ok[j] +=string(1,newT);
            }
            for(int j=0;j<notOk.size();j++){
                notOk[j]+=string(1,newT);
            }
            notOk.push_back("$");
            newProductions[newT] = notOk;
            newProductions[curr] = ok;
            steps++;
        }
         //print(newProductions);
         //print(productions);
    }
    cout<<"OUTPUT:\n";
    print(newProductions);
}