#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int);
		
	public:
		Parser(string);
		bool nextIs(int);
		void run();
		void program(); 
		void declarations(); 
		void mainClass(); 
		void classDeclaration(); 
		void maybeExtend(); 
		void varDeclarations(); 
		void methodDeclarations(); 
		void varDeclaration(); 
		void methodDeclaration(); 
		void maybeParams(); 
		void statements(); 
		void params(); 
		void moreParams(); 
		void type(); 
		void maybeArray(); 
		void statement(); 
		void statementCont(); 
		void expression(); 
		void expression2(); 
		void relExpression(); 
		void relExpression2(); 
		void addExpression(); 
		void addExpression2(); 
		void multExpression(); 
		void multExpression2(); 
		void unExpression(); 
		void primExpression(); 
		void primExpression2(); 
		void primExpressionCont(); 
		void maybeExpressionList(); 
		void expressionList(); 
		void moreExpressions(); 



        void error(string);
};


