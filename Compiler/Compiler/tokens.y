/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
extern "C" int yylex();
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
}

/* Определение лево-ассоцитивности. Аналогично есть %right.
Порядок объявление важен - чем позже объявлен оператор, тем больше его приоритет.
В данном случае оба оператора лево-ассоциативные, но - имеет более высокий приоритет, чем & и |. */
%left '+''-'
%left '*''/'
%left UMINUS
%left '['']'
%left '('')'
%left '.'
%left '!''&''<'
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
%type<varDecl> FormalRest;

/* Секция с описанием правил парсера. */
%%
Program:
	MainClass { $$ = new CProgram($1, nullptr); }
	| MainClass ClassDecls { $$ = new CProgram($1, $2); }
ClassDecls: ClassDecl { $$ = new CClassDeclList($1); }
	| ClassDecls ClassDecl { 
		std::vector< IClassDecl* > decls = dynamic_cast< CClassDeclList* >($1)->ClassDeclList();
		decls.push_back($2);
		$$ = new CClassDeclList(decls); 
	}
MainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '['']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( std::string($2), $15 ); }
ClassDecl: CLASS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( std::string($2), "", $4, $5 ); }
	| CLASS ID '{' MethodDecls '}' { $$ = new CClassDecl(std::string($2), "", nullptr, $4 ); }
	| CLASS ID '{' VarDecls '}' { $$ = new CClassDecl(std::string($2), "", $4, nullptr ); }
	| CLASS ID '{' '}' { $$ = new CClassDecl(std::string($2), "", nullptr, nullptr ); }
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), $6, $7 ); }
	| CLASS ID EXTENDS ID '{' MethodDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), nullptr, $6 ); }
	| CLASS ID EXTENDS ID '{' VarDecls '}' { $$ = new CClassDecl(std::string($2), std::string($4), $6, nullptr ); }
	| CLASS ID EXTENDS ID '{' '}' { $$ = new CClassDecl(std::string($2), std::string($4), nullptr, nullptr ); }
VarDecls: VarDecl { $$ = new CVarDeclList( $1 ); }
	| VarDecls VarDecl { 
		std::vector< IVarDecl* > decls = dynamic_cast<CVarDeclList*>($1)->VarDeclList();
		decls.push_back($2);
		$$ = new CVarDeclList(decls); 
	}
MethodDecls: MethodDecl { $$ = new CMethodDeclList( $1 ); }
	| MethodDecls MethodDecl { 
		std::vector< IMethodDecl* > decls = dynamic_cast<CMethodDeclList*>($1)->MethodDeclList();
		decls.push_back($2);
		$$ = new CMethodDeclList(decls); 
	}
VarDecl: Type ID ';' { $$ = new CVarDecl( $1, std::string($2) ); }
MethodDecl: PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			$8,
			$9,
			$11
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			nullptr,
			$8,
			$10
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			$8,
			nullptr,
			$10
			);
	}
	| PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}' {
		$$ = new CMethodDecl( 
			$2, 
			std::string($3),
			$5,
			nullptr,
			nullptr,
			$9
			);
	}
Statements: Statement { $$ = new CStatementList($1); }
	| Statements Statement  { 
		std::vector< IStatement* > decls = dynamic_cast< CStatementList* >($1)->StatementList();
		decls.push_back($2);
		$$ = new CStatementList(decls); 
	}
FormalList: /*epsilon*/ { $$ = nullptr; }
	| Type ID FormalRests { 
		CVarDecl* var = new CVarDecl( $1, std::string($2) );
		std::vector< IVarDecl* > decls = dynamic_cast< СFormalList* >($3)->List();
		decls.insert(decls.begin(), var);
		$$ = new СFormalList( decls );
	}
	| Type ID { $$ = new СFormalList( new CVarDecl( $1, std::string($2) ) ); }
FormalRests: FormalRest { $$ = new СFormalList($1); }
	| FormalRests FormalRest {
		std::vector< IVarDecl* > decls = dynamic_cast< СFormalList* >($1)->List();
		decls.push_back( $2 );
		$$ = new СFormalList( decls );
	}
FormalRest: ',' Type ID { $$ = new CVarDecl( $2, std::string($3) ); }
Type: INT '[' ']' { $$ = new CType( "int[]"); }
	| BOOLEAN { $$ = new CType( "boolean"); }
	| INT { $$ = new CType( "int"); }
	| ID { $$ = new CType( "id"); }
Statement: '{' Statements '}' { std::cout << "{Statements}" << std::endl;}
	| '{' '}' { $$ = nullptr; }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CIfStatement( $3, $5, $7 ); }
	| WHILE '(' Exp ')' Statement { $$ = new CWhileStatement( $3, $5 ); }
	| PRINT '(' Exp ')' ';' { $$ = new CPrintStatement( $3 ); }
	| ID '=' Exp ';' { $$ = new CAssignmentStatement( std::string( $1 ), $3 ); }
	| ID '[' Exp ']' '=' Exp ';' { $$ = new CElementAssignment( std::string($1), $3, $6 ); }
Exp: '-' Exp %prec UMINUS { $$ = new CUnExp( $2, "-" ); }
	| Exp '+' Exp { $$ = new CBinExp( $1, $3, "+" ); }
	| Exp '<' Exp { $$ = new CBinExp( $1, $3, "<" ); }
	| Exp '&' Exp { $$ = new CBinExp( $1, $3, "&" ); }
	| Exp '-' Exp { $$ = new CBinExp( $1, $3, "-" ); }
	| Exp '*' Exp { $$ = new CBinExp( $1, $3, "*" ); }
	| Exp '/' Exp { $$ = new CBinExp( $1, $3, "/" ); }
	| Exp '[' Exp ']' { $$ = new CBinExp( $1, $3, "[]" ); }
	| Exp '.' LENGTH { $$ = new CLengthExp( $1 ); }
	| Exp '.' ID '(' ExpList ')' { std::cout << "Method call" << std::endl; }
	| INTEGER_LITERAL { std::cout << "INTEGER_LITERAL" << std::endl; }
	| TRUE
	| FALSE
	| ID
	| THIS
	| NEW INT '[' Exp ']'
	| NEW ID '(' ')'
	| '!' Exp { $$ = new CUnExp( $2, "!" ); }
	| '(' Exp ')' { $$ = $2; }
ExpList: /*epsilon*/
	| Exp  { $$ = new CExpList( $1 ); }
	| Exp ExpRests { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>($2)->Expressions();
		exps.insert(exps.begin(), $1);
		$$ = new CExpList(exps); 
	}
ExpRests: ExpRest { $$ = new CExpList( $1 ); }
	| ExpRests ExpRest  { 
		std::vector< IExp* > exps = dynamic_cast<CExpList*>($1)->Expressions();
		exps.push_back($2);
		$$ = new CExpList(exps); 
	}
ExpRest: ',' Exp { $$ = $2; }
%%

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}