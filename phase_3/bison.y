%{
#include <unistd.h>
#include "stdc++.h"

using namespace std;

extern int yylex();
extern FILE *yyin;
void yyerror(const char * s);

int id_counter = 1;
typedef enum {INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE} type;
map<string, pair<int,type>> symbol_table;
ofstream outFile("javaByteCode.j");

vector<string> javaByteCode;
vector<int> *make_list(int index);
vector<int> *merge(vector<int> *p1, vector<int> *p2);
void back_patch(vector<int> *p, int index);
void declare_variable (string id_str, int id_type);
void addLine(string s);
void print_output();
bool isInteger(float val);
%}

%code requires {
	#include <vector>
	#include <map>
	using namespace std;
}

%start method_body

%union{
	int int_val;
	float float_val;
	char * id_val;
	struct bool_expression {
		vector<int> *true_list;
		vector<int> *false_list;
	};
	struct expression_type {
        	int type;
        };
        int id_type;
	char* operation;
	bool boolean_val;
	struct statement_type{
	vector<int> *next_list;
	};
}

%token <id_val> identifier
%token <int_val> int_value
%token <float_val> float_value
%token <boolean_val> boolean
%token <operation> relop
%token <operation> boolean_op //and, or , not
%token semi_colon
%token equals
%token int_word
%token float_word
%token boolean_word
%token <operation> mulop
%token <operation> addop
%token <float_val> num

%type <id_type> primitive_type
%type <bool_expression> boolean_expression
%type <expression_type> expression
%type <expression_type> simple_expression
%type <expression_type> term
%type <expression_type> factor
%type <statement_type> statement_list
%type <statement_type> statement
%type <statement_type> while
%type <statement_type> if
%type <statement_type> N
%type <int_type> create_label
%type <operation> sign

%%
method_body: statement_list;

statement_list: statement_list statement | statement;

statement: declaration 
| if {$$.next_list = $1.next_list}
| while {$$.next_list = $1.next_list} 
| assignment;

