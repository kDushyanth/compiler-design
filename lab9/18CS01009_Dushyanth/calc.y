%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int yylex();
void yyerror(char *s);

%}
%token NUM PLUS MINUS MUL DIV
%start S 

%left PLUS MINUS
%left MUL DIV

%%
S : E { $$ = $1; printf("value of expression %d\n",$$);}
  ;
E : E PLUS T {$$ = $1 + $3;}
  | E MINUS T {$$ = $1 - $3;}
  | T     {$$ = $1;}
  ;
T : T MUL F {$$ = $1 * $3;}
  | T DIV F {$$ = $1 / $3;}
  | F       {$$ = $1;}
  ;
F : NUM   {$$ = $1;}
  ;


%%

extern int yylex();
extern FILE *yyin;
extern int yyparse();
extern int yylineno;

void yyerror(char *s){
	printf("Error: %s at line %d\n",s, yylineno);
	exit(-1);
}
int main(){
	
    yyin = fopen("input1.txt","r");
	yyparse();
	printf("Accepted\n");
	return 0;
}