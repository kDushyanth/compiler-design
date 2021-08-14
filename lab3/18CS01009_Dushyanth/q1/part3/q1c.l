pattern (0|(1(01*0)*1))*
%%
{pattern} {printf("accepted\n");return 1;}
.*        {printf("rejected\n");return 0;}
%%
int yywrap(void){return 1;}
int main(){
    yyin = fopen("myfilec","r");
    int token = yylex();
    printf("string:%s\nlength:%d",yytext,yyleng);
}