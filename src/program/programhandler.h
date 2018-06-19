/*
 * Copyright (c) 2018 Jedidiah Pommert <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef FRACTALPROGRAM_PROGRAMHANDLER_H
#define FRACTALPROGRAM_PROGRAMHANDLER_H

#define FRACTALPROGRAM_PROGRAMHANDLER_DEBUG

#include <iostream>
#include <string>
#include <stack>
#include <memory>

#include "program.h"
#include "block.h"
#include "programparser.tab.hpp"

namespace FractalProgram {

class ProgramHandler {
public:
	ProgramHandler();

	virtual ~ProgramHandler();

	std::unique_ptr<Program> finish();

	/* AST Events go here */

	void onStatement(ProgramParser::location_type &loc);

	void onDeclaration(std::string name, ProgramParser::location_type &loc);

	void onAssignment(std::string name, ProgramParser::location_type &loc);

	void onImaginaryNumber(double num, ProgramParser::location_type &loc);

	void onNumber(double num, ProgramParser::location_type &loc);

	void onVariable(std::string name, ProgramParser::location_type &loc);

	void onFunctionDeclarationArgument(std::string name, ProgramParser::location_type &loc);

	void onFunctionDeclaration(std::string name, ProgramParser::location_type &loc);

	void onFunctionDefinition(ProgramParser::location_type &loc);

	void onFunctionCallArgument(ProgramParser::location_type &loc);

	void onFunctionCall(std::string name, ProgramParser::location_type &loc);

	void onOpenParenthesis(ProgramParser::location_type &loc);

	void onCloseParenthesis(ProgramParser::location_type &loc);

	void onOpenBlock(ProgramParser::location_type &loc);

	void onCloseBlock(ProgramParser::location_type &loc);

	void onExponent(ProgramParser::location_type &loc);

	void onMultiplication(ProgramParser::location_type &loc);

	void onDivision(ProgramParser::location_type &loc);

	void onAddition(ProgramParser::location_type &loc);

	void onSubtraction(ProgramParser::location_type &loc);

private:
	std::unique_ptr<Block> currentBlock;
	std::stack<std::unique_ptr<Block> > oldBlocks;
	std::stack<std::unique_ptr<Statement> > statements;
};

}

#endif // FRACTALPROGRAM_PROGRAMHANDLER_H
