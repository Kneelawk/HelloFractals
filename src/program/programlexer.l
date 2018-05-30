%{
#include <string>
#include <iostream>

#include "programlexer.h"

#undef YY_DECL
#define YY_DECL int FractalProgram::ProgramLexer::yylex(FractalProgram::ProgramParser::semantic_type *const lval, FractalProgram::ProgramParser::location_type *loc)

using token = FractalProgram::ProgramParser::token;

#define yyterminate() return(token::END)

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option nodefault
%option noyywrap
%option yyclass="FractalProgram::ProgramLexer"
%option c++

%%
%{
				yylval = lval;
%}

[ \t]			;

\n				{
					loc->lines();
					return token::NEWLINE;
				}

var				{
					return token::VAR;
				}

[+-]?([0-9]+|[0-9]+\.[0-9]+|\.[0-9]+)i	{
					yylval->build<double>(std::stod(yytext));
					return token::IMAGINARY_NUMBER;
				}

[+-]?([0-9]+|[0-9]+\.[0-9]+|\.[0-9]+)	{
					yylval->build<double>(std::stod(yytext));
					return token::NUMBER;
				}

[a-zA-Z0-9]		{
					yylval->build<std::string>(yytext);
					return token::STRING;
				}

=				{
					return token::EQUALS;
				}

\(				{
					return token::OPEN_PARENTHESIS;
				}

\)				{
					return token::CLOSE_PARENTHESIS;
				}

\^				{
					return token::EXPONENT;
				}

\*				{
					return token::MULTIPLICATION;
				}

\/				{
					return token::DIVISION;
				}

\+				{
					return token::ADDITION;
				}

-				{
					return token::SUBTRACTION;
				}

.				{
					std::cerr << "Unrecognized token: '" << yytext << "'\n";
				}

%%
