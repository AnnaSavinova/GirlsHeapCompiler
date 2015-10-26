#include <iostream>
#include "common.h"
#include "tokens.tab.hpp"

extern "C" int yylex();

int main()
{
    yyparse(0);
    system( "pause" );
	return 0;
}