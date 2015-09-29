/* ������ ������ ������ ����� ���� �� �������� �������, ����� ��� ����, ����� ���� ����������� ����� � ��������� ��, ��� ����� ������� */

/* ������ � �����, ������� ������� � ������.*/
%{
#include <iostream>
extern "C" int yylex();
void yyerror( int*, const char* str );
%}

/* ���� ��� ����� ������� �� ����������� Union
������ ������������ ��� �������� �������, ����������� �������������� ������. */

%code requires {#include "common.h"}
/* ��������� ������� �������. */
%parse-param { int* hasError }

/* ����������� ��������� ����� ���������. */
%union{
	int ival;
	char sval[255];
}

/* ����������� ����-��������������. ���������� ���� %right.
������� ���������� ����� - ��� ����� �������� ��������, ��� ������ ��� ���������.
� ������ ������ ��� ��������� ����-�������������, �� - ����� ����� ������� ���������, ��� & � |. */
/*%left '&',\'|'
%left '-'*/

/* ����������� �������. ����� ������ ������������� � ������� ��� �� Union. */

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

/* ��������� ��� �� union � ������ �������. */
%type<program> Program


/* ������ � ��������� ������ �������. */
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

/* ������� ��������� ������. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}