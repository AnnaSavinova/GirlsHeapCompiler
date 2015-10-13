#include <iostream>
#include "common.h"

extern "C" int yylex();

int main()
{
    yyparse(0);
    system( "pause" );
	return 0;
}