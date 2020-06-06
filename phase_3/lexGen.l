%{
#include "y.tab.h"
%}

num [0-9]+

%%
"boolean"                                  {return boolean_word;}
"int"                                      {return int_word;}
"float"                                    {return float_word;}
"true"|"false"                             {return boolean;}
[a-zA-Z][a-zA-z|0-9]*                      {return identifier;}
"-"?{num}                                  {return int_value;}
"-"?{num}.{num}("E"{num})?                 {return float_value;}
"=="|"!="|">="|"<="|"^"|"<"|">"            {return relop;}
"&&"|"||"|"!"                              {return boolean_op;}
"*"|"/"                                    {return mulop;}
"+"|"-"                                    {return addop;}
";"                                        {return semi_colon;}
"="                                        {return equals;}

%%

int yywrap()
{
return 1;
}

