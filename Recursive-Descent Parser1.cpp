#include <iostream>
#include <string>
/*
<expr> ::= <expr>+<term> | <expr>-<term> | <term>
<term> ::= <term>*<factor> | <term>/<factor> | <factor>
<factor> ::= (<expr>) |<digit>
<digit> ::= 0|1|2|3

removing left recursion problem...

<expr> ::= <term><expr1>
<expr1> ::= +<term><expr1> | -<term><expr1> | empty
<term> ::= <factor><term1>
<term1> ::= *<factor><term1> | /<factor><term1> | empty
<factor> ::= (<expr>) | <digits>
<digits> ::= 0 | 1 | 2 | 3

simplified plus dollar sign

<start> ::= <expr>$
<expr> ::= <term><expr1>
<expr1> ::= {(+|-)<term><expr1>}
<term> ::= <factor><term1>
<term1> ::= {(*|/)<factor><term1>}
<factor> ::= (<expr>) | <digits>
<digits> ::= 0 | 1 | 2 | 3
*/

#define DOLLAR_CODE '$'
#define PLUS_CODE '+'
#define MINUS_CODE '-'
#define MULT_CODE '*'
#define DIV_CODE '/'
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
using namespace std;

//global variables
string str;
bool valid;
char NEXTTOKEN;

void lex();
void start();
void expr();
void expr1();
void term();
void term1();
void factor();
void digits();
void error();

int main(void){
    int n;
    string input;
    cout << "Input the number of test cases: ";
    getline(cin, input);
    try{
        n=stoi(input);
    }catch(const exception& e){
        cout << "INVALID INPUT\nPROGRAM TERMINATED" << endl;
        return 0;
    }
    cout << "\n\nInput the test cases separated by a newline:\n" << endl;
    while(n >0){
        getline(cin, input);
        str = input;
        valid  = true;
        lex();
        start();
        n--;
    }
    return 0;
}
void error(){
    if(valid){
        valid = false;
        cout << "\t\t\t\tINVALID" << endl;
    }
}

void lex(){
    if(str.size()==0){
        NEXTTOKEN=0;
    }else{
        NEXTTOKEN = str[0];
        str.erase(str.begin(), str.begin()+1);
    }
}

void start(){
    expr();
    if(NEXTTOKEN  == DOLLAR_CODE && str.size()==0 && valid)
        cout << "\t\t\tVALID" << endl;
    else
        error();
}

void expr(){
    term();
    expr1();
}

void expr1(){
    while(NEXTTOKEN == PLUS_CODE || NEXTTOKEN  == MINUS_CODE){
        lex();
        term();
        expr1();
    }
} 

void term(){
    factor();
    term1();
}

void term1(){
    while(NEXTTOKEN == MULT_CODE || NEXTTOKEN == DIV_CODE){
        lex();
        factor();
        term1();
    }
}

void factor(){
    if(NEXTTOKEN == LEFT_PAREN){
        lex();
        expr();
        if(NEXTTOKEN  == RIGHT_PAREN)
            lex();
        else
            error();
    }else
        digits();
}

void digits(){
    if(NEXTTOKEN >= '0' && NEXTTOKEN <=  '3'){
        lex();
    }else{
        error();
    }
}
