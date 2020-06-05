%{
#include <stdio.h>
#include <bits/stdc++.h>
#include "y.tab.h"
%}

%%

//"if"         {return if;}
//"else"       {printf("else");}
//"while"      {return while;}
//"boolean"    {printf("boolean");}
//"int"        {printf("int");}
//"float"      {printf("float");}
[a-zA-Z][a-zA-z|0-9]*      {return identifier;}
[0-9]*       {printf("Number");}
"=="|"!="|">="|"<="|"^"|"<"|">"       {return relop;}
"*"|"/"      {return mulop;}
"+"|"-"       {return addop;}
"("          {printf("(");}
")"          {printf(")");}
"{"          {printf("{");}
"}"          {printf("}");}
";"          {printf(";");}
","          {printf(",");}
"="          {return equals;}

%%

int yywrap()
{
return 1;
}

