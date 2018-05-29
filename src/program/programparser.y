%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define api.namespace { FractalProgram }
%define parser_class_name { ProgramParser }

%code requires {
namespace FractalProgram {
class ProgramLexer;
class ProgramHandler;
}

#ifndef YY_NULLPTR
# if defined __cplusplus && 201103L <= __cplusplus
#  define YY_NULLPTR nullptr
# else
#  define YY_NULLPTR 0
# endif
#endif
}

%parse-param { ProgramLexer &lexer }
%parse-param { ProgramHandler &handle }

%code {
#include <cstdio>
#include <iostream>

#include "programdriver.h"
#include "programlexer.h"

#undef yylex
#define yylex lexer.yylex
}

%define api.value.type variant
%define parse.assert

%token					END			0	"End of file"
%token					NEWLINE
%token					VAR
%token	<double>		IMAGINARY_NUMBER
%token	<double>		NUMBER
%token	<std::string>	STRING
%token					EQUALS
%token					OPEN_PARENTHESIS
%token					CLOSE_PARENTHESIS
%right					EXPONENT
%left					MULTIPLICATION
%left					DIVISION
%left					ADDITION
%left					SUBTRACTION

%start program

%locations

%%

program
			: END
			| lines END
			;

lines
			: line
			| lines newlines line
			;

line
			: %empty
			| statement
			;

newlines
			: NEWLINE
			| newlines NEWLINE
			;

statement
			: declaration
			| assignment
			| expression
			;

declaration
			: VAR STRING EQUALS statement { handle.onDeclaration($2); }
			;

assignment
			: STRING EQUALS statement { handle.onAssignment($1); }
			;

expression
			: number
			| variable
			| parenthesis
			| exponent
			| product
			| sum
			;

number
			: IMAGINARY_NUMBER { handle.onImaginaryNumber($1); }
			| NUMBER { handle.onNumber($1); }
			;

variable
			: STRING { handle.onVariable($1); }
			;

parenthesis
			: open_parenthesis statement CLOSE_PARENTHESIS { handle.onCloseParenthesis(); }
			;

open_parenthesis
			: OPEN_PARENTHESIS { handle.onOpenParenthesis(); }
			;

exponent
			: statement EXPONENT statement { handle.onExponent(); }
			;

product
			: statement MULTIPLICATION statement { handle.onMultiplication(); }
			| statement DIVISION statement { handle.onDivision(); }
			;

sum
			: statement ADDITION statement { handle.onAddition(); }
			| statement SUBTRACTION statement { handle.onSubtraction(); }
			;

%%

void FractalProgram::ProgramParser::error(const location_type &l, const std::string &msg) {
	std::cerr << "Parse error: " << msg << " at: " << l << std::endl;

	std::cerr << "Exiting...\n";
	exit(-1);
}
