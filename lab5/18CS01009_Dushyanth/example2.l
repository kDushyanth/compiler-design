letter     [a-zA-Z]
digit      [0-9]
digits     {digit}+
ic         {digits}
fc         {digits}"."{digits}
l_or_d     ({letter}|{digit})
identifier ({letter}{l_or_d}*)
str        \"{l_or_d}*\"
sep        [ \t\n]+
%%
{sep}   {return 1;}
"+"     {printf("+\n");return 1;}
"-"     {printf("-\n");return 1;}
"*"     {printf("*\n");return 1;}
"/"     {printf("/\n");return 1;}
"="     {printf("=\n");return 1;}
">"     {printf(">\n");return 1;}
"<"     {printf("<\n");return 1;}
"("     {printf("(\n");return 1;}
")"     {printf(")\n");return 1;}
"{"     {printf("{\n");return 1;}
"}"     {printf("}\n");return 1;}
":="     {printf(":=\n");return 1;}
";"     {printf(";\n");return 1;}
"and"     {printf("and\n");return 1;}
"else"     {printf("else\n");return 1;}
"end"     {printf("end\n");return 1;}
{ic}     {printf("ic\n");return 1;}
"if"     {printf("if\n");return 1;}
"int"     {printf("int\n");return 1;}
"do"     {printf("do\n");return 1;}
{fc}     {printf("fc\n");return 1;}
"float"     {printf("float\n");return 1;}
"not"     {printf("not\n");return 1;}
"or"     {printf("or\n");return 1;}
"print"     {printf("print\n");return 1;}
"prog"     {printf("prog\n");return 1;}
"scan"     {printf("scan\n");return 1;}
{str}     {printf("str\n");return 1;}
"then"     {printf("then\n");return 1;}
"while"     {printf("while\n");return 1;}
{identifier}     {printf("id\n");return 1;}
.           {printf("invalid token");return 0;}
%%
int yywrap(void){return 1;}
int main(){
    yyin = fopen("input2.txt","r");
    while(yylex()){

    }
}