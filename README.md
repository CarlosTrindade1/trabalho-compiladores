# Trabalho de Compiladores 

Estudantes: Carlos Trindade, Geffté Caetano, Matheus Mota

## Como executar o programa 💻

### Configurando programa ⚙️
Para executar o programa, primeiro deve-se criar todos os arquivos, então no terminal digite:
```bash  
    make all
```
Assim todos os arquivos necessários devem ser criados.

### Configurando testes 🎲
Para testar, deve-se adicionar o arquivo .mj na raiz e adicionar seus nomes no Makefile.
Exite um arquivo Makefile com a função "run", nele há os testes com extensão .mj. 
Se o nome do arquivo for "testex.mj", deve-se adicionar na run uma nova linha contendo
```bash  
    ./minijava_compiler testex.mj
```
### Rodando o programa 🚀
Por fim, com os testes configurados, para rodar o programa com os testes, digite no terminal:
```bash  
    make run
```
