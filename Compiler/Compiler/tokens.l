%option noyywrap

%{
	#pragma once
	#include "tokens.tab.hpp"
	#define YY_DECL extern "C" int yylex()
%}

%option yylineno

LETTER ([a-zA-Z])
DIGIT ([0-9])
ID ({LETTER})({LETTER}|{DIGIT}|_)*
INTEGER ({DIGIT}+)
COMMENT ((\/\*(([^*\n]*)|([^/\n]*)|(([^*\n]*\*+[^*/\n]+[^*\n]*)*)|([^*\n]*\*+))\*\/)|(\/\/.*))
BRACKETS [\[\](){}]
OPERANDS [-+*!.,;:=<]

%%
"&&" {
	//std::cout << "&&" << std::endl;
	return '&';
}

"||" {
	return '|';
}

{BRACKETS} {
	//std::cout << yytext << std::endl;
	return *yytext;
}


{INTEGER} {
	yylval.ival = atoi( yytext );
	//std::cout << yytext << std::endl;
	return INTEGER_LITERAL;
}

"class"	{
	//std::cout << "class" << std::endl; 
	return CLASS;
}

"public" {
	//std::cout << "public" << std::endl;
	return PUBLIC;
}

"static" {
	//std::cout << "static" << std::endl;
	return STATIC;
}

"void" {
	//std::cout << "void" << std::endl;
	return VOID;
}

"main" {
	//std::cout << "main" << std::endl;
	return MAIN;
}

"extends" {
	//std::cout << "extends" << std::endl;
	return EXTENDS;
}

"return" {
	//std::cout << "return" << std::endl;
	return RETURN;
}

"int" {
	//std::cout << "int" << std::endl;
	return INT;
}

"boolean" {
	//std::cout << "boolean" << std::endl;
	return BOOLEAN;
}

"if" {
	//std::cout << "if" << std::endl;
	return IF;
}

"else" {
	//std::cout << "else" << std::endl;
	return ELSE;
}

"while" {
	//std::cout << "while" << std::endl;
	return WHILE;
}

"String" {
	//std::cout << "String" << std::endl;
	return STRING;
}

"System.out.println" {
	//std::cout << "System.out.println" << std::endl;
	return PRINT;
}

"length" {
	//std::cout << "length" << std::endl;
	return LENGTH;
}

"true" {
	//std::cout << "true" << std::endl;
	return TRUE;
}

"false" {
	//std::cout << "false" << std::endl;
	return FALSE;
}

"this" {
	//std::cout << "this" << std::endl;
	return THIS;
}

"new" {
	//std::cout << "new" << std::endl;
	return NEW;
}

{COMMENT} {
	//std::cout << "COMMENT" << std::endl;
}

{OPERANDS} {
	//std::cout << "OPERAND " << *yytext << std::endl;
	return *yytext;
}

{ID} {
	strcpy_s(yylval.sval, yytext);
	//std::cout << "ID" << std::endl;
	return ID;
}

[ \t\n] {} /*ignore*/

. {
	std::cout << "PANIC!!" << std::endl;
};
%%
int YYtext();