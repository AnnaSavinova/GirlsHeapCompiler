#pragma once
#include <string>
#include <map>

class CSymbol
{
public:
	CSymbol( const std::string& _s ) : s( _s ) {};
	const std::string& String() const
	{
		return s;
	}

private:
	std::string s;
};

class CStorage
{
public:
	CSymbol* Get( const std::string & s )
	{
		auto found = symbols.find( s );
		if( found == symbols.end() ) {
			CSymbol* res = new CSymbol( s );
			symbols[s] = res;
			return res;
		} else {
			return found->second;
		}
	}
private:
	std::map<std::string, CSymbol*> symbols;
};

extern CStorage symbolStorage;