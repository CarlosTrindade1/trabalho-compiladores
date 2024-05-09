#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names {
    UNDEF, // 0
    ID, // 1
    BOOLEAN, // 2
    CLASS, // 3
    ELSE, // 4
    EXTENDS, // 5
    FALSE, // 6
    IF, // 7
    INT, // 8
    LENGTH, // 9
    MAIN, // 10
    NEW, // 11
    PUBLIC, // 12
    RETURN, // 13
    STATIC, // 14
    STRING, // 15
    SOUT, // 16
    THIS, // 17
    TRUE, // 18
    VOID, // 19
    WHILE, // 20
    OP, // 21
    AND, // 22
    LT, // 23
    GT, // 24
    PLUS, // 25
    MINUS, // 26
    MULT, // 27
    DIV, // 28
    ATRIB, // 29
    EQ, // 30
    NEQ, // 31
    NOT, // 32
    SEP, // 33
    L_PAREN, // 34
    R_PAREN, // 35
    L_BRACKET, // 36
    R_BRACKET, // 37
    L_KEY, // 38
    R_KEY, // 39
    SEMI, // 40
    DOT, // 41
    COMMA, // 42
    NUMBER, // 43
    INTEGER_LITERAL, // 44
    CMT, // 45
    START_OF_CMT, // 46
    END_OF_CMT, // 47
    END_OF_LINE, // 48
    END_OF_FILE // 49
};

class Token {
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name) {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l) {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr) {
            this->name = name;
            attribute = attr;
        }
};
