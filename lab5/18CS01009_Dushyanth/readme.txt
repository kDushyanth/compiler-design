Consider first grammar:
Lexical analyser for this grammar is in ‘example1.l’ file.
The grammar is left factored and left-recursion is removed to make the grammar LL(1).
The processed grammar is placed in ‘grammarll1.txt’ file and the corresponding First and Follow sets are in ‘firstfollow1.txt’ file.
Format for contents of ‘grammarll1.txt’:
1.	Enter number of terminals
2.	Enter the terminals, each in a new line
3.	Enter number of non-terminals
4.	Enter the non-terminals each in a new line
5.	Enter all productions in below format:
Consider: E -> T*F | T+F | F | epsilon 
Enter:       E 4 3 T * F 3 T + F 1 F 1 #
#: denotes epsilon
Format for contents of ‘firstfollow1.txt’:
1.	Enter Follow sets in the following format for each non-terminal:
Consider: Follow(E) = {a ,b ,$, g}
		Enter:       E 4 a b $ g
2.	Enter First Sets in the following formats for each non-terminal, terminal, epsilon:
Consider: First(E) = {a, b, #, g}
Enter:       E 4 a b # g
Consider: First(a) = {a}
Enter:        a 1 a
For epsilon enter: # 1 #

After settingup 'grammarll1.txt' and 'firstfollow1.txt' files place the input string in 'input.txt' file and execute 'parser.cpp' as folllows:
1. flex example1.l
2. gcc lex.yy.c
3. a.exe > tkn.txt 
the above step redirects the output(tokens) to 'tkn.txt' file
4. g++ parser.cpp
5. a.exe
    enter file name that contains grammar: grammarll1.txt
    enter file name that contains first and follow sets: firstfollow1.txt

The inputs considered for execution and the corresponding outputs were places in './InputsOutputs/grammar1' folder.

The above steps were similarly applied for second grammar.

INPUTS-OUTPUTS
Grammar-1
    input-1: (a+b)*(c+d)+z
    output-1: parsing table, configuration of parser with actions performed, verdict (either success/ invalid syntax error)
    in this case the output is 'success'

    The lexical analyzer can reject the input string if it encounters invalid token
    
    input-1: (a+b)*(c*d)++
    output-1: invalid syntax due to '++'

Grammar-2
    input-1,output-1: the parser successfully parsed the program
    input-2,output-2: invalid token due to "str"+"str" in 6th line of program

left factoring, removing left recursion and computing first and follow sets is done manually