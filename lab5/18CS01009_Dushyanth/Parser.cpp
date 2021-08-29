#include<bits/stdc++.h>
using namespace std;
//cd lab5/18CS01009_dushyanth
class Grammar{
    protected:
        int num_T,num_N;
        vector<pair<string,set<vector<string>>>> productions;
        unordered_map<string,unordered_set<string>> firstSets;
        unordered_map<string,unordered_set<string>> followSets;
        unordered_map<string,int> N_idx;
        unordered_map<int,string> idx_N;
        unordered_map<int,string> idx_T;
        unordered_map<string,int> T_idx;
    public:
    Grammar(){
        //read grammar file and store productions in datastructure
        string gfile/*="grammarll2.txt"*/;
        cout<<"enter file that contains grammar"<<endl;
        cin>>gfile;
        ifstream infile(gfile);
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
        //T_idx["#"] = num_T+1;
        //idx_T[num_T+1] = "#";
        for(int i=0;i<num_N;i++){
            //cout<<i<<endl;
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
        
        cout<<"productions--------------------"<<endl;
        for(int i=0;i<num_N;i++){
            cout<<productions[i].first<<"->";
            for(auto itr:productions[i].second){
                for(auto itr1:(itr)){
                    cout<<(itr1);
                }cout<<"|";
            }cout<<endl;
        }
        cout<<"idx2T--------------------"<<endl;
        for(auto x: idx_T){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"idx2N--------------------"<<endl;
        for(auto x: idx_N){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"T2idx--------------------"<<endl;
        for(auto x: T_idx){
            cout<<x.first<<" "<<x.second<<endl;
        }
        cout<<"N2idx--------------------"<<endl;
        for(auto x: N_idx){
            cout<<x.first<<" "<<x.second<<endl;
        }
        
        //string gfile;
        // read file and store first and follow sets in datastructure
        cout<<"enter file that contains first and follow sets"<<endl;
        cin>>gfile;
        //gfile = "firstfollow2.txt";
        ifstream infile2(gfile);
        for(int i=0;i<num_N;i++){
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
        for(int i=0;i<num_N+num_T+1;i++){
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
        
        cout<<"First--------------------"<<endl;
        for(auto x: firstSets){
            cout<<x.first<<" ";
            for(auto y:x.second){
                cout<<y<<" ";
            }cout<<endl;
        }
        cout<<"Follow--------------------"<<endl;
        for(auto x: followSets){
            cout<<x.first<<" ";
            for(auto y:x.second){
                cout<<y<<" ";
            }cout<<endl;
        }
        cout<<"--------------------"<<endl;
        
    }    
};

class Parser :public Grammar{
    private:
    vector<vector<pair<string,vector<string>>>> parsingTable;
    int curr;
    stack<string> s;
    public:
    Parser(){
        curr=0;
        s.push("$");
        parsingTable = vector<vector<pair<string,vector<string>>>>(num_N,vector<pair<string,vector<string>>>( num_T+1));
    }
    void printStack(stack<string> s){
        if(s.empty())return;
        cout<<(s.top());
        string str = s.top();
        s.pop();
        printStack(s);
        s.push(str);
    }
    void printInput(vector<string> ip,int curr){
        for(int i=curr;i<ip.size();i++){
            cout<<ip[i];
        }
    }
    void parse(vector<string> input){
        input.push_back("$");
        s.push(idx_N[0]);
        //cout<<(idx_N[0]);
        cout<<"stack \t\t\t input \t\t\t actions\n";
        while(s.top()!="$"){
            //cout<<(s.top())<<"\t\t"<<input[curr]<<endl;
            if(T_idx.find(s.top())==T_idx.end()){
                if(parsingTable[N_idx[s.top()]][T_idx[input[curr]]].first==""){
                    cout<<"incorrect syntax"<<endl;
                    break;
                }else{
                    vector<string> vec = parsingTable[N_idx[s.top()]][T_idx[input[curr]]].second;
                    printStack(s);cout<<"\t\t\t";
                    printInput(vec,curr);cout<<"\t\t\t";
                    cout<<s.top()<<"->";
                    for(auto x:vec){
                        cout<<x;
                    }cout<<endl;
                    
                    s.pop();
                    for(auto itr = vec.rbegin();itr!=vec.rend();itr++){
                        if(*itr!="#")s.push(*itr);
                    }

                }      
            }else if(s.top()==input[curr]){
                    printStack(s);cout<<"\t\t\t";
                    printInput(input,curr);cout<<"\t\t\t";
                    cout<<"match "<<(s.top())<<endl;
                    s.pop();
                    curr++;
            }else{
                cout<<"incorrect syntax"<<endl;
                break;
            }
        }
        if(s.top()=="$" && input[curr]=="$")cout<<"success"<<endl;
    }
    //does the 2nd step of parsing table filling algorithm
    unordered_set<string> getAll(string lhs,vector<string> RHS){
        unordered_set<string> result;
        bool isEnd=true;
        for(int i=0;i<RHS.size();i++){
            result.insert(firstSets[RHS[i]].begin(),firstSets[RHS[i]].end());
            if(firstSets[RHS[i]].find("#")==firstSets[RHS[i]].end()){
                isEnd=false;
                break;
            }else result.erase("#");
        }
        if(isEnd){
            result.insert(followSets[lhs].begin(),followSets[lhs].end());
        }
        return result;
    }
    void printer(unordered_set<string> vec){
        cout<<"----------debug------------"<<endl;
        for(string x:vec){
            cout<<x<<" ";
        }cout<<"\n----------debug------------"<<endl;
    }
    void printSpace(int num){
        while(num--){
            cout<<" ";
        }
    }
    //fill the parsing table
    void create(){
        for(int i=0;i<num_N;i++){
            string A = productions[i].first;
            for(auto itr = productions[i].second.begin();itr!= productions[i].second.end();itr++){
                unordered_set<string> result = getAll(A,(*itr));
                for(string x:result){
                    parsingTable[N_idx[A]][T_idx[x]].first = A;
                    parsingTable[N_idx[A]][T_idx[x]].second = (*itr);
                }
            }
        }
    }
    //print parsing table
    void print(){
        cout<<"Parsing Table:"<<endl;
        vector<int> width(num_T+1,INT_MIN);
        for(int i=0;i<num_N;i++){
            for(int j=0;j<num_T+1;j++){
                width[j+1] = max(width[j+1],(int) (parsingTable[i][j].first.length()+2+parsingTable[i][j].second.size()));
            }
        }
        for(auto p:N_idx){
            width[0] = max(width[0],(int)p.first.size());
        }
        
        printSpace(width[0]);
        for(int j=0;j<num_T+1;j++){
                    cout<<(idx_T[j]);printSpace(width[j+1]-(idx_T[j].length())+3);
        }cout<<endl;
        for(int i=0;i<num_N;i++){
            cout<<(idx_N[i])<<"\t";
            for(int j=0;j<num_T+1;j++)
            {
                //cout<<width[j]<<"[]"<<(width[j] - parsingTable[i][j].first.length()+parsingTable[i][j].second.size()+2)<<endl;
                if(parsingTable[i][j].first.length()+2+parsingTable[i][j].second.size()>2){
                        cout<<parsingTable[i][j].first<<"->";
                        for(int k=0;k<parsingTable[i][j].second.size();k++){
                            cout<<parsingTable[i][j].second[k];
                        }//cout<<"\t";
                        printSpace(width[j+1] - (parsingTable[i][j].first.length()+parsingTable[i][j].second.size()+2)+3);
                }else{
                    printSpace(width[j+1]+3);
                }
            }cout<<endl;
        }
    }

};
//read tokens from a file
vector<string> myReader(string fname){
    vector<string> tkns;
    ifstream infile(fname);
    string str;
    while(getline(infile,str)){
        tkns.push_back(str);
    }
    return tkns;
}
int main(){
    Parser p;
    p.create();
    p.print();
    //vector<string> tokens;
    p.parse(myReader("tkn.txt"));
}
