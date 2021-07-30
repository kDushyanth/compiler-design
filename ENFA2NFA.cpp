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
};
class ENFA{
    public:
    unordered_map<string,vector<unordered_set<string>>> transitions;
    string start;
    unordered_set<string> accept;
    ENFA(unordered_map<string,vector<unordered_set<string>>> transitions,string start,unordered_set<string> accept):
    transitions(transitions),start(start),accept(accept){}
    ENFA operator ||(const ENFA &b){
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
        ENFA newENFA(t,to_string(steps)+"Q1",a);
        steps++;
        return newENFA;
    }
    ENFA operator &&(const ENFA &b){
        unordered_map<string,vector<unordered_set<string>>> t;
        unordered_set<string> a;
        a.insert(b.accept.begin(),b.accept.end());
        t.insert((this->transitions).begin(),(this->transitions).end());
        t.insert((b.transitions).begin(),(b.transitions).end());
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            string curr = *itr;
            //vector<unordered_set<string>> temp1(27,unordered_set<string>());
            //t[curr] = temp1;
            t[curr][0].insert(b.start);
        }
        ENFA newENFA(t,this->start,a);
        return newENFA;
    }
    ENFA operator ++(int){
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
        ENFA newENFA(t,to_string(steps)+"Q1",a);
        steps++;
        return newENFA;
    }
    NFA toNFA(){
        //compute epsilon closure
        unordered_map<string,unordered_set<string>> closure;
        for(auto itr = transitions.begin();itr!=transitions.end();itr++){
            queue<string> q;
            unordered_map<string,bool> visit;
            for(auto it = transitions.begin();it!=transitions.end();it++){
                visit[it->first] = false;
            }
            q.push(itr->first);
            visit[itr->first]=true;
            string curr;
            unordered_set<string> temp;
            temp.insert(itr->first);
            while(q.empty()==false){
                curr = q.front();
                for(auto it = transitions[curr][0].begin();it!=transitions[curr][0].end();it++){
                    if(visit[*it]==false){
                        temp.insert(*it);
                        visit[*it] = true;
                        q.push(*it);
                    }   
                }
                q.pop();
            }
            closure[itr->first] = temp;
        }
        cout<<"-------------------------epsilon closure-------------------------"<<endl;
        for(auto itr = closure.begin();itr!=closure.end();itr++){
            cout<<itr->first<<"->";
            for(auto it = (itr->second).begin();it!=(itr->second).end();it++){
                cout<<(*it)<<" ";
            }cout<<endl;
        }
        unordered_map<string,vector<unordered_set<string>>> t;
        for(auto itr = transitions.begin();itr!=transitions.end();itr++){
            string curr = itr->first;
            unordered_set<string> currClosure= closure[curr];
            vector<unordered_set<string>> apply1(26,unordered_set<string>());
            for(auto it = currClosure.begin();it!=currClosure.end();it++){
                for(int i=0;i<26;i++){
                    apply1[i].insert(transitions[*it][i+1].begin(),transitions[*it][i+1].end());
                }
            }
            vector<unordered_set<string>> apply2(26,unordered_set<string>());
            for(int i=0;i<26;i++){
                for(auto it=apply1[i].begin();it!=apply1[i].end();it++){
                    apply2[i].insert(closure[*it].begin(),closure[*it].end());
                }
            }
            t[curr] = apply2;
        }
        //print NFA
        cout<<"-------------------------------NFA-------------------------------"<<endl;
        cout<<"transition function:"<<endl;
        for(auto itr = t.begin();itr!=t.end();itr++){
            cout<<itr->first<<"->";
            for(int i=0;i<26;i++){
                cout<<(char(i+97))<<":{";
                for(auto it = (itr->second)[i].begin();it!=(itr->second)[i].end();it++){
                    cout<<(*it)<<",";
                }cout<<"} ";
            }cout<<endl;
        }
        //start state
        string currStart = this->start;
        cout<<"start state: "<<currStart<<endl;
        unordered_set<string> currFinal;
        //final states

        unordered_set<string> totFinalClosure;
        for(auto itr = accept.begin();itr!=accept.end();itr++){
            totFinalClosure.insert(closure[*itr].begin(),closure[*itr].end());
        }
        unordered_set<string> finalStates;
        for(auto itr = closure.begin();itr!=closure.end();itr++){
            for(auto it = (itr->second).begin();it!=(itr->second).end();it++){
                if(totFinalClosure.find(*it)!=totFinalClosure.end()){
                    finalStates.insert(itr->first);
                    break;
                }
            }
        }
        cout<<"final state(s): ";
        for(auto itr=finalStates.begin();itr!=finalStates.end();itr++){
            cout<<(*itr)<<" ";
        }
        return NFA(t,currStart,finalStates);
    }
    void print(){
        cout<<"------------------------------ENFA------------------------------"<<endl;
        cout<<"start state: "<<this->start<<endl<<"final state(s): ";
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            cout<<*itr<<" ";
        }cout<<endl;
        cout<<"transition function:\n";
        for(auto itr = (this->transitions).begin();itr!=(this->transitions).end();itr++){
            cout<<(itr->first)<<"->";
            for(int i=0;i<27;i++){
                if(i!=0)cout<<(char(96+i))<<":{";
                else cout<<"E:{";
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
ENFA create(char a){
    if(a=='E'){  
        unordered_map<string,vector<unordered_set<string>>> t;
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        s.insert(to_string(steps)+"Q1");
        ENFA newENFA(t,to_string(steps)+"Q1",s);
        steps++;
        return newENFA;
    }else if(a=='P'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        unordered_set<string> s;
        ENFA newENFA(t,to_string(steps)+"Q1",s);
        steps++;
        return  newENFA;
    }else if(a>='a' && a<='z'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[to_string(steps)+"Q1"] = vector<unordered_set<string>> (27);
        t[to_string(steps)+"Q2"] = vector<unordered_set<string>> (27);
        t[to_string(steps)+"Q1"][a-'a'+1].insert(to_string(steps)+"Q2");
        unordered_set<string> s;s.insert(to_string(steps)+"Q2");
        ENFA newENFA(t,to_string(steps)+"Q1",s);
        steps++;
        return  newENFA;
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
    stack<ENFA> s;
    for(int i=0;i<modified.length();i++){
        if(modified[i]>='a' && modified[i]<='z' || modified[i]=='P' || modified[i]=='E'){
            s.push(create(modified[i]));
        }else if(modified[i]=='&'){
            ENFA n1 = s.top();
            s.pop();
            ENFA n2 = s.top();
            s.pop();
            s.push(n2&&n1);
        }else if(modified[i]=='|'){
            ENFA n1 = s.top();
            s.pop();
            ENFA n2 = s.top();
            s.pop();
            s.push(n1||n2);
        }else if(modified[i]=='+'){
            ENFA n1 = s.top();
            s.pop();
            s.push(n1++);
        }
    }
    ENFA result = s.top();
    s.pop();
    cout<<"verify:"<<(s.empty()==true)<<endl;
    result.print();
    NFA nfa = result.toNFA();
}
