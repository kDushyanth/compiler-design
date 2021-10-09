%{ 
 #include<stdio.h> 
 #include "calc.tab.h" 
 extern int yylval;
%}
%option yylineno 
%%
[0-9]+  {yylval=atoi(yytext);/*printf("%d..\n",yylval);*/return NUM;}
"+"     {return PLUS;}
"-"     {return MINUS;}
"*"     {return MUL;}
"/"     {return DIV;}
[ \t\n]   {}
%%
int yywrap(void) {return 1;}