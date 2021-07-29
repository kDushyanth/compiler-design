#include<bits/stdc++.h>
using namespace std;

int precedence(char x){
    switch(x){
        case '+': return 3;
        case '&': return 2;
        case '|': return 1;
        default : return 0;
    }
}
int steps = 1;
class NFA{
    public:
    unordered_map<string,vector<unordered_set<string>>> transitions;
    string start;
    unordered_set<string> accept;
    NFA(unordered_map<string,vector<unordered_set<string>>> transitions,string start,unordered_set<string> accept):
    transitions(transitions),start(start),accept(accept){}
    NFA operator ||(const NFA &b){
        unordered_map<string,vector<unordered_set<string>>> t;
        
        t.insert((this->transitions).begin(),(this->transitions).end());
        t.insert((b.transitions).begin(),(b.transitions).end());
        vector<unordered_set<string>> vec(27,unordered_set<string>());
        unordered_set<string> next;next.insert(this->start);next.insert(b.start);
        vec[0] = next;
        t[to_string(steps)+"Q1"] = vec;
        
        unordered_set<string> a;
        a.insert((this->accept).begin(),(this->accept).end());
        a.insert((b.accept).begin(),(b.accept).end());
        NFA newNFA(t,to_string(steps)+"Q1",a);
        steps++;
        return newNFA;
    }
    NFA operator &&(const NFA &b){
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
    NFA operator ++(int){
        unordered_map<string,vector<unordered_set<string>>> t;
        unordered_set<string> a;
        a.insert((this->accept).begin(),(this->accept).end());
        a.insert(to_string(steps)+"Q1");
        t.insert((this->transitions).begin(),(this->transitions).end());
        vector<unordered_set<string>> temp1(27,unordered_set<string>());
        t[to_string(steps)+"Q1"] = temp1;
        t[to_string(steps)+"Q1"][0].insert(this->start);
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            t[*itr][0].insert(this->start);
        }
        NFA newNFA(t,to_string(steps)+"Q1",a);
        steps++;
        return newNFA;
    }
    
    void print(){
        cout<<"start state: "<<this->start<<endl<<"final state(s): ";
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            cout<<*itr<<" ";
        }cout<<endl;
        for(auto itr = (this->transitions).begin();itr!=(this->transitions).end();itr++){
            cout<<(itr->first)<<" ";
            for(int i=0;i<27;i++){
                cout<<i<<"{";
                for(auto it = (itr->second)[i].begin();it!=(itr->second)[i].end();it++){
                    cout<<(*it)<<",";
                }
                cout<<"} ";
            }
            cout<<endl;
        }
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
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        s.insert(to_string(steps)+"Q1");
        NFA newNFA(t,to_string(steps)+"Q1",s);
        steps++;
        return newNFA;
    }else if(a=='P'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        NFA newNFA(t,to_string(steps)+"Q1",s);
        steps++;
        return  newNFA;
    }else if(a>='a' && a<='z'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        t[to_string(steps)+"Q2"] = vector<unordered_set<string>> (27);
        t[to_string(steps)+"Q1"][a-'a'+1].insert(to_string(steps)+"Q2");
        unordered_set<string> s;s.insert(to_string(steps)+"Q2");
        NFA newNFA(t,to_string(steps)+"Q1",s);
        steps++;
        return  newNFA;
    }
};
int main(){
    //P: phi and E:epsilon
    cout<<"the regular expression must confirm to following rules:"
          "\n P denotes Phi"
          "\n E denotes epsilon"
          "\n alphabet: a to z"
          "\n Operators on regular expressions:"
          "\n 1. re1 | re2 denotes re1 or re2"
          "\n 2. re1 & re2 denotes re1 concatenated with re2"
          "\n 3. re+ denotes zero or more occurances of re\n";
    cout<<"enter regular expression:";
    string re;
    cin>>re;
    string modified = inToPost(re);
    cout<<modified<<endl;
    stack<NFA> s;
    for(int i=0;i<modified.length();i++){
        if(modified[i]>='a' && modified[i]<='z' || modified[i]=='P' || modified[i]=='E'){
            s.push(create(modified[i]));
        }else if(modified[i]=='&'){
            NFA n1 = s.top();
            s.pop();
            NFA n2 = s.top();
            s.pop();
            s.push(n1&&n2);
        }else if(modified[i]=='|'){
            NFA n1 = s.top();
            s.pop();
            NFA n2 = s.top();
            s.pop();
            s.push(n1||n2);
        }else if(modified[i]=='+'){
            NFA n1 = s.top();
            s.pop();
            s.push(n1++);
        }
    }
    NFA result = s.top();
    s.pop();
    cout<<"verify:"<<(s.empty()==true)<<endl;
    result.print();
}
