/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
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
}

/* Определение лево-ассоцитивности. Аналогично есть %right.
Порядок объявление важен - чем позже объявлен оператор, тем больше его приоритет.
В данном случае оба оператора лево-ассоциативные, но - имеет более высокий приоритет, чем & и |. */
/*%left '&',\'|'
%left '-'*/

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
%token BINOP

%token <ival> INTEGER_LITERAL
%token <sval> ID

/* Связываем тип из union и символ парсера. */
%type<program> Program


/* Секция с описанием правил парсера. */
%%
Program: 
	MainClass ClassDecls
ClassDecls: /* epsilon */
	| ClassDecl ClassDecls
MainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '['']' ID ')' '{' Statement '}' '}'
ClassDecl: CLASS ID '{' VarDecls MethodDecls '}'
VarDecls: /*epsilon*/
	| VarDecl VarDecls
MethodDecls: /*epsilon*/
	| MethodDecl MethodDecls
VarDecl: Type ID ';'
MethodDecl: PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}'
Statements: /*epsilon*/
	| Statement Statements
FormalList: /*epsilon*/
	| Type ID FormalRests
FormalRests: /*epsilon*/
	| FormalRest FormalRests
FormalRest: ',' Type ID
Type: INT '[' ']'
	| BOOLEAN
	| INT
	| ID
Statement: '{' Statements '}'
	| IF '(' Exp ')' Statement ELSE Statement
	| WHILE '(' Exp ')' Statement
	| PRINT '(' Exp ')' ';'
	| ID '=' Exp ';'
	| ID '[' Exp ']' '=' Exp ';'
Exp: Exp BINOP Exp
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
	| Exp ExpRests
ExpRests: /*epsilon*/
	| ExpRest ExpRests
ExpRest: ',' Exp
%%

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}