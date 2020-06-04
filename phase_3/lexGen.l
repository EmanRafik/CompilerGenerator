%{
#include<stdio.h>
%}
%%
"if" {printf("if");}
"else" {printf("else");}
"while" {printf("while");}
"boolean" {printf("boolean");}
"int" {printf("int");}
"float" {printf("float");}
[a-zA-Z][a-zA-z|0-9]* {printf("Identifier");}
[0-9]* {printf("Number");}
"=="|"!="|">="|"<="|"^"|"<"|">" {printf("relop");}
"*"|"/" {printf("mulop");}
"+"|"" {printf("addop");}
"(" {printf("(");}
")" {printf(")");}
"{" {printf("{");}
"}" {printf("}");}
";" {printf(";");}
"," {printf(",");}
"=" {printf("assign");}
%%
int yywrap()
{
return 1;
}
main()
{
printf("Enter a string of code\n");
yylex();
}
