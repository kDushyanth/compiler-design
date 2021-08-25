#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
//cd lab4/18CS01009_dushyanth/q2

//E=>E T=>T E'=>D T'=>S F=>F
bool E(map<char,set<string>> productions,string str,int &curr);
bool T(map<char,set<string>> productions,string str,int &curr);
bool D(map<char,set<string>> productions,string str,int &curr);
bool S(map<char,set<string>> productions,string str,int &curr);
bool F(map<char,set<string>> productions,string str,int &curr);
void printer(char T,string str,int curr){
    cout<<T<<" "<<(str.insert(curr,"|"))<<endl;
}
bool isTerminal(char ch){
    return (ch>='a' && ch<='z');
}
//functions for each non-terminal in grammar
bool E(map<char,set<string>> productions,string str,int &curr){
    //Sleep(2000);
    int t = curr;
    //cout<<"E"<<endl;
    printer('E',str,curr);
    //cout<<curr<<endl;
    set<string> rhs=productions['E'];
    bool exists=false;
    for(auto x:rhs){
        if(x=="$"){
            exists=true;continue;
        }
        bool found=true;
        for(auto y:x){
            //bool r = true;
            switch(y){
                case 'T':found = T(productions,str,curr);break;
                case 'E':found = E(productions,str,curr);break;
                case 'D':found = D(productions,str,curr);break;
                case 'S':found = S(productions,str,curr);break;
                case 'F':found = F(productions,str,curr);break;
                case '$':found = (curr==str.length());break;
                default :found = (curr!=str.length() && str[curr]==y);if(str[curr]==y)curr++;
            }
            if(found==false){
                break;
            }
        }
        if(found==true){
            return true;
        }
    }
    curr = t;
    return exists;
}
bool T(map<char,set<string>> productions,string str,int &curr){
    printer('T',str,curr);
    //Sleep(2000);
    int t = curr;
    //cout<<curr<<endl;
    set<string> rhs=productions['T'];
    bool exists=false;
    for(auto x:rhs){
        bool found=true;
        if(x=="$"){
            exists=true;
            break;
        }  
        for(auto y:x){
            //bool r = true;
            switch(y){
                case 'T':found = T(productions,str,curr);break;
                case 'E':found = E(productions,str,curr);break;
                case 'D':found = D(productions,str,curr);break;
                case 'S':found = S(productions,str,curr);break;
                case 'F':found = F(productions,str,curr);break;
                case '$':found = (curr==str.length());break;
                default :found = (curr!=str.length() && str[curr]==y);if(str[curr]==y)curr++;
            }
            if(found==false){
                break;
            }
        }
        if(found==true)return true;
    }
    curr = t;
    return exists;
}
bool D(map<char,set<string>> productions,string str,int &curr){
    printer('D',str,curr);
    //Sleep(2000);
    int t = curr;
    //cout<<curr<<endl;
    //if(curr==str.length())return true;
    set<string> rhs=productions['D'];
    bool exists=false;
    for(auto x:rhs){
        if(x=="$"){
            exists=true;
            continue;
        }
        bool found=true;
        for(auto y:x){
            //bool r = true;
            //cout<<y<<"rem"<<endl;
            switch(y){
                case 'T':found = T(productions,str,curr);break;
                case 'E':found = E(productions,str,curr);break;
                case 'D':found = D(productions,str,curr);break;
                case 'S':found = S(productions,str,curr);break;
                case 'F':found = F(productions,str,curr);break;
                case '$':found = (curr==str.length());break;
                default :found = (curr!=str.length() && str[curr]==y);if(str[curr]==y)curr++;
            }
            if(found==false){
                //cout<<curr<<" "<<"dreco"<<endl;
                break;
            }
        }
        if(found==true){
            //cout<<"dreco"<<endl;
            return true;
        }
    }
    curr = t;
    return exists;
}
bool S(map<char,set<string>> productions,string str,int &curr){
    printer('S',str,curr);
    int t = curr;
    set<string> rhs=productions['S'];
    bool exists = false;
    for(auto x:rhs){
        bool found=true;
        if(x=="$"){
            exists = true;
            continue;
        }
        for(auto y:x){
            //bool r = true;
            switch(y){
                case 'T':found = T(productions,str,curr);break;
                case 'E':found = E(productions,str,curr);break;
                case 'D':found = D(productions,str,curr);break;
                case 'S':found = S(productions,str,curr);break;
                case 'F':found = F(productions,str,curr);break;
                case '$':found = (curr==str.length());break;
                default :found = (curr!=str.length() && str[curr]==y);if(str[curr]==y)curr++;
            }
            if(found==false){
                break;
            }
        }
        if(found==true){
            //cout<<"sreco"<<endl;
            return true;
        }
    }
    curr = t;
    return exists;
}
bool F(map<char,set<string>> productions,string str,int &curr){
    printer('F',str,curr);
    int t = curr;
    //Sleep(500);
    //cout<<curr<<endl;
    set<string> rhs=productions['F'];
    bool exists = false;
    for(auto x:rhs){
        bool found=true;
        if(x=="$"){
            exists = true;
            continue;
        }
        //cout<<x<<"out"<<endl;
        for(auto y:x){
            //cout<<y<<"in"<<endl;
            //bool r = true;
            switch(y){
                case 'T':found = T(productions,str,curr);break;
                case 'E':found = E(productions,str,curr);break;
                case 'D':found = D(productions,str,curr);break;
                case 'S':found = S(productions,str,curr);break;
                case 'F':found = F(productions,str,curr);break;
                case '$':found = (curr==str.length());break;
                default :/*cout<<x<<" "<<curr<<"f"<<endl;*/found = (curr!=str.length() &&(str[curr]==y || (y=='i' && isTerminal(str[curr]))));if(str[curr]==y  || (y=='i' && isTerminal(str[curr])))curr++;
            }
            if(found==false){
                break;
            }
        }
        if(found==true){
            //cout<<"ireco"<<endl;
            return true;
        }
    }
    curr = t;
    return exists;
}
int main(){
    string str;
    cout<<"enter a string:";
    cin>>str;
    //grammar
    map<char,set<string>> productions;
    productions['E'] = {"TD"};
    productions['D'] = {"+TD","$"};
    productions['T'] = {"FS"};
    productions['S'] = {"*FS","$"};
    productions['F'] = {"(E)","i"};
    int curr=0;
    bool ok = E(productions,str,curr);
    (ok && curr==str.length())? cout<<"syntactically valid\n":cout<<"syntactically invalid\n"<<endl;
}