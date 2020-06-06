%{
#include "y.tab.h"
#include <bits/stdc++.h>
%}

num [0-9]+

%%
"boolean"                                  {return boolean_word;}
"int"                                      {return int_word;}
"float"                                    {return float_word;}
"if"                                       {return if_term;}
"else"                                     {return else_term;}
"while"									   {return while_token;}
"true"|"false"                             {if(!strcmp(yytext,"true")){
                                                yylval.boolean_val = 1;
                                              } else {
                                                yylval.boolean_val = 0;
                                              }
                                              return boolean;
                                            }

[a-zA-Z][a-zA-z|0-9]*                      {yylval.id_val = strdup(yytext);
                                            return identifier;}

"-"?{num}                                  {yylval.int_val = atoi(yytext);
                                            return int_value;}

"-"?{num}.{num}("E"{num})?                 {yylval.float_val = atof(yytext);
                                            return float_value;}

"=="|"!="|">="|"<="|"^"|"<"|">"            {yylval.operation = strdup(yytext);
                                            return relop;}

"&&"|"||"|"!"                              {yylval.operation = strdup(yytext);
                                            return boolean_op;}

"*"|"/"                                    {yylval.operation = strdup(yytext);
                                            return mulop;}

"+"|"-"                                    {yylval.operation = strdup(yytext);
                                            return addop;}

";"                                        {return semi_colon;}
"="                                        {return equals;}
"("                                        {return round_open;}
")"                                        {return round_close;}
"{"                                        {return curly_open;}
"}"                                        {return curly_close;}

%%

int yywrap()
{
return 1;
}

