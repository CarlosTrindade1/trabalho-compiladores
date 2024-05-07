#include "scanner.h"

int main(int argc, char* argv[]) {
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2) {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    char* file_name = argv[1];

    Scanner* scanner = new Scanner(file_name);
    
    Token* token;
    
    do {
        token = scanner->nextToken();
        
        cout << token->name << " ";

    } while (token->name != END_OF_LINE);

    cout << endl;

    delete scanner;
    
    return 0;
}