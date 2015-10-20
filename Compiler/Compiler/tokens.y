/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
#include "classes.h"
extern "C" int yylex();
void yyerror( int*, const char* str );
%}

/* Этот код будет помещен до определения Union
Обычно используется для описания классов, реализующих синтаксическое дерево. */

%code requires {#include "common.h"}
/* Параметры функции парсера. */
%parse-param { int* hasError }

/* Определение возможных типов выражения. */
%union{
	int ival;
	char sval[255];
	CProgram* program;
	CMainClass* mainClass;
	CClassDecl* classDecl;
	CClassDeclList* classDecls;
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
%type<classDeclList> ClassDecls

/* Секция с описанием правил парсера. */
%%
Program: 
	MainClass { $$ = new CProgramm($1, nullptr);}
	| MainClass ClassDecls { $$ = new CProgramm($1, $2);}
ClassDecls: ClassDecl
	| ClassDecls ClassDecl { $$ = }
MainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '['']' ID ')' '{' Statement '}' '}'
ClassDecl: CLASS ID '{' VarDecls MethodDecls '}'
	| CLASS ID '{' MethodDecls '}'
	| CLASS ID '{' VarDecls '}'
	| CLASS ID '{' '}'
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}'
	| CLASS ID EXTENDS ID '{' MethodDecls '}'
	| CLASS ID EXTENDS ID '{' VarDecls '}'
	| CLASS ID EXTENDS ID '{' '}'
VarDecls: VarDecl
	| VarDecls VarDecl
MethodDecls: MethodDecl
	| MethodDecls MethodDecl
VarDecl: Type ID ';'
MethodDecl: PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}'
Statements: Statement
	| Statements Statement
FormalList: /*epsilon*/
	| Type ID FormalRests
	| Type ID
FormalRests: FormalRest
	| FormalRests FormalRest
FormalRest: ',' Type ID
Type: INT '[' ']'
	| BOOLEAN
	| INT
	| ID
Statement: '{' Statements '}'
	| '{' '}'
	| IF '(' Exp ')' Statement ELSE Statement
	| WHILE '(' Exp ')' Statement
	| PRINT '(' Exp ')' ';'
	| ID '=' Exp ';'
	| ID '[' Exp ']' '=' Exp ';'
Exp: '-' Exp %prec UMINUS
	| Exp '+' Exp
	| Exp '<' Exp
	| Exp '&' Exp
	| Exp '-' Exp
	| Exp '*' Exp
	| Exp '/' Exp
	| Exp '[' Exp ']'
	| Exp '.' LENGTH
	| Exp '.' ID '(' ExpList ')'
	| INTEGER_LITERAL
	| TRUE
	| FALSE
	| ID
	| THIS
	| NEW INT '[' Exp ']'
	| NEW ID '(' ')'
	| '!' Exp
	| '(' Exp ')'
ExpList: /*epsilon*/
	| Exp 
	| Exp ExpRests
ExpRests: ExpRest
	| ExpRests ExpRest
ExpRest: ',' Exp
%%

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}