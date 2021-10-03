%{ 
 #include<stdio.h> 
 #include "lab8.tab.h" 
 extern int yylval;
%}
%option yylineno 
digit [0-9] 
digits {digit}+
letter [a-zA-Z]
l_or_d {letter}|{digit}
%% 
"//".*"\n" {}
"and" { return AND; }
":=" { return ASSIGN;}
":" {return COLON;}
"," {return COMMA;}
"def" {return DEF;}
"/" {return DIV;}
"." {return DOT;}
"else" {return ELSE;} 
"end" {return END;}
"=" {return EQ;}
"exit" {return EXITLOOP;}
"float" {return FLOAT;}
{digits}"."{digits} {return FLOAT_CONST;}
%[dfs] {return FORMAT;}
"from" {return FROM;}
"fun" {return FUN;}
">=" {return GE;}
"global" {return GLOBAL;}
">" {return GT;}
"if" {return IF;}
"int" {return INT;}
{digits} {return INT_CONST;}
"(" {return LEFT_PAREN;}
"[" {return LEFT_SQ_BKT;}
"<=" {return LE;}
"<" {return LT;}
"-" {return MINUS;}
"mod" {return MOD; }
"*" {return MULT; } 
"<>" {return NE; }
"not" {return NOT;}
"null" {return NUL;}
"or" {return OR;}
"+" {return PLUS;}
"print" {return PRINT;}
"product" {return PRODUCT;}
"read" {return READ;}
"return" {return RETURN;}
"->" {return RETURNS;}
")" {return RIGHT_PAREN;}
"]" {return RIGHT_SQ_BKT;}
";" {return SEMICOLON;}
"skip" {return SKIP;}
"step" {return STEP;}
"to" {return TO;}
"while" {return WHILE;}
{letter}{l_or_d}+ {return ID;}
\".*\" {return STRING;}
[\n\t ] {}; 
%%
int yywrap(void) {return 1;}