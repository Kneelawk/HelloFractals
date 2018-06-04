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

#include "programhandler.h"

#include "parsingexception.h"
#include "declaration.h"
#include "assignment.h"
#include "constant.h"
#include "variable.h"
#include "exponent.h"

using namespace FractalProgram;

FractalProgram::ProgramHandler::ProgramHandler() {
	currentBlock = std::make_unique<Block>();
}

FractalProgram::ProgramHandler::~ProgramHandler() {
}

std::unique_ptr<FractalProgram::Program> FractalProgram::ProgramHandler::finish() {
	std::unique_ptr<Program> program = std::make_unique<Program>();
	program->setStatement(std::move(currentBlock));
	return program;
}

void FractalProgram::ProgramHandler::onStatement(ProgramParser::location_type &loc) {
	std::cout << "Statement at: " << loc << std::endl;
	if (statements.size() != 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}
	currentBlock->appendStatement(std::move(statements.top()));
	statements.pop();
}

void FractalProgram::ProgramHandler::onDeclaration(std::string name, ProgramParser::location_type &loc) {
	std::cout << "Declaration: " << name << " at: " << loc << std::endl;
	if (statements.size() < 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}
	std::unique_ptr<Declaration> declaration = std::make_unique<Declaration>();
	declaration->setLocation(loc);
	declaration->setName(name);
	declaration->setStatement(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(declaration));
}

void FractalProgram::ProgramHandler::onAssignment(std::string name, ProgramParser::location_type &loc) {
	std::cout << "Assignment: " << name << " at: " << loc << std::endl;
	if (statements.size() < 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}
	std::unique_ptr<Assignment> assignment = std::make_unique<Assignment>();
	assignment->setLocation(loc);
	assignment->setName(name);
	assignment->setStatement(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(assignment));
}

void FractalProgram::ProgramHandler::onImaginaryNumber(double num, ProgramParser::location_type &loc) {
	std::cout << "Imaginary Number: " << num << "i at: " << loc << std::endl;
	std::unique_ptr<Constant> constant = std::make_unique<Constant>();
	constant->setLocation(loc);
	constant->setValue(std::complex<double>(0, num));
	statements.push(std::move(constant));
}

void FractalProgram::ProgramHandler::onNumber(double num, ProgramParser::location_type &loc) {
	std::cout << "Number: " << num << " at: " << loc << std::endl;
	std::unique_ptr<Constant> constant = std::make_unique<Constant>();
	constant->setLocation(loc);
	constant->setValue(std::complex<double>(num, 0));
	statements.push(std::move(constant));
}

void FractalProgram::ProgramHandler::onVariable(std::string name, ProgramParser::location_type &loc) {
	std::cout << "Variable: " << name << " at: " << loc << std::endl;
	std::unique_ptr<Variable> variable = std::make_unique<Variable>();
	variable->setLocation(loc);
	variable->setName(name);
	statements.push(std::move(variable));
}

void FractalProgram::ProgramHandler::onOpenParenthesis(ProgramParser::location_type &loc) {
	std::cout << "Open Parenthesis at: " << loc << std::endl;
}

void FractalProgram::ProgramHandler::onCloseParenthesis(ProgramParser::location_type &loc) {
	std::cout << "Close Parenthesis at: " << loc << std::endl;
}

void FractalProgram::ProgramHandler::onExponent(ProgramParser::location_type &loc) {
	std::cout << "Exponent at: " << loc << std::endl;
	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}
	std::unique_ptr<Exponent> exponent = std::make_unique<Exponent>();
	exponent->setLocation(loc);
	std::unique_ptr<Statement> r = std::move(statements.top());
	statements.pop();
	std::unique_ptr<Statement> l = std::move(statements.top());
	statements.pop();
	exponent->setStatements(std::move(l), std::move(r));
	statements.push(std::move(exponent));
}

void FractalProgram::ProgramHandler::onMultiplication(ProgramParser::location_type &loc) {
	std::cout << "Multiplication at: " << loc << std::endl;
}

void FractalProgram::ProgramHandler::onDivision(ProgramParser::location_type &loc) {
	std::cout << "Division at: " << loc << std::endl;
}

void FractalProgram::ProgramHandler::onAddition(ProgramParser::location_type &loc) {
	std::cout << "Addition at: " << loc << std::endl;
}

void FractalProgram::ProgramHandler::onSubtraction(ProgramParser::location_type &loc) {
	std::cout << "Subtraction at: " << loc << std::endl;
}
