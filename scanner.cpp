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
                // Início do identificador de ID
                } else if (isalpha(input[pos])) {
                    state = 1;
                // Início do whitespace ignorer
                } else if (isspace(input[pos])) {
                    state = 3;
                // Inícios da identificação de operadores
                } else if (input[pos] == '&') {
                    state = 5;
                } else {
                    lexicalError("Token mal formado");
                }

                pos++;
                break;
            // Estados 1 e 2: Implementação da identificação de IDs
            case 1:
                if (!isalnum(input[pos]))
                    state = 2;

                pos++;
                break;
            case 2:
                token = new Token(ID);

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
            // TODO
            case 5:
                if (input[pos] == '&')
                    state = 6;
                else
                    lexicalError("Token mal formado");

                pos++;
                break;

            case 6:
                token = new Token(OP, AND);
                return token;
                break;
            default:
                lexicalError("Token mal formado");
        }
    }
    return token;
}

void Scanner::lexicalError(string msg) {
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
