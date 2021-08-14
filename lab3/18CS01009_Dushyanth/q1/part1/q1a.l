pattern    (1*01*(01*01*)*)
%%
{pattern}    {printf("accepted\n");return 1;}
.*           {printf("rejected");return 0;}
%%
int yywrap(void){return 1;}
int main(){
    yyin = fopen("myfilea","r");
    int token = yylex();
    if(token)printf("string:%s\nlength:%d\n",yytext,yyleng);
}