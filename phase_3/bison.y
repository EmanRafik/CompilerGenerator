%{
#include <stdio.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <vector>
#include <map>
using namespace std;

int id_counter = 1;
typedef enum {INT_TYPE, FLOAT_TYPE} type;
map<string, pair<int,type>> symbol_table;
ofstream outFile("javaByteCode.j");

vector<string> javaByteCode;
vector<int> *make_list(int index);
vector<int> *merge(vector<int> *p1, vector<int> *p2);
void back_patch(vector<int> *p, int index);
void addLine(string s);
void print_output();
bool isInteger(double val);
}%

%start declaration

%union{
	int int_type;
	float float_type;
	char * id_type;
	struct bool_expression {
		vector<int> *true_list;
		vector<int> *false_list;
	};
	struct expression {
        	int val;
        };
	char* operation;
	bool boolean_type;
	int sType;
}

%token <id_type> id
%token <int_type> int
%token <float_type> float
%token <boolean_type> boolean
%token <operation> relop
%token <operation> boolean_op //and, or , not
%token semi_colon
%token equals
%token <mulop> mulop
%token <addop> addop

%type <bool_expression> boolean_expression
//%type <expression> expression
%type <term> sType
%type <factor> sType
%type <simple_expression> sType
%type <expression> sType

%%
declaration:
	primitive_type identifier semi_colon {
		string id_str($2);
		if($1 == INT_TYPE){
			declare_variable (id_str, INT_TYPE);
		} else if ($1 == FLOAT_TYPE){
			declare_variable (id_str, FLOAT_TYPE);
		}
	};

boolean_expression :
//case of AND, OR
 boolean_expression boolean_op create_label boolean_expression {  //create label is still not ready
	if(strcmp($2,"||") == 0){
		backpatch($1.false_list, $3);
		$$.true_list = merge($1.true_list, $4.true_list);
		$$.false_list = $4.false_list;
	}
	else if(strcmp($2,"&&") == 0){
		backpatch($1.true_list,$3);
		$$.true_list = $4.true_list;
		$$.false_list = merge($1.false_list, $4.false_list);
	}
}
//case of NOT
| bool_op boolean_expression{
	$$.true_list = $2.false_list;
	$$.false_list = $2.true_list;
}
| boolean_expression{
	$$.true_list = $1.true_list;
	$$.false_list = $1.false_list;
}
//case of RELOP
| expression relop expression {
	$$.true_list = make_list(javaByteCode.size());
	$$.false_list = make_list(javaByteCode.size()+1);
	// add line and go here if condition is true
	addLine("goto ")
}
//case of TRUE and FALSE
| boolean{
	if($1){
		$$.true_list = make_list(javaByteCode.size());
		addLine("goto ");
	}
	else{
		$$.false_list = make_list(javaByteCode.size());
		addLine("goto ");
	}
};


while: 'while' '(' M expression ')' '{' M statement '}'
{
	back_patch($4.true_list, $7);
	back_patch($8.next_list, $3);
	$$.next_list = $4.false_list;
	addLine("goto " + to_string($3));
};

assignment:
	id equals expression semi_colon {
		string id_str($1);
                if(is_valid_id(id_str)){
			if($3.sType == symbol_table[id_str].second) {
				if($3.sType == INT_TYPE) {
					addLine("istore " + to_string(symbol_table[id_str].first));
				}
				else if ($3.sType == FLOAT_TYPE) {
					addLine("fstore " + to_string(symbol_table[id_str].first));
				}
			} else {
				string error = "identifier and expression are not of the same type";
				yyerror(error.c_str());
			}
                } else {
                	string error = id_str + " isn't declared in this scope";
                        yyerror(error.c_str());
                }
	};

expression: simple_expression {$$.sType = $1.sType};
| simple_expression relop simple_expression

simple_expression: 
term {$$.sType = $1.sType};
| sign term {
	if (strcmp($1,"-")==0)
	{
		if ($2.sType == INT_TYPE)
		{
			addLine("ineg");
		}
		else
		{
			addLine("fneg");
		}
	}
};
| simple_expression addop term
{
	if ($1.sType == FLOAT_TYPE || $3.sType == FLOAT_TYPE)
	{
		$$.sType = FLOAT_TYPE;
		if (strcmp($2,"+")==0)
		{
			addLine("fadd");
		}
		else if (strcmp($2,"-")==0)
		{
			addLine("fsub");
		}
	}
	else
	{
		$$.sType = INT_TYPE;
		if (strcmp($2,"+")==0)
		{
			addLine("iadd");
		}
		else if (strcmp($2,"-")==0)
		{
			addLine("isub");
		}
	}
}
term: 
	factor {
		$$.sType = $1.sType;
	};
| term mulop factor {
	if ($1.sType == FLOAT_TYPE || $3.sType == FLOAT_TYPE)
	{
		$$.sType = FLOAT_TYPE;
		if (strcmp($2,"*")==0)
		{
			addLine("fmul");
		}
		else if (strcmp($2,"/")==0)
		{
			addLine("fdiv");
		}
	}
	else
	{
		$$.sType = INT_TYPE;
		if (strcmp($2,"*")==0)
		{
			addLine("imul");
		}
		else if (strcmp($2,"/")==0)
		{
			addLine("idiv");
		}
	}
	
};
factor: 
	id {
		string id_str($1);
		if (is_valid_id(id_str)) 
		{
			if (symbol_table[id_str].second == INT_TYPE)
			{
				$$.sType = INT_TYPE;
				addLine("iload " + to_string(symbol_table[id_str].first));
			}
			else
			{
				$$.sType = FLOAT_TYPE;
				addLine("fload " + to_string(symbol_table[id_str].first));
			}
		}
		else
		{
			string error = id_str + " isn't declared in this scope";
            yyerror(error.c_str());
		}
	};
	| num {
		if (isInteger(atof(num))) 
		{
			$$.sType = INT_TYPE;
		}
		else
		{
			$$.sType = FLOAT_TYPE;
		}
		addLine("ldc " + $1)
	};
	| '(' expression ')' {$$.sType = $2.sType};
sign: '+' | '-'

Line : Line EX | EX ;
EX : ID '+' ID {printf("line")};
ID : ;
%%


void yyerror(char * s)
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

//adds a new line in the javaByteCode list
void addLine(string s){
  javaByteCode.push_back(s);
}

//checks if the id is already identified or not
bool is_valid_id(string id) {
  return (symbol_table.find(id) != symbol_table.end());
}

void declare_variable (string id_str, int id_type) {
 	if (is_valid_id(id_str)) {
		string error = id_str + " was declared before";
		yyerror(error.c_str());
	} else {
		if (id_type == INT_TYPE) {
			addLine("iconst_0\nistore " + to_string(id_counter));
		} else if (id_type == FLOAT_TYPE) {
			addLine("iconst_0\nistore " + to_string(id_counter));
		}
		symbol_table[id_str] = make_pair (id_counter++, (type)id_type);
	}
}

//print java byte code
void print_output(){
  for ( int i = 0 ; i < javaByteCode.size() ; i++)
  {
    outFile<<javaByteCode[i]<<endl;
  }
}

//check if number is integer
bool isInteger(double val)
{
    int truncated = (int)val;
    return (val == truncated);
}
