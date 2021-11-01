#include <iostream>
#include <string>
using namespace std;

/*
Attention!!
The given grammar:
    <expr> ::= +<num> | -<num> | <num>
    <num> ::= <num><digits> | <digits>
    <digits> ::= <digit> | <digit>.<digit>
    <digit> ::= 0|1|2|3|4|5|6|7|8|9
accepts some strings with 2 or more decimals points (e.g. "5.55.55").

The grammar has been revised shown below (plus dollar sign):
    <start> ::= <expr>$
    <expr> ::= -<num> | +<num> | <num>
    <num> ::= <digits>.<digits> | <digits>
    <digits> ::= <digit> | <digit><digits>
    <digit> ::= 0 | 1 | ... | 9

simplified version

    <start> ::= <expr>$
    <expr> ::= {(+|-)}<num>
    <num> ::= <digits>(.<digits>)?
    <digits> ::= <digit><digits>?
    <digit> ::= 0 | 1 | ... | 9

NOTE: Input ".001$", ".2$" and the likes(inputs where there is no digit/s before the decimal) are INVALID.
*/
#define DOLLAR_CODE '$'
#define PLUS_CODE '+'
#define MINUS_CODE '-'
#define DECIMAL '.'
string str;
bool valid;
char NEXTTOKEN;

void start();
void lex();
void error();
void expr();
void num();
void digits();
void digit();

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
        NEXTTOKEN = 0;
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
    if(NEXTTOKEN == PLUS_CODE || NEXTTOKEN == MINUS_CODE){
        lex();
    }
    num();
}

void num(){
    digits();
    if(NEXTTOKEN == DECIMAL){
        lex();
        digits();
    }
}

void digits(){
    digit();
    if(NEXTTOKEN>='0' && NEXTTOKEN<='9' ){
        digits();
    }
}

void digit(){
    if(NEXTTOKEN  >= '0' && NEXTTOKEN  <= '9'){
        lex();
    }else{
        error();
    }
}
