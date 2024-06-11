#include <iostream>
#include "parser.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[]) {
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2) {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    Parser* parser = new Parser(argv[1]);

    parser->run();

    delete parser;
    
    // char* file_name = argv[1];

    // Scanner* scanner = new Scanner(file_name);
    
    // allocVetor();

    // Token* token;
    
    // do {
    //     token = scanner->nextToken();
        
    //     print(token);

    // } while (token->name != END_OF_FILE);

    // cout << endl;

    // freeVetor();

    // delete scanner;
    
    return 0;
}

void allocVetor() {
    vet = new string[50];

    vet[0] = "UNDEF";//0
    vet[1] = "ID";//1
    vet[2] = "BOOLEAN";//2
    vet[3] = "CLASS";//3
    vet[4] = "ELSE";//4
    vet[5] = "EXTENDS"; //5
    vet[6] = "FALSE";//6
    vet[7] = "IF";//7
    vet[8] = "INT";//8
    vet[9] = "LENGTH";//9
    vet[10] = "MAIN";//10
    vet[11] = "NEW";//11
    vet[12] = "PUBLIC";//12
    vet[13] = "RETURN";//13
    vet[14] = "STATIC";//14
    vet[15] = "STRING";//15
    vet[16] = "SOUT";//16
    vet[17] = "THIS";//16
    vet[18] = "TRUE";//16
    vet[19] = "VOID";//16
    vet[20] = "WHILE";//16
    vet[21] = "OP";//16
    vet[22] = "AND";//16
    vet[23] = "LT";//16
    vet[24] = "GT";//16
    vet[25] = "PLUS";//16
    vet[26] = "MINUS";//16
    vet[27] = "MULT";//16
    vet[28] = "DIV";//16
    vet[29] = "ATRIB";//16
    vet[30] = "EQ";//16
    vet[31] = "NEQ";//16
    vet[32] = "NOT";//16
    vet[33] = "SEP";//16
    vet[34] = "L_PAREN";//16
    vet[35] = "R_PAREN";//16
    vet[36] = "L_BRACKET";//16
    vet[37] = "R_BRACKET";//16
    vet[38] = "L_KEY";//16
    vet[39] = "R_KEY";//16
    vet[40] = "SEMI";//16
    vet[41] = "DOT";//16
    vet[42] = "COMMA";//16
    vet[43] = "NUMBER";//16
    vet[44] = "INTEGER_LITERAL";//16
    vet[45] = "CMT"; // 45
    vet[46] = "START_OF_CMT"; // 46
    vet[47] = "END_OF_CMT"; // 47
    vet[48] = "END_OF_LINE";//16
    vet[49] = "END_OF_FILE";//16
}

void freeVetor() {
    delete[] vet;
}

void print(Token* t) {
    cout << vet[t->name];

    if (t->attribute != UNDEF)
        cout << "(" << vet[t->attribute] << ")";

    cout << " ";
}