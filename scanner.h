#include <fstream>
#include "token.h"

class Scanner {
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line;
        int reserved_words_qtd = 19;
        string reserved_words[19] = {
            "boolean",
            "class",
            "else",
            "extends",
            "false",
            "if",
            "int",
            "length",
            "main",
            "new",
            "public",
            "return",
            "static",
            "String",
            "System.out.println",
            "this",
            "true",
            "void",
            "while"
        };
        
        bool isReservedWord(string lexeme);
        bool isValidId(string id);
        Names getEnumReservedWord(string lexeme);
    
    public:
    //Construtor
        Scanner(string);

        int getLine();
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void lexicalError(string);
};