primitive_type:
	int_word {$$ = INT_TYPE;}
	| float_word {$$ = FLOAT_TYPE;}
	| boolean_word {$$ = BOOLEAN_TYPE;};

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
		back_patch($1.false_list, $3);
		$$.true_list = merge($1.true_list, $4.true_list);
		$$.false_list = $4.false_list;
	}
	else if(strcmp($2,"&&") == 0){
		back_patch($1.true_list,$3);
		$$.true_list = $4.true_list;
		$$.false_list = merge($1.false_list, $4.false_list);
	}
}
//case of NOT
| boolean_op boolean_expression{
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
	string op_type= "";
        if(strcmp($2,"==")){
        op_type = "icmpeq";
        }
        else if(strcmp($2,">=")){
        op_type = "icmpge";
        }
        else if(strcmp($2, ">")){
        op_type = "icmpgt";
        }
        else if(strcmp($2, "<=")){
        op_type = "icmple";
        }
        else if(strcmp($2, "<")){
        op_type = "icmplt";
        }
        else if (strcmp($2, "!=")){
        op_type = "icmpne";
        }
        addLine("if_"+op_type+" ");
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

while: "while" "(" create_label boolean_expression ")" "{" create_label statement "}"
{
	back_patch($4.true_list, $7);
	back_patch($8.next_list, $3);
	$$.next_list = $4.false_list;
	addLine("goto " + to_string($3));
};

if: "if" "(" boolean_expression ")" "{" create_label statement "}" N "else" "{" create_label statement "}"
{
back_patch($3.true_list,$6);
back_patch($3.true_list,$12);
vector<int> *temp;
temp = merge($7.next_list,$9.next_list);
$$.next_list = merge(temp,$13.next_list);
};

N: {
$$.next_list = make_list(javaByteCode.size())
addLine("goto ");
};

assignment:
	identifier equals expression semi_colon {
		string id_str($1);
                if(is_valid_id(id_str)){
			if($3.type == symbol_table[id_str].second) {
				if($3.type == INT_TYPE) {
					addLine("istore " + to_string(symbol_table[id_str].first));
				}
				else if ($3.type == FLOAT_TYPE) {
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
	
expression: simple_expression 
{$$.type = $1.type};
//| simple_expression relop simple_expression

simple_expression: 
term {$$.type = $1.type}
| sign term {
	$$.type = $2.type;
	if (strcmp($1,"-")==0)
	{
		if ($2.type == INT_TYPE)
		{
			addLine("ineg");
		}
		else
		{
			addLine("fneg");
		}
	}
}
| simple_expression addop term
{
	if ($1.type == FLOAT_TYPE || $3.type == FLOAT_TYPE)
	{
		$$.type = FLOAT_TYPE;
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
		$$.type = INT_TYPE;
		if (strcmp($2,"+")==0)
		{
			addLine("iadd");
		}
		else if (strcmp($2,"-")==0)
		{
			addLine("isub");
		}
	}
};

term: 
	factor {
		$$.type = $1.type;
	}
| term mulop factor {
	if ($1.type == FLOAT_TYPE || $3.type == FLOAT_TYPE)
	{
		$$.type = FLOAT_TYPE;
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
		$$.type = INT_TYPE;
		if (strcmp($2,"*")==0)
		{
			addLine("imul");
		}
		else if (strcmp($2,"/")==0)
		{
			addLine("idiv");
		}
	}
	
}

factor: 
	identifier {
		string id_str($1);
		if (is_valid_id(id_str)) 
		{
			if (symbol_table[id_str].second == INT_TYPE)
			{
				$$.type = INT_TYPE;
				addLine("iload " + to_string(symbol_table[id_str].first));
			}
			else
			{
				$$.type = FLOAT_TYPE;
				addLine("fload " + to_string(symbol_table[id_str].first));
			}
		}
		else
		{
			string error = id_str + " isn't declared in this scope";
            yyerror(error.c_str());
		}
	}
	| num {
		if (isInteger(atof(num))) 
		{
			$$.type = INT_TYPE;
		}
		else
		{
			$$.type = FLOAT_TYPE;
		}
		addLine("ldc " + $1)
	}
	| '(' expression ')' {$$.type = $2.type};

create_label: {
$$ = javaByteCode.size();
};

sign: '+' | '-';
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
  yyparse();
  print_output();
}

//makelist --> creates and returns a new list that only contains an index to an instruction
vector<int> *make_list(int index)
{
  vector<int> *vec = new vector<int>());
  vec->push_back(index);
  return vec;
}

//merge --> concatenates p1 and p2 and returns the concatenated list
vector<int> *merge(vector<int> *p1, vector<int> *p2)
{
  if(p1 == NULL && p2 == NULL){
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
    vector<int> *vec = new vector<int>(*p1);
    vec->insert(vec->end(),p2->begin(),p2->end());
    return vec;
  }
}

//backpatch --> inserts index as target label for each instruction in p
void back_patch(vector<int> *p, int index)
{
  if(p == null){
    return;
  }
  for(int i=0; i<p->size(); i++){
    int_val = (*p)[i];
    javaByteCode[inst_val] = javaByteCode[inst_val] + to_string(index);
  }
}

//adds a new line in the javaByteCode list
void addLine(string s)
{
  javaByteCode.push_back(s);
}

//checks if the id is already identified or not
bool is_valid_id(string id)
{
  return (symbol_table.find(id) != symbol_table.end());
}

void declare_variable (string id_str, int id_type)
{
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
void print_output()
{
  for ( int i = 0 ; i < javaByteCode.size() ; i++)
  {
    outFile<<javaByteCode[i]<<endl;
  }
}

//check if number is integer
bool isInteger(float val)
{
    int truncated = (int)val;
    return (val == truncated);
}



