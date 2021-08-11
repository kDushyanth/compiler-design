#include <bits/stdc++.h>
#include<windows.h>
using namespace std;
/*
g++ LexicalAnalyzer.cpp
a.exe
if input<10 then output1=100 else output2>=100
*/
struct token
{
    string type;
    string lexeme;
    bool isValid()
    {
        return this->lexeme != "nf" && this->type != "nf";
    }
    void print()
    {
        cout << "(" + type + "," + lexeme + ")\n";
    }
    token(string type, string lexeme) : type(type), lexeme(lexeme) {}
};
bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}
bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch>='A' && ch<='Z');
}
string getString(int start, int end, string stmt)
{
    //cout << start << "to" << end << endl;
    string res = "";
    for (int i = start; i <= end; i++)
    {
        res += stmt[i];
    }
    return res;
}
//transition diagram that recognizes 'identifier'
token ID(string stmt, int &idx)
{
    int state = 0;
    const int start = idx;
    while (1)
    {
        switch (state)
        {
        case 0:
            if (isLetter(stmt[idx]))
            {
                idx++;
                state = 1;
            }
            else
            {
                return token("nf", "nf");
            }
            break;
        case 1:
            if (isLetter(stmt[idx]) || isDigit(stmt[idx]))
            {
                idx++;
            }
            else
            {   
                state = 2;
            }
            break;
        case 2:
            return token("id", getString(start, idx - 1, stmt));
        }
    }
}
//transition diagram that recognizes 'number'
token NUMBER(string stmt, int &idx)
{
    int state = 0;
    const int start = idx;
    while (1)
    {
        switch (state)
        {
        case 0:
            if (isDigit(stmt[idx]))
            {
                idx++;
                state = 1;
            }
            else
            {
                return token("nf", "nf");
            }
            break;
        case 1:
            if (stmt[idx] == '.')
            {
                idx++;
                state = 2;
            }
            else if (stmt[idx] == 'E')
            {
                idx++;
                state = 4;
            }
            else if (isDigit(stmt[idx]))
            {
                idx++;
            }
            else
            {
                state = 8;
            }
            break;
        case 2:
            if (isDigit(stmt[idx]))
            {
                idx++;
                state = 3;
            }
            else
            {
                return token("nf", "nf");
            }
            break;
        case 3:
            if (isDigit(stmt[idx]))
            {
                idx++;
            }
            else if (stmt[idx] == 'E')
            {
                idx++;
                state = 4;
            }
            else
            {
                state = 9;
            }
            break;
        case 4:
            if (isDigit(stmt[idx]))
            {
                idx++;
                state = 6;
            }
            else if (stmt[idx] == '+' || stmt[idx] == '-')
            {
                state = 5;
                idx++;
            }
            break;
        case 5:
            if (isDigit(stmt[idx]))
            {
                idx++;
                state = 6;
            }
            else
            {
                return token("nf", "nf");
            }
            break;
        case 6:
            if (isDigit(stmt[idx]))
            {
                idx++;
            }
            else
            {
                state = 7;
            }
            break;
        case 7:
            return token("number", getString(start, idx - 1, stmt));
            break;
        case 8:
            return token("number", getString(start, idx - 1, stmt));
        case 9:
            return token("number", getString(start, idx - 1, stmt));
        }
    }
}
//transition diagram that recognizes 'whitespaces'
void WS(string stmt, int &idx)
{
    int state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            switch (stmt[idx])
            {
            case ' ':
                idx++;
                state = 1;
                break;
            default:
                return;
            }
            break;
        case 1:
            switch (stmt[idx])
            {
            case ' ':
                idx++;
                break;
            default:
                state = 2;
                break;
            }
            break;
        case 2:
            return;
        }
    }
}
//transition diagram that recognizes 'else'
token ELSE(string stmt, int &idx)
{
    int state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            switch (stmt[idx])
            {
            case 'e':
                idx++;
                state = 1;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 1:
            switch (stmt[idx])
            {
            case 'l':
                idx++;
                state = 2;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 2:
            switch (stmt[idx])
            {
            case 's':
                idx++;
                state = 3;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 3:
            switch (stmt[idx])
            {
            case 'e':
                idx++;
                state = 4;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 4:
            if (!(isDigit(stmt[idx])) && !(isLetter(stmt[idx])))
            {
                return token("else", "");
            }
            else
            {
                return token("nf", "nf");
            }
        }
    }
}
//transition diagram that recognizes 'if'
token IF(string stmt, int &idx)
{
    int state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            switch (stmt[idx])
            {
            case 'i':
                idx++;
                state = 1;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 1:
            switch (stmt[idx])
            {
            case 'f':
                idx++;
                state = 2;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 2:
            if (!(isDigit(stmt[idx])) && !(isLetter(stmt[idx])))
            {
                return token("if", "");
            }
            else
            {
                return token("nf", "nf");
            }
        }
    }
}
//transition diagram that recognizes 'then'
token THEN(string stmt, int &idx)
{
    int state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            switch (stmt[idx])
            {
            case 't':
                idx++;
                state = 1;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 1:
            switch (stmt[idx])
            {
            case 'h':
                idx++;
                state = 2;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 2:
            switch (stmt[idx])
            {
            case 'e':
                idx++;
                state = 3;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 3:
            switch (stmt[idx])
            {
            case 'n':
                idx++;
                state = 4;
                break;
            default:
                return token("nf", "nf");
            }
            break;
        case 4:
            if (!(isDigit(stmt[idx])) && !(isLetter(stmt[idx])))
            {
                return token("then", "");
            }
            else
            {
                return token("nf", "nf");
            }
        }
    }
}
//transition diagram that recognizes 'relational operator'
token RELOP(string stmt, int &idx)
{
    int state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            switch (stmt[idx])
            {
            case '<':
                idx++;
                state = 1;
                break;
            case '=':
                idx++;
                state = 5;
                break;
            case '>':
                idx++;
                state = 6;
                break;
            default:
                return token("nf", "nf");
            };
            break;
        case 1:
            switch (stmt[idx])
            {
            case '=':
                idx++;
                state = 2;
                break;
            case '>':
                idx++;
                state = 3;
                break;
            default:
                state = 4;
            }
            break;
        case 2:
            return token("relop", "<=");
        case 3:
            return token("relop", "<>");
        case 4:
            return token("relop", "<");
        case 5:
            //idx++;
            return token("relop", "=");
        case 6:
            switch (stmt[idx])
            {
            case '=':
                idx++;
                state = 7;
                break;
            default:
                state = 8;
                break;
            }
            break;
        case 7:
            return token("relop", ">=");
        case 8:
            return token("relop", ">");
        };
    }
}
int main()
{
    string stmt;
    cout << "enter a statement with following grammar:\n"
            "stmt  -->  if expr then stmt\n"
            "       |   if expr then stmt else stmt\n"
            "       |   e\n"
            "expr  -->  term relop term\n"
            "       |   term\n"
            "term  -->  id\n"
            "       |   number\nInput:";
    getline(cin, stmt);
    //cout<<stmt;
    int curr = 0;
    while (curr < stmt.length())
    {
        int val1 = curr;
        token temp = IF(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
            WS(stmt, curr);
            continue;
        }else{
            curr=val1;
        }
        int val2 = curr;
        temp = ELSE(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
           
            WS(stmt, curr);
            continue;
        }else curr = val2;
        int val3 = curr;
        temp = THEN(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
            WS(stmt, curr);
            continue;
        }else curr = val3;
        int val4=curr;
        temp = RELOP(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
            WS(stmt, curr);
            continue;
        }else curr = val4;
        int val5 = curr;
        temp = ID(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
            WS(stmt, curr);
            continue;
        }else curr = val5;
        int val6 = curr;
        temp = NUMBER(stmt, curr);
        if (temp.isValid())
        {
            temp.print();
            WS(stmt, curr);
            continue;
        }else curr = val6;
        
    //Sleep(1000);
    cout << "\ncheck your input!!!\n";
    break;
    }
}