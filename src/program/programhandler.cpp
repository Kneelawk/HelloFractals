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
#include "multiplication.h"
#include "division.h"
#include "addition.h"
#include "subtraction.h"
#include "functiondefinition.h"
#include "functioninvocation.h"

using namespace FractalProgram;

FractalProgram::ProgramHandler::ProgramHandler() {
	currentBlock = std::make_unique<Block>();
}

FractalProgram::ProgramHandler::~ProgramHandler() {
}

std::unique_ptr<FractalProgram::Program> FractalProgram::ProgramHandler::finish() {
	if (statements.size() > 0) {
		std::stringstream ss;
		ss << "Unused expressions still on the stack:\n";
		for (std::size_t i = 0; i < statements.size(); i++) {
			statements.top()->toString(ss, 0);
			statements.pop();
			ss << "\n";
		}
		ss << "something broke";

		throw ParsingException(ss.str(), ProgramParser::location_type());
	}

	std::unique_ptr<Program> program = std::make_unique<Program>();
	program->setStatement(std::move(currentBlock));
	return program;
}

void FractalProgram::ProgramHandler::onStatement(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Statement at: " << loc << std::endl;
#endif

	if (statements.size() < 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	currentBlock->appendStatement(std::move(statements.top()));
	statements.pop();
}

void FractalProgram::ProgramHandler::onDeclaration(std::string name, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Declaration: " << name << " at: " << loc << std::endl;
#endif

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
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Assignment: " << name << " at: " << loc << std::endl;
#endif

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
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Imaginary Number: " << num << "i at: " << loc << std::endl;
#endif
	std::unique_ptr<Constant> constant = std::make_unique<Constant>();
	constant->setLocation(loc);
	constant->setValue(std::complex<double>(0, num));
	statements.push(std::move(constant));
}

void FractalProgram::ProgramHandler::onNumber(double num, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Number: " << num << " at: " << loc << std::endl;
#endif
	std::unique_ptr<Constant> constant = std::make_unique<Constant>();
	constant->setLocation(loc);
	constant->setValue(std::complex<double>(num, 0));
	statements.push(std::move(constant));
}

void FractalProgram::ProgramHandler::onVariable(std::string name, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Variable: " << name << " at: " << loc << std::endl;
#endif
	std::unique_ptr<Variable> variable = std::make_unique<Variable>();
	variable->setLocation(loc);
	variable->setName(name);
	statements.push(std::move(variable));
}

void FractalProgram::ProgramHandler::onFunctionDeclarationArgument(std::string name, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Function Declaration Argument: " << name << " at: " << loc << std::endl;
#endif
	functionDeclarationArgs.push_back(name);
}

void FractalProgram::ProgramHandler::onFunctionDeclaration(std::string name, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Function Declaration: " << name << " at: " << loc << std::endl;
#endif
	functionDeclarationName = name;
}

void FractalProgram::ProgramHandler::onFunctionDefinition(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Function Definition at: " << loc << std::endl;
#endif

	if (statements.size() < 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<FunctionDefinition> functionDefinition = std::make_unique<FunctionDefinition>();
	functionDefinition->setLocation(loc);
	functionDefinition->setArguments(functionDeclarationArgs);
	functionDeclarationArgs.clear();
	functionDefinition->setName(functionDeclarationName);
	functionDefinition->setStatement(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(functionDefinition));
}

void FractalProgram::ProgramHandler::onFunctionCallArgument(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Function Call Argument at: " << loc << std::endl;
#endif

	if (statements.size() < 1) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	functionCallArgs.push_back(std::move(statements.top()));
	statements.pop();
}

void FractalProgram::ProgramHandler::onFunctionCall(std::string name, ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Function Call: " << name << " at: " << loc << std::endl;
#endif

	std::unique_ptr<FunctionInvocation> functionInvocation = std::make_unique<FunctionInvocation>();
	functionInvocation->setLocation(loc);
	functionInvocation->setName(name);
	functionInvocation->setArguments(std::move(functionCallArgs));
	statements.push(std::move(functionInvocation));
}

void FractalProgram::ProgramHandler::onOpenParenthesis(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Open Parenthesis at: " << loc << std::endl;
#endif
}

void FractalProgram::ProgramHandler::onCloseParenthesis(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Close Parenthesis at: " << loc << std::endl;
#endif
}

void FractalProgram::ProgramHandler::onOpenBlock(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Open Block at: " << loc << std::endl;
#endif
	oldBlocks.push(std::move(currentBlock));
	currentBlock = std::make_unique<Block>();
}

void FractalProgram::ProgramHandler::onCloseBlock(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Close Block at: " << loc << std::endl;
#endif

	if (oldBlocks.size() < 1) {
		throw ParsingException("Closing out of base block, something broke", loc);
	}

	currentBlock->setLocation(loc);
	statements.push(std::move(currentBlock));
	currentBlock = std::move(oldBlocks.top());
	oldBlocks.pop();
}

void FractalProgram::ProgramHandler::onExponent(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Exponent at: " << loc << std::endl;
#endif

	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<Exponent> exponent = std::make_unique<Exponent>();
	exponent->setLocation(loc);
	exponent->setRight(std::move(statements.top()));
	statements.pop();
	exponent->setLeft(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(exponent));
}

void FractalProgram::ProgramHandler::onMultiplication(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Multiplication at: " << loc << std::endl;
#endif

	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<Multiplication> multiplication = std::make_unique<Multiplication>();
	multiplication->setLocation(loc);
	multiplication->setRight(std::move(statements.top()));
	statements.pop();
	multiplication->setLeft(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(multiplication));
}

void FractalProgram::ProgramHandler::onDivision(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Division at: " << loc << std::endl;
#endif

	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<Division> division = std::make_unique<Division>();
	division->setLocation(loc);
	division->setRight(std::move(statements.top()));
	statements.pop();
	division->setLeft(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(division));
}

void FractalProgram::ProgramHandler::onAddition(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Addition at: " << loc << std::endl;
#endif

	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<Addition> addition = std::make_unique<Addition>();
	addition->setLocation(loc);
	addition->setRight(std::move(statements.top()));
	statements.pop();
	addition->setLeft(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(addition));
}

void FractalProgram::ProgramHandler::onSubtraction(ProgramParser::location_type &loc) {
#ifdef FRACTALPROGRAM_PROGRAMHANDLER_DEBUG
	std::cout << "Subtraction at: " << loc << std::endl;
#endif

	if (statements.size() < 2) {
		throw ParsingException("Invalid statement stack size: " + std::to_string(statements.size()) + ", something broke", loc);
	}

	std::unique_ptr<Subtraction> subtraction = std::make_unique<Subtraction>();
	subtraction->setLocation(loc);
	subtraction->setRight(std::move(statements.top()));
	statements.pop();
	subtraction->setLeft(std::move(statements.top()));
	statements.pop();
	statements.push(std::move(subtraction));
}
