%{
#include<stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>


using namespace std;
vector<string> javaByteCode;
vector<int> *make_list(int index);
vector<int> *merge(vector<int> *p1, vector<int> *p2);
void back_patch(vector<int> *p, int index);
}%

%start boolean_expression
%union{
	struct boolean_expression {
	vector<int> *true_list;
	vector<int> *false_list
	};
}
%token Line
%token Ex
%token ID
%type <bexpr_type> boolean_expression

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

//makelist --> creates and returns a new list that only contains an index to an instruction
vector<int> *make_list(int index){
vector<int> *vec = new vector<int>());
vec.push_back(index);
return vec;
}

//merge --> concatenates p1 and p2 and returns the concatenated list
vector<int> *merge(vector<int> *p1, vector<int> *p2){
if(p1 == null && p2 == null){
vector<int> *vec = new vector<int>();
return vec;
}
else if(p1 == null){
return p2;
}
else if(p2 == null){
return p1;
}
else{
vector<int> *vec = new vector<int>(p1);
vec->insert(vec->end(),p2->begin(),p2->end());
return vec;
}
}

//backpatch --> inserts index as target label for each instruction in p
void back_patch(vector<int> *p, int index){
if(p == null){
return;
}
for(int i=0; i<p->size(); i++){
	inst_val = (*p)[i];
	javaByteCode[inst_val] = javaByteCode[inst_val] + "label_"+ to_string(index);
}

}
