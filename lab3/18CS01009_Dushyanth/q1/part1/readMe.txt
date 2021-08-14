input to the program should be written in 'myfilea' file in same directory
Steps to execute the program:
1. flex q1a.l
2. gcc lex.yy.c
3. a.exe

Derivation of regular expression:
1*01* + 1*01*01*01* + 1*01*01*01*01*01* + .....
=> 1*01*(e + 01*01* + 01*01*01*01* + .....)
=> 1*01*(01*01*)*

sample inputs and ouputs are shown in 'examples.docx' with screen shots