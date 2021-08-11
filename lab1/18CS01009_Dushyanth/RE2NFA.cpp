#include<bits/stdc++.h>
using namespace std;

//a macro to define number of elements in regular expressions's alphabet.
#define COUNT 3

//precedence of regular expression operations
int precedence(char x){
    switch(x){
        case '+': return 3;
        case '&': return 2;
        case '|': return 1;
        default : return 0;
    }
}

//generates unique name for each state
int steps = 1;
string getState(){
    return "Q"+to_string(steps);
}


//A C++ class that represents NFA
class NFA{
    public:
    unordered_map<string,vector<unordered_set<string>>> transitions;
    string start;
    unordered_set<string> accept;
    NFA(unordered_map<string,vector<unordered_set<string>>> transitions,string start,unordered_set<string> accept):
    transitions(transitions),start(start),accept(accept){}
};
//A C++ class that represents epsilon NFA
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
        vector<unordered_set<string>> vec(COUNT+1,unordered_set<string>());
        unordered_set<string> next;next.insert(this->start);next.insert(b.start);
        vec[0] = next;
        t[getState()] = vec;
        
        unordered_set<string> a;
        a.insert((this->accept).begin(),(this->accept).end());
        a.insert((b.accept).begin(),(b.accept).end());
        ENFA newENFA(t,getState(),a);
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
            //vector<unordered_set<string>> temp1(COUNT+1,unordered_set<string>());
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
        a.insert(getState());
        t.insert((this->transitions).begin(),(this->transitions).end());
        vector<unordered_set<string>> temp1(COUNT+1,unordered_set<string>());
        t[getState()] = temp1;
        t[getState()][0].insert(this->start);
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            t[*itr][0].insert(this->start);
        }
        ENFA newENFA(t,getState(),a);
        steps++;
        return newENFA;
    }
    //function that converts epsilon NFA to NFA and prints the correesponding NFA
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
            vector<unordered_set<string>> apply1(COUNT,unordered_set<string>());
            for(auto it = currClosure.begin();it!=currClosure.end();it++){
                for(int i=0;i<COUNT;i++){
                    apply1[i].insert(transitions[*it][i+1].begin(),transitions[*it][i+1].end());
                }
            }
            vector<unordered_set<string>> apply2(COUNT,unordered_set<string>());
            for(int i=0;i<COUNT;i++){
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
            for(int i=0;i<COUNT;i++){
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
    //prints epsilon NFA in certain format
    void print(){
        cout<<"------------------------------ENFA------------------------------"<<endl;
        cout<<"start state: "<<this->start<<endl<<"final state(s): ";
        for(auto itr = (this->accept).begin();itr!=(this->accept).end();itr++){
            cout<<*itr<<" ";
        }cout<<endl;
        cout<<"transition function:\n";
        for(auto itr = (this->transitions).begin();itr!=(this->transitions).end();itr++){
            cout<<(itr->first)<<"->";
            for(int i=0;i<COUNT+1;i++){
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
/*
The regular expression input from user is converted to postfix 
and then this postfix is evaluated using a stack.
This function takes infix expression and returns postfix expression.
*/
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
//function that returns the epsilon NFAs of basic Regular Expressions like a,b..z,epsilon,phi
ENFA create(char a){
    if(a=='E'){  
        unordered_map<string,vector<unordered_set<string>>> t;
        t[getState()] = vector<unordered_set<string>> (COUNT+1);
        unordered_set<string> s;
        s.insert(getState());
        ENFA newENFA(t,getState(),s);
        steps++;
        return newENFA;
    }else if(a=='P'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        t[getState()] = vector<unordered_set<string>> (COUNT+1);
        unordered_set<string> s;
        ENFA newENFA(t,getState(),s);
        steps++;
        return  newENFA;
    }else if(a>='a' && a<='z'){
        
        unordered_map<string,vector<unordered_set<string>>> t;
        string ss = getState();steps++;string fs = getState();steps++;
        t[ss] = vector<unordered_set<string>> (COUNT+1);
        t[fs] = vector<unordered_set<string>> (COUNT+1);
        t[ss][a-'a'+1].insert(fs);
        unordered_set<string> s;s.insert(fs);
        ENFA newENFA(t,ss,s);
        //steps++;
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
    //infix to postfix 
    string modified = inToPost(re);
    cout<<modified<<endl;
    stack<ENFA> s;
    //process the postfix expression and create epsilon NFA.
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
    //print epsilon NFA
    result.print();
    //convert epsilon nfa to nfa
    NFA nfa = result.toNFA();
}
