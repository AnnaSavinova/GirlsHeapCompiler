/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
#include "PrettyPrinter.h"
#include "SymbTableBuilder.h"
#include "TypeChecker.h"
#include "IRTranslator.h"
#include "IRTreePrettyPrinter.h"

extern "C" int yylex();
extern int yylineno;

int CLabel::nextUniqueId = 0;
int CTemp::nextUniqueId = 0;
int CFrame::wordSize = 4;
void yyerror( int*, const char* str );
%}

/* Этот код будет помещен до определения Union
Обычно используется для описания классов, реализующих синтаксическое дерево. */

%code requires {
	#include "classes.h"
}
/* Параметры функции парсера. */
%parse-param { int* hasError }

/* Определение возможных типов выражения. */
%union{
	int ival;
	char sval[255];
	IProgram* program;
	IMainClass* mainClass;
	IClassDecl* classDecl;
	IClassDeclList* classDecls;
	IExpList* expList;
	IFormalList* formalList;
	IStatement* statement;
	IMethodDecl* methodDecl;
	IMethodDeclList* methodDecls;
	IStatementList* statements;
	IExp* exp;
	IVarDecl* varDecl;
	IVarDeclList* varDecls;
	IType* type;
	CFormalListElement* formalListElement;
}

/* Определение лево-ассоцитивности. Аналогично есть %right.
Порядок объявление важен - чем позже объявлен оператор, тем больше его приоритет.
В данном случае оба оператора лево-ассоциативные, но - имеет более высокий приоритет, чем & и |. */
%left '+''-'
%left '*'
%left UMINUS
%left '['']'
%left '('')'
%left '.'
%left '!''&''<''|'
/* Определение токенов. Можно задать ассоциируемый с токеном тип из Union. */

%token CLASS
%token PUBLIC
%token STATIC
%token VOID
%token MAIN
%token STRING
%token EXTENDS
%token RETURN
%token INT
%token BOOLEAN
%token IF
%token ELSE
%token WHILE
%token PRINT
%token LENGTH
%token TRUE
%token FALSE
%token THIS
%token NEW

%token <ival> INTEGER_LITERAL
%token <sval> ID

/* Связываем тип из union и символ парсера. */
%type<program> Program
%type<mainClass> MainClass
%type<classDecl> ClassDecl
%type<classDecls> ClassDecls
%type<expList> ExpList;
%type<formalList> FormalList;
%type<methodDecl> MethodDecl;
%type<methodDecls> MethodDecls;
%type<statements> Statements;
%type<statement> Statement;
%type<varDecl> VarDecl;
%type<varDecls> VarDecls;
%type<exp> Exp;
%type<expList> ExpRests;
%type<exp> ExpRest;
%type<type> Type;
%type<formalList> FormalRests;
%type<formalListElement> FormalRest;

/* Секция с описанием правил парсера. */
%%
Program: MainClass { $$ = new CProgram($1, nullptr, yylineno); program = $$; }
	| MainClass ClassDecls { $$ = new CProgram($1, $2, yylineno); program = $$; }
ClassDecls: ClassDecl { $$ = new CClassDeclList($1, yylineno); }
	| ClassDecls ClassDecl { 
		std::vector< IClassDecl* > decls = dynamic_cast< CClassDeclList* >($1)->ClassDeclList();
		decls.push_back($2);
		$$ = new CClassDeclList(decls, yylineno); 
	}
MainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '['']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( std::string($2), $15, yylineno ); }
ClassDecl: CLASS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( std::string($2), "", $4, $5, yylineno ); }
	| CLASS ID '{' MethodDecls '}' { $$ = new CClassDecl(std::string($2), "", nullptr, $4, yylineno ); }
	| CLASS ID '{' VarDecls '}' { $$ = new CClassDecl(std::string($2), "", $4, nullptr, yylineno ); }
	| CLASS ID '{' '}' { $$ = new CClassDecl(std::string($2), "", nullptr, nullptr, yylineno ); }
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), $6, $7, yylineno ); }
	| CLASS ID EXTENDS ID '{' MethodDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), nullptr, $6, yylineno ); }
	| CLASS ID EXTENDS ID '{' VarDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), $6, nullptr, yylineno ); }
	| CLASS ID EXTENDS ID '{' '}' { $$ = new CClassDecl(std::string($2), std::string($4), nullptr, nullptr, yylineno ); }
VarDecls: VarDecl { $$ = new CVarDeclList( $1, yylineno ); }
	| VarDecls VarDecl { 
		std::vector< IVarDecl* > decls = dynamic_cast<CVarDeclList*>($1)->VarDeclList();
		decls.push_back($2);
		$$ = new CVarDeclList(decls, yylineno); 
	}
MethodDecls: MethodDecl { $$ = new CMethodDeclList( $1, yylineno ); }
	| MethodDecls MethodDecl { 
		std::vector< IMethodDecl* > decls = dynamic_cast<CMethodDeclList*>($1)->MethodDeclList();
		decls.push_back($2);
		$$ = new CMethodDeclList(decls, yylineno); 
	}
VarDecl: Type ID ';' { $$ = new CVarDecl( $1, std::string($2), yylineno ); }
MethodDecl: PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			$8,
			$9,
			$11, 
			yylineno
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			nullptr,
			$8,
			$10, 
			yylineno
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			$8,
			nullptr,
			$10, 
			yylineno
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			nullptr,
			nullptr,
			$9, 
			yylineno
			);
	}
