input to the program should be written in 'myfile' file in same directory
Steps to execute the program:
1. flex q2.l
2. gcc lex.yy.c
3. a.exe

sample inputs and outputs are shown in 'examples.docx' with screen shots, and explanation

Note: 
1.longest matching prefix is found. If more than one match is found with same length then the match corresponding to
first rule written in rules section is considered.
2.If the action returns some value this is returned by the calling function 'yylex()'
3.If the action doesn't return anything, the Lexical Analyzer continues with the next unconsumed input without returning.
