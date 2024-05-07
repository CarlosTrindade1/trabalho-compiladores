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
            // Estado de identificação do fim de arquivo
            case 0:
                if (input[pos] == '\n') {
                    token = new Token(END_OF_LINE);
                    return token;
                } else if (isalpha(input[pos])) {
                    state = 1;
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