Statements: Statement { $$ = new CStatementList($1, yylineno); }
	| Statements Statement  { 
		std::vector< IStatement* > decls = dynamic_cast< CStatementList* >($1)->StatementList();
		decls.push_back($2);
		$$ = new CStatementList(decls, yylineno); 
	}
FormalList: /*epsilon*/ { $$ = nullptr; }
	| Type ID FormalRests { 
		CFormalListElement* var = new CFormalListElement( $1, std::string($2), yylineno );
		std::vector< CFormalListElement* > decls = dynamic_cast< CFormalList* >($3)->List();
		decls.insert(decls.begin(), var);
		$$ = new CFormalList( decls, yylineno );
	}
	| Type ID { $$ = new CFormalList( new CFormalListElement( $1, std::string($2), yylineno ), yylineno ); }
FormalRests: FormalRest { $$ = new CFormalList($1, yylineno); }
	| FormalRests FormalRest {
		std::vector< CFormalListElement* > decls = dynamic_cast< CFormalList* >($1)->List();
		decls.push_back( $2 );
		$$ = new CFormalList( decls, yylineno );
	}
FormalRest: ',' Type ID { $$ = new CFormalListElement( $2, std::string($3), yylineno ); }
Type: INT '[' ']' { $$ = new CType( "int[]", yylineno ); }
	| BOOLEAN { $$ = new CType( "boolean", yylineno ); }
	| INT { $$ = new CType( "int", yylineno ); }
	| ID { $$ = new CType( $1, yylineno ); }
Statement: '{' Statements '}' { $$ = new CStatementBlock($2, yylineno); }
	| '{' '}' { $$ = nullptr; }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CIfStatement( $3, $5, $7, yylineno ); }
	| WHILE '(' Exp ')' Statement { $$ = new CWhileStatement( $3, $5, yylineno ); }
	| PRINT '(' Exp ')' ';' { $$ = new CPrintStatement( $3, yylineno ); }
	| ID '=' Exp ';' { $$ = new CAssignmentStatement( std::string( $1 ), $3, yylineno ); }
	| ID '[' Exp ']' '=' Exp ';' { $$ = new CElementAssignment( std::string($1), $3, $6, yylineno ); }
Exp: '-' Exp %prec UMINUS { $$ = new CUnExp( $2, "-", yylineno ); }
	| Exp '+' Exp { $$ = new CBinExp( $1, $3, "+", yylineno ); }
	| Exp '<' Exp { $$ = new CBinExp( $1, $3, "<", yylineno ); }
	| Exp '&' Exp { $$ = new CBinExp( $1, $3, "&", yylineno ); }
	| Exp '|' Exp { $$ = new CBinExp( $1, $3, "|", yylineno ); }
	| Exp '-' Exp { $$ = new CBinExp( $1, $3, "-", yylineno ); }
	| Exp '*' Exp { $$ = new CBinExp( $1, $3, "*", yylineno ); }
	| Exp '[' Exp ']' { $$ = new CBinExp( $1, $3, "[]", yylineno ); }
	| Exp '.' LENGTH { $$ = new CLengthExp( $1, yylineno ); }
	| Exp '.' ID '(' ExpList ')' { $$ = new CMethodCall( $1, $3, $5, yylineno ); }
	| INTEGER_LITERAL { $$ = new CNumber($1, yylineno); }
	| TRUE { $$ = new CNumber(1, yylineno); }
	| FALSE { $$ = new CNumber(0, yylineno); }
	| ID { $$ = new CId($1, yylineno); }
	| THIS { $$ = new CId("this", yylineno); }
	| NEW INT '[' Exp ']' { $$ = new CNewInt( $4, yylineno ); }
	| NEW ID '(' ')' { $$ = new CConstructor( $2, yylineno ); }
	| '!' Exp { $$ = new CUnExp( $2, "!", yylineno ); }
	| '(' Exp ')' { $$ = $2; }
ExpList: /*epsilon*/ { $$ = nullptr; }
	| Exp  { $$ = new CExpList( $1, yylineno ); }
	| Exp ExpRests { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>($2)->Expressions();
		exps.insert(exps.begin(), $1);
		$$ = new CExpList(exps, yylineno); 
	}
ExpRests: ExpRest { $$ = new CExpList( $1, yylineno ); }
	| ExpRests ExpRest  { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>($1)->Expressions();
		exps.push_back($2);
		$$ = new CExpList(exps, yylineno); 
	}
ExpRest: ',' Exp { $$ = $2; }
%%

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}

int main()
{
    yyparse(0);
//    CPrettyPrinter printer;
//    printer.Visit( (CProgram*) program );

	CSymbTableBuilder tableBuilder;
	tableBuilder.Visit( (CProgram*) program );

	CTypeChecker checker( tableBuilder.GetSymbolTable() );
	checker.Visit( (CProgram*) program );

	CIRTranslator IRTranslator( tableBuilder.GetSymbolTable(), checker.GetExpTypesTable() );
	IRTranslator.Visit( (CProgram*) program );

	// Вывод IR-деревьев в "просматриваемый вид".
	std::stack< CFrame* > frames = IRTranslator.GetFramesList();
	while( !frames.empty() ) {
		CFrame* frame = frames.top();
		frames.pop();
		CIRTreePrettyVisitor IRTreePrettyPrinter( std::string( "IRTree_" ) + frame->GetName() + std::string( ".dot" ) );
		frame->GetRoot()->Accept( &IRTreePrettyPrinter );
		IRTreePrettyPrinter.Flush();
	}

	system("pause");
	return 0;
}