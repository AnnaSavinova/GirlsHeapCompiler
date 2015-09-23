%option noyywrap

%{
	#pragma once
	#include <iostream>
	#define YY_DECL extern "C" int yylex()
%}

%option yylineno

LETTER ([a-zA-Z])
DIGIT ([0-9])
ID ({LETTER})({LETTER}|{DIGIT}|_)*
INTEGER (-?{DIGIT}+)
BINOP ([-+*/])
COMMENT_CLOSE (\*\/)
COMMENT ((\/\*(([^*\n]*)|([^/\n]*)|(([^*\n]*\*+[^*/\n]+[^*\n]*)*)|([^*\n]*\*+))\*\/)|(\/\/.*))

%%

{INTEGER}	{
		std::cout << "INTEGER" << std::endl;		
	}

"class"		{
		std::cout << "class" << std::endl; 
	}

"public"	{
		std::cout << "public" << std::endl;
	}

"static"	{
		std::cout << "static" << std::endl;
	}

"void"		{
		std::cout << "void" << std::endl;
	}

"main"		{
		std::cout << "main" << std::endl;
	}

"extends"	{
		std::cout << "extends" << std::endl;	
}

"return"	{
		std::cout << "return" << std::endl;
	}

"int"		{
		std::cout << "int" << std::endl;
	}

"boolean"	{
		std::cout << "boolean" << std::endl;
	}

"if"		{
		std::cout << "if" << std::endl;
	}

"else"		{
		std::cout << "else" << std::endl;
	}

"while"		{
		std::cout << "while" << std::endl;
	}

"System.out.println" {
		std::cout << "System.out.println" << std::endl;
	}

"length"	{
		std::cout << "length" << std::endl;
	}

"true"		{
		std::cout << "true" << std::endl;
	}

"false"		{
		std::cout << "false" << std::endl;
	}

"this"		{
		std::cout << "this" << std::endl;
	}

"new int"	{
		std::cout << "new int" << std::endl;
	}

"new"		{
		std::cout << "new" << std::endl;
	}

{COMMENT}	{
		std::cout << "COMMENT" << std::endl;
}

{BINOP}		{
		std::cout << "BINOP" << std::endl;
}

{ID}		{
		std::cout << "ID" << std::endl;
	}

.	{
		std::cout << "PANIC!!" << std::endl;
	};
%%
int YYtext();