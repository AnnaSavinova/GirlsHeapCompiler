/* ������ ������ ������ ����� ���� �� �������� �������, ����� ��� ����, ����� ���� ����������� ����� � ��������� ��, ��� ����� ������� */

/* ������ � �����, ������� ������� � ������.*/
%{
#include <iostream>
#include "classes.h"
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
	CProgram* program;
	CMainClass* mainClass;
	CClassDecl* classDecl;
	CClassDeclList* classDecls;
}

/* ����������� ����-��������������. ���������� ���� %right.
������� ���������� ����� - ��� ����� �������� ��������, ��� ������ ��� ���������.
� ������ ������ ��� ��������� ����-�������������, �� - ����� ����� ������� ���������, ��� & � |. */
%left '+''-'
%left '*''/'
%left UMINUS
%left '['']'
%left '('')'
%left '.'
%left '!''&''<'
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

%token <ival> INTEGER_LITERAL
%token <sval> ID

/* ��������� ��� �� union � ������ �������. */
%type<program> Program
%type<mainClass> MainClass
%type<classDecl> ClassDecl
%type<classDeclList> ClassDecls

/* ������ � ��������� ������ �������. */
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

/* ������� ��������� ������. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}