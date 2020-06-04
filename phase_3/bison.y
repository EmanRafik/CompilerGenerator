%{
#include<stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>
}%

%token Line
%token Ex
%token ID
%start Line

%% 

Line : Line EX | EX ;
EX : ID '+' ID {printf("line")};
ID : ;
%%

#include "lex.yy.c"  
   
void yyerror(char * s) 
/* yacc error handler */
{    
 fprintf (stderr, "%s\n", s); 
}  
   
int main(void)  
{
  FILE *f;
  f = fopen("input.txt", "r");
  yyin = f;
  return yyparse(); 
}   