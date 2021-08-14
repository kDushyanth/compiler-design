%{
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"
%}
whitespace [ \t]+
letter     [a-zA-Z]
digit      [0-9]
digits     {digit}+
number     {digits}("."{digits})?("E"[+-]?{digits})?
l_or_d     ({letter}|{digit})
identifier ({letter}{l_or_d}*)
relop      ([><=])|([><]=)|("<>")
%%
if              {
                    printf("%s<%sif,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
else            {
                    printf("%s<%selse,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
then              {
                    printf("%s<%sthen,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{identifier}    {
                    printf("%s<%sidentifier,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{number}        {
                    printf("%s<%snumber,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{relop}         {
                    printf("%s<%srelop,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{whitespace}    {return 1;}
\n              {}
.               {printf("\nunexpected input\n");return 0;}
%%
int yywrap(void){return 1;}
int main(){
    int token;
    yyin = fopen("myfile","r");
    int counter=0;
    while((token=yylex())!=0){}
}