%{
int lines=1;
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"
%}
whitespace [ \t]+
letter     [a-zA-Z]
digit      [0-9]
inum       ({digit}+)
fnum       {inum}"."{inum}
l_or_d     ({letter}|{digit})
identifier ({letter}{l_or_d}*)
incr       "++"
decr       "--"
operator   "-"|"+"|"*"|"/"
opAssign   ({operator}=)
relop      [><]=?|[!=]=
seperator  [{}();,]
%%
int             {
                    printf("%s<%sint,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
float           {
                    printf("%s<%sfloat,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
if              {
                    printf("%s<%sif,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
else            {
                    printf("%s<%selse,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
while           {
                    printf("%s<%swhile,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
for             {
                    printf("%s<%sfor,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
read            {
                    printf("%s<%sread,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
print           {
                    printf("%s<%sprint,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
main            {
                    printf("%s<%smain,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{whitespace}    {return 1;}
\n              {lines++;}
{identifier}    {
                    printf("%s<%sidentifier,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{inum}          {
                    printf("%s<%sinteger,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{fnum}          {
                    printf("%s<%sfloating_point,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
=               {
                    printf("%s<%s=,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{incr}          {
                    printf("%s<%s++,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{decr}          {
                    printf("%s<%s--,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{opAssign}      {
                    printf("%s<%sop&assign,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{relop}         {
                    printf("%s<%srelop,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{operator}      {
                    printf("%s<%sarth_op,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
{seperator}     {
                    printf("%s<%sseperator,%s%s>%s\n",KGRN,KNRM,yytext,KGRN,KNRM);
                    return 1;
                }
\n              {} 
.               {printf("unexpected input\n");return 0;}
%%
int yywrap(void){return 1;}
int main(){
    int token;
    yyin = fopen("myfile","r");
    while((token=yylex())!=0){}
}