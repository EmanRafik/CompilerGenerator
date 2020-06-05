%{
#include <stdio.h>
#include <bits/stdc++.h>
#include "y.tab.h"
%}

%%

//"if"         {return if;}
//"else"       {printf("else");}
//"while"      {return while;}
//"("          {printf("(");}
//")"          {printf(")");}
//"{"          {printf("{");}
//"}"          {printf("}");}
//","          {printf(",");}

[a-zA-Z][a-zA-z|0-9]*                      {return identifier;}
"-"?{[0-9]+}                               {return int_value;}
"-"?{[0-9]+}.{[0-9]+}("E"{[0-9]+}+)?       {return float_value;}
"true"|"false"                             {return boolean;}
"=="|"!="|">="|"<="|"^"|"<"|">"            {return relop;}
"&&"|"|"|"!"                               {return boolean_op;}
"boolean"                                  {return boolean_word;}
"int"                                      {return int_word;}
"float"                                    {return float_word;}
"*"|"/"                                    {return mulop;}
"+"|"-"                                    {return addop;}
";"                                        {return semi_colon;}
"="                                        {return equals;}

%%

int yywrap()
{
return 1;
}

