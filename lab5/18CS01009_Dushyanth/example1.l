letter  [a-zA-Z]
id      {letter}+
%%
"+"     {printf("+\n");return 1;}
"*"     {printf("*\n");return 1;}
"("     {printf("(\n");return 1;}
")"     {printf(")\n");return 1;}
{id}    {printf("id\n");return 1;}
.       {printf("rejected\n");return 0;}
%%
int yywrap(void){return 1;}
void writer(char ch[]){
    printf("(%c)\n",&ch);
}
int main(){
    yyin = fopen("input.txt","r");
    int tkn;
    while((tkn= yylex())){
        //printf("..%d..\n",tkn);
    }
    
}