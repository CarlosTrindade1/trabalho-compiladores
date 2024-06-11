#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input) {
    this->pos = 0;
    this->line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            this->input.append(line + '\n');
        }
        this->input.append("\0");
        inputFile.close();
    } else  {
        cout << "Unable to open file\n";
    }
}

int Scanner::getLine() {
    return line;
}

//Método que retorna o próximo token da entrada
Token* Scanner::nextToken() {
    Token* token;
    string lexeme;
    int state = 0;

    while (true) {
        switch(state) {
            // Estado inicial
            case 0:
                // Idenfiticador do fim de linha
                if (input[pos] == '\0') {
                    token = new Token(END_OF_FILE);
                    return token;
                // Incrementador de linha
                } else if (input[pos] == '\n') {
                    this->line++;
                // Início do identificador de ID
                } else if (isalpha(input[pos])) {
                    state = 1;
                    lexeme += input[pos];
                // Início do whitespace ignorer
                } else if (isspace(input[pos])) {
                    state = 3;
                // Inícios da identificação de operadores
                } else if (input[pos] == '&') { // AND '&&'
                    state = 5;
                } else if (input[pos] == '<') { // LT '<'
                    state = 7;
                } else if (input[pos] == '>') { // GT '>'
                    state = 8;
                } else if (input[pos] == '+') { // PLUS '+'
                    state = 9;
                } else if (input[pos] == '-') { // MINUS '-'
                    state = 10;
                } else if (input[pos] == '*') { // MULT '*'
                    state = 11;
                } else if (input[pos] == '/') { // DIV '/' e CMT
                    state = 12;
                } else if (input[pos] == '=') { // ATRIB '=' e OP(EQ)
                    state = 19;
                } else if (input[pos] == '!') { // OP(NEQ) e OP(NOT)
                    state = 22;
                } else if (input[pos] == '(') { // SEP(L_PAREN)
                    state = 25;
                } else if (input[pos] == ')') { // SEP(R_PAREN)
                    state = 26;
                } else if (input[pos] == '[') { // SEP(L_BRACKET)
                    state = 27;
                } else if (input[pos] == ']') { // SEP(L_BRACKET)
                    state = 28;
                } else if (input[pos] == '{') { // SEP(L_KEY)
                    state = 29;
                } else if (input[pos] == '}') { // SEP(R_KEY)
                    state = 30;
                } else if (input[pos] == ';') { // SEP(SEMI)
                    state = 31;
                } else if (input[pos] == '.') { // SEP(DOT)
                    state = 32;
                } else if (input[pos] == ',') { // SEP(COMMA)
                    state = 33;
                } else if (isdigit(input[pos])) { // INTEGER_LITERAL
                    state = 34;
                } else {
                    lexicalError("Token mal formado");
                }

                pos++;
                break;
            // Estados 1 e 2: Implementação da identificação de IDs
            case 1:
                if (!isalnum(input[pos]) && input[pos] != '.') {
                    state = 2;
                } else if (input[pos] == '.') {
                    state = 36;
                    lexeme += input[pos];
                } else {
                    lexeme += input[pos];
                }

                pos++;
                break;
            case 2:
                if (isReservedWord(lexeme))
                    token = new Token(CLASS);
                else if (isValidId(lexeme))
                    token = new Token(ID);
                else
                    lexicalError("Token mal formado.");

                pos--;

                return token;
                break;
            // Estados 3 e 4: Implementação do whitespace ignorer
            case 3:
                if (!isspace(input[pos]))
                    state = 4;

                pos++;
            case 4:
                state = 0;
                pos--;
                break;
            // Estados 5-24: Implementação da identificação dos operadores e comentários
            case 5: // AND '&&'
                if (input[pos] == '&')
                    state = 6;
                else
                    lexicalError("Token mal formado");

                pos++;
                break;

            case 6: // AND '&&'
                token = new Token(OP, AND);
                return token;
                break;

            case 7: // LT '<'
                token = new Token(OP, LT);
                return token;
                break;
            case 8: // GT '>'
                token = new Token(OP, GT);
                return token;
                break;
            case 9: // PLUS '+'
                token = new Token(OP, PLUS);
                return token;
                break;
            case 10: // MINUS '-'
                token = new Token(OP, MINUS);
                return token;
                break;
            case 11: // MULT '*'
                token = new Token(OP, MULT);
                return token;
                break;
            case 12: // DIV '/' e CMTs
                if (input[pos] == '/')
                    state = 14;
                else if (input[pos] == '*')
                    state = 16;
                else
                    state = 13;

                pos++;

                break;
            case 13: // DIV '/'
                token = new Token(OP, DIV);

                pos--;
                
                return token;
                break;
            case 14: // CMT
                if (input[pos] == '\n')
                    state = 15;

                pos++;
                break;
            case 15: // CMT
                token = new Token(CMT);

                this->line++;

                return token;
                break;
            case 16: // CMT
                if (input[pos] == '*')
                    state = 17;
                else if (input[pos] == '\0')
                    lexicalError("Token mal formado");

                pos++;
                break;
            case 17: // CMT
                if (input[pos] == '/')
                    state = 18;
                else
                    state = 16;
                pos++;
                break;
            case 18: // CMT
                token = new Token(CMT);
                return token;
                break;
            case 19: // OP(ATRIB) e OP(EQ)
                if (input[pos] == '=')
                    state = 21;
                else
                    state = 20;

                pos++;
                break;
            case 20: // OP(ATRIB)
                token = new Token(OP, ATRIB);
                pos--;
                return token;
                break;
            case 21: // OP(EQ)
                token = new Token(OP, EQ);
                return token;
                break;
            case 22: // OP(NEQ) e OP(NOT)
                if (input[pos] == '=')
                    state = 24;
                else
                    state = 23;

                pos++;
                break;
            case 23: // OP(NOT)
                token = new Token(OP, NOT);
                pos--;
                return token;
                break;
            case 24: // OP(NEQ)
                token = new Token(OP, NEQ);
                return token;
                break;
            // Estados 25-33: Implementação dos separadores
            case 25: // SEP(L_PAREN)
                token = new Token(SEP, L_PAREN);
                return token;
                break;
            case 26: // SEP(L_PAREN)
                token = new Token(SEP, R_PAREN);
                return token;
                break;
            case 27: // SEP(L_BRACKET)
                token = new Token(SEP, L_BRACKET);
                return token;
                break;
            case 28: // SEP(L_BRACKET)
                token = new Token(SEP, R_BRACKET);
                return token;
                break;
            case 29: // SEP(L_KEY)
                token = new Token(SEP, L_KEY);
                return token;
                break;
            case 30: // SEP(R_KEY)
                token = new Token(SEP, R_KEY);
                return token;
                break;
            case 31: // SEP(SEMI)
                token = new Token(SEP, SEMI);
                return token;
                break;
            case 32: // SEP(DOT)
                token = new Token(SEP, DOT);
                return token;
                break;
            case 33: // SEP(COMMA)
                token = new Token(SEP, COMMA);
                return token;
                break;
            case 34: // INTEGER_LITERAL
                if (!isdigit(input[pos]))
                    state = 35;
                
                pos++;

                break;
            case 35:
                token = new Token(INTEGER_LITERAL);
                pos--;
                return token;
                break;
            case 36:
                if (isalpha(input[pos]))
                    state = 1;
                else
                    lexicalError("Token mal formado.");

                lexeme += input[pos];
                pos++;
                break;
            default:
                lexicalError("Token mal formado");
                break;
        }
    }
    return token;
}

void Scanner::lexicalError(string msg) {
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}

bool Scanner::isReservedWord(string lexeme) {
    for (int i = 0; i < reserved_words_qtd; i++) {
        if (reserved_words[i] == lexeme) {
            return true;
        }
    }
    return false;
}

bool Scanner::isValidId(string id){
    for (char ch : id) {
        if (ch == '.') {
            return false;
        }
    }
    return true;
}