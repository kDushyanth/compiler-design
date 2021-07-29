#include<bits/stdc++.h>
using namespace std;

int precedence(char x){
    switch(x){
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default : return 0;
    }
}
int steps = 1;
class NFA{
    unordered_map<string,vector<unordered_set<string>>> transitions;
    string start;
    unordered_set<string> accept;
    NFA(unordered_map<string,vector<unordered_set<string>>> transitions,string start,unordered_set<string> accept):
    transitions(transitions),start(start),accept(accept){}
    NFA operator +(const NFA &b){
        unordered_map<string,vector<unordered_set<string>>> t;
        
        t.insert((this->transitions).begin(),(this->transitions).end());
        t.insert((b.transitions).begin(),(b.transitions).end());
        vector<unordered_set<string>> vec(27,unordered_set<string>());
        unordered_set<string> next;next.insert(this->start);next.insert(b.start);
        vec[0] = next;
        t[steps+"Q1"] = vec;
        
        unordered_set<string> a;
        a.insert((this->accept).begin(),(this->accept).end());
        a.insert((b.accept).begin(),(b.accept).end());
        NFA newNFA(t,steps+"Q1",a);
        steps++;
        return newNFA;
    }
    NFA operator &(const NFA &b){
        unordered_map<string,vector<unordered_set<string>>> t;
        unordered_set<string> a;
        a.insert(b.accept.begin(),b.accept.end());
        t.insert((this->transitions).begin(),(this->transitions).end());
        t.insert((b.transitions).begin(),(b.transitions).end());
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            string curr = *itr;
            vector<unordered_set<string>> temp1(27,unordered_set<string>());
            t[curr] = temp1;
            t[curr][0].insert(b.start);
        }
        NFA newNFA(t,this->start,a);
        return newNFA;
    }
    NFA operator *(){
        unordered_map<string,vector<unordered_set<string>>> t;
        unordered_set<string> a;
        a.insert((this->accept).begin(),(this->accept).end());
        a.insert(steps+"Q1");
        t.insert((this->transitions).begin(),(this->transitions).end());
        vector<unordered_set<string>> temp1(27,unordered_set<string>());
        t[steps+"Q1"] = temp1;
        t[steps+"Q1"][0].insert(this->start);
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            t[*itr][0].insert(this->start);
        }
        NFA newNFA(t,steps+"Q1",a);
        steps++;
        return newNFA;
    }
};
string inToPost(string re){
    string result = "";
    stack<char> s;
    for(int i=0;i<re.length();i++){
        if(re[i]>='a' && re[i]<='z' || re[i]=='P' || re[i]=='E')result+=re[i];
        else if(re[i]=='(')s.push(re[i]);
        else if(re[i]==')'){
            while(s.top()!='('){
                result+=s.top();
                s.pop();
            }s.pop();
        }else if(s.empty()==true || s.top()=='('){
            s.push(re[i]);
        }else if(precedence(re[i])>precedence(s.top())){
            s.push(re[i]);
        }else{
            while(s.empty()==false && precedence(re[i])<precedence(s.top())){
                result+=s.top();
                s.pop();
            }s.push(re[i]);
        }
    }
    while(!s.empty()){
        result+=s.top();
        s.pop();
    }
    return result;
}
NFA create(char a){
    if(a=='E'){  
        unordered_map<string,vector<unordered_set<string>>> t;
        t[steps+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        s.insert(steps+"Q1");
        NFA newNFA= NFA(t,steps+"Q1",s);
        steps++;
        return  newNFA;
    }else if(a=='P'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[steps+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        NFA newNFA= NFA(t,steps+"Q1",s);
        steps++;
        return  newNFA;
    }else if(a>='a' && a<='z'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[steps+"Q1"] = vector<unordered_set<string>> (27);
        t[steps+"Q2"] = vector<unordered_set<string>> (27);
        t[steps+"Q1"][a-'a'+1].insert(steps+"Q2");
        unordered_set<string> s;s.insert(steps+"Q2");
        NFA newNFA=  NFA(t,steps+"Q1",s);
        steps++;
        return  newNFA;
    }
};
int main(){
    //P: phi and E:epsilon
    cout<<"enter regular expression:";
    string re;
    cin>>re;
    cout<<inToPost(re)<<endl;

}
