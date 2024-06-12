#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

bool
Parser::nextIs(int t)
{
	return lToken->name == t || lToken->attribute == t;
}

void
Parser::match(int t)
{
	if (nextIs(t))
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	
	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program()
{
    mainClass();
	declarations();
	match(END_OF_FILE);
}

void
Parser::declarations()
{
	classDeclaration();
	// declarations();
}
 
void
Parser::mainClass()
{
	match(CLASS);
	match(ID);
	match(L_KEY);
	match(PUBLIC);
	match(STATIC);
	match(VOID);
	match(MAIN);
	match(L_PAREN);
	match(STRING);
	match(L_BRACKET);
	match(R_BRACKET);
	match(ID);	
	match(R_PAREN);
	match(L_KEY);
	statement();
	match(R_KEY);
	match(R_KEY);

}
 
void
Parser::classDeclaration()
{
	match(CLASS);
	match(ID);
	maybeExtend();
	match(L_KEY);
	varDeclarations();
	methodDeclarations();
	match(R_KEY);
}
 
void
Parser::maybeExtend()
{
	if (nextIs(EXTENDS)){
		match(EXTENDS);
		match(ID);
	} else return;
}
 
void
Parser::varDeclarations()
{
	if (nextIs(INT) ||nextIs(BOOLEAN) ||nextIs(ID)){
		varDeclaration();
		varDeclarations();
	} else return;
}
 
void
Parser::methodDeclarations()
{
	if (nextIs(PUBLIC)){
		methodDeclaration();
		methodDeclarations();
	} else return;
}
 
void
Parser::varDeclaration()
{
	type();
	match(ID);
	match(SEMI);
}
 
void
Parser::methodDeclaration()
{
	match(PUBLIC);
	type();
	match(ID);
	match(L_PAREN);
	maybeParams();
	match(R_PAREN);
	match(L_KEY);
	varDeclarations();
	statements();
	match(R_KEY);
}
 
void
Parser::maybeParams()
{
	if (nextIs(R_PAREN)){
		return;
	} else {
		params();
	}
}
 
void
Parser::statements()
{
	if (nextIs(L_KEY) || nextIs(IF) || nextIs(WHILE) || nextIs(SOUT) || nextIs(ID)){
		statement();
		statements();
	} else return;
}
 
void
Parser::params()
{
	type();
	match(ID);
	moreParams();

}
 
void
Parser::moreParams()
{

	if(nextIs(COMMA)){
		match(COMMA);
		type();
		match(ID);
		moreParams();
		
	} else {
		return;
	}

}
 
void
Parser::type()
{
	if (nextIs(INT)){
		match(INT);
		maybeArray();
	} else if (nextIs(BOOLEAN)){
		match(BOOLEAN);
	} else match(ID);
}
 
void
Parser::maybeArray()
{
	if (nextIs(L_BRACKET)){
		match(L_BRACKET);
		match(R_BRACKET);
	} else return;
}
 
void
Parser::statement()
{
	if (nextIs(L_KEY)){
		match(L_KEY);
		statements();
		match(R_KEY);
	} else if (nextIs(IF)){
		match(IF);
		match(L_PAREN);
		expression();
		match(R_PAREN);
		statement();
		match(ELSE);
		statement();
	} else if (nextIs(WHILE)){
		match(WHILE);
		match(L_PAREN);
		expression();
		match(R_PAREN);
		statement();
	} else if (nextIs(SOUT)){
		match(SOUT);
		match(L_PAREN);
		expression();
		match(R_PAREN);
		match(SEMI);
	} else {
		match(ID);
		statementCont() ;

	} 
}
 
void
Parser::statementCont()
{
	if(nextIs(ATRIB)){
		match(ATRIB);
		expression();
		match(SEMI);
	} else {
		match(L_BRACKET);
		expression();
		match(R_BRACKET);
		match(ATRIB);
		expression();
		match(SEMI);
	}
}
 
void
Parser::expression()
{
	relExpression();
	expression2();
}
 
void
Parser::expression2()
{
	if (nextIs(AND)){
		match(AND);
		relExpression();
		expression2();
	} else return;
}
 
void
Parser::relExpression()
{
	addExpression();
	relExpression2();
}
 
void
Parser::relExpression2()
{
	if (nextIs(LT)){
		match(LT);
		addExpression();
		relExpression2();

	} else if (nextIs(GT)){
		match(GT);
		addExpression();
		relExpression2();

	} else if (nextIs(EQ)){
		match(EQ);
		addExpression();
		relExpression2();

	} else if (nextIs(NEQ)){
		match(NEQ);
		addExpression();
		relExpression2();

	} else return;
}
 
void
Parser::addExpression()
{
	multExpression() ;
	addExpression2();
}
 
void
Parser::addExpression2()
{
	if (nextIs(PLUS)){
		match(PLUS);
		multExpression() ;
		addExpression2();
	} else if (nextIs(MINUS)){
		match(MINUS);
		multExpression() ;
		addExpression2();
	} else return;
}
 
void
Parser::multExpression()
{
	unExpression();
	multExpression2();
}

void
Parser::multExpression2()
{
	if (nextIs(MULT)){
		match(MULT);
		unExpression();
		multExpression2();

	} else if (nextIs(DIV)){
		match(DIV);
		unExpression();
		multExpression2();

	} else return;
}
 
void
Parser::unExpression()
{
	if (nextIs(NOT)){
		match(NOT);
		unExpression();
	} else if (nextIs(MINUS)){
		match(MINUS);
		unExpression();
	} else if (nextIs(INTEGER_LITERAL)){
		match(INTEGER_LITERAL);
	} else if (nextIs(TRUE)){
		match(TRUE);
	} else if (nextIs(FALSE)){
		match(FALSE);
	} else if (nextIs(NEW)){
		match(NEW);
		match(INT);
		match(L_BRACKET);
		expression();
		match(R_BRACKET);
	}  else {
		primExpression();
		primExpressionCont();
	}
}
 
void
Parser::primExpression()
{
	if(nextIs(ID)){
		match(ID);
		primExpression2();
	} else if (nextIs(L_PAREN)){
		match(L_PAREN);
		expression();
		match(R_PAREN);
		primExpression2();
	} else if (nextIs(THIS)){
		match(THIS);
		primExpression2();
	} else {
		match(NEW);
		match(ID);
		match(L_PAREN);
		match(R_PAREN);
		primExpression2();
	}
}
 
void
Parser::primExpressionCont()
{
	if (nextIs(DOT)){
		match(DOT);
		match(LENGTH);
	} else if (nextIs(L_BRACKET)){
		match(L_BRACKET);
		expression();
		match(R_BRACKET);
	} else return;
}
 
void
Parser::primExpression2()
{
	if (nextIs(DOT)){
		match(DOT);
		match(ID);
		if (nextIs(L_PAREN)){
			match(L_PAREN);
			maybeExpressionList();
			match(R_PAREN);
		}
	} else return;
}
 
void
Parser::maybeExpressionList()
{
	if(nextIs(R_PAREN)) {
		return;
	} else {
		expressionList();
	}
}
 
void
Parser::expressionList()
{
	expression();
	moreExpressions();
}
 
void
Parser::moreExpressions()
{
	if (nextIs(COMMA))
	{
		match(COMMA);
		expression();
		moreExpressions();
	} else return;
	
}
 


void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
