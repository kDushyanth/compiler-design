#include<bits/stdc++.h>
using namespace std;

//cd lab4/18CS01009_dushyanth/q2
bool isTerminal(const string &a,int i){
    return a[i]>='a' && a[i]<='z';
}
int lp(const string &a,const string &b){
    int i=0;int j=0;
    int len=0;
    while(i<a.length() && j<b.length() && isTerminal(a,i) && isTerminal(b,j) && a[i]==b[j]){
        i++;j++;len++;
    }
    return len;
}
void print(map<char,vector<string>> productions){
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
int steps = 0;
void leftFactor(map<char,vector<string>> &productions,map<char,vector<string>> &newProductions){
    //int counter=0;
    while(productions.size()>0){
        //counter++;
        //if(counter>4)break;
        //print(productions);
        //cout<<(productions.size());
        auto itr = productions.begin();
        vector<string> temp;
        vector<string> curr = (itr->second);
        sort(curr.begin(),curr.end());
        for(int i=0;i<curr.size();i++){
            int len = curr[i].length();int j=i+1;
            for(j=i+1;j<curr.size();j++){
                int prev = len;
                len = min(len,lp(curr[i],curr[j]));
                if(len==0){
                    len = prev;
                    break;
                }
            }
            if(len>=1 && j-1-i>0){
                string sub_str = curr[i].substr(0,len);
                //cout<<sub_str<<endl;
                char newT = (char)'Z'-steps;
                productions[newT] = {};
                for(int p=i;p<j;p++){
                    if(curr[p].length()==len){
                        productions[newT].push_back("$");
                        continue;
                    }
                    productions[newT].push_back(curr[p].substr(len)); 
                }
                temp.push_back((sub_str)+string(1,newT));
                steps++;
                i=j-1;
            }else{
                temp.push_back(curr[i]);
            }
        }
        newProductions[itr->first] = temp;
        productions.erase(itr);
    }
}
int main(){
    map<char,vector<string>> productions;
    map<char,vector<string>> newProductions;
    cout<<"Input Format:\n\n"
          "grammar:\nA->aAB|aBc|aAc\n"
          "input:\n1\nA 3 aAB aBc aAc\n";
    cout<<"enter #productions:";
    int n;cin>>n;
    cout<<"\nenter productions\n";
    for(int i=0;i<n;i++){
        char lhs;cin>>lhs;
        productions[lhs] = {};
        int k;cin>>k;
        for(int j=0;j<k;j++){
            string rhs;cin>>rhs;
            productions[lhs].push_back(rhs);
        } 
    }
    cout<<"INPUT:\n";
    print(productions);
    leftFactor(productions,newProductions);
    cout<<"OUTPUT:\n";
    print(newProductions);
}