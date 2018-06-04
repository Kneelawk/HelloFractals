%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define api.namespace { FractalProgram }
%define parser_class_name { ProgramParser }

%code requires {
namespace FractalProgram {
class ProgramLexer;
class ProgramHandler;
class ParsingException;
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
#include "parsingexception.h"

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
			: lines END
			;

lines
			: line
			| lines newlines line
			;

line
			: %empty
			| statement { handle.onStatement(@$); }
			;

newlines
			: NEWLINE
			| newlines NEWLINE
			;

statement
			: sum_expression
			;

declaration
			: VAR STRING EQUALS statement { handle.onDeclaration($2, @$); }
			;

assignment
			: STRING EQUALS statement { handle.onAssignment($1, @$); }
			;

sum_expression
			: sum
			| difference
			| product_expression
			;

product_expression
			: product
			| quotient
			| exponent_expression
			;

exponent_expression
			: exponent
			| other_expression
			;

other_expression
			: number
			| variable
			| parenthesis
			| declaration
			| assignment
			;

number
			: IMAGINARY_NUMBER { handle.onImaginaryNumber($1, @$); }
			| NUMBER { handle.onNumber($1, @$); }
			;

variable
			: STRING { handle.onVariable($1, @$); }
			;

parenthesis
			: open_parenthesis statement CLOSE_PARENTHESIS { handle.onCloseParenthesis(@$); }
			;

open_parenthesis
			: OPEN_PARENTHESIS { handle.onOpenParenthesis(@$); }
			;

exponent
			: exponent_expression EXPONENT exponent_expression { handle.onExponent(@$); }
			;

product
			: product_expression MULTIPLICATION product_expression { handle.onMultiplication(@$); }
			;

quotient
			: product_expression DIVISION product_expression { handle.onDivision(@$); }
			;

sum
			: sum_expression ADDITION sum_expression { handle.onAddition(@$); }
			;

difference
			: sum_expression SUBTRACTION sum_expression { handle.onSubtraction(@$); }
			;

%%

void FractalProgram::ProgramParser::error(const location_type &l, const std::string &msg) {
	throw FractalProgram::ParsingException(msg, l);
}
