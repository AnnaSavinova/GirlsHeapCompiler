/* Данный пример скорее всего даже не является рабочим, нужен для того, чтобы была возможность найти и загуглить то, что нужно гуглить */

/* Секция с кодом, который попадет в парсер.*/
%{
#include <iostream>
extern "C" int yylex();
void yyerror( int*, const char* str );
%}

/* Этот код будет помещен до определения Union
Обычно используется для описания классов, реализующих синтаксическое дерево. */

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
%left '&', '|'
%left '-'

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


/* Секция с описанием правил парсера. */
%%
Program: ;
%%

/* Функция обработки ошибки. */
void yyerror( int*, const char* str )
{
	std::cout << str << std::endl;
}