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

FractalProgram::ProgramHandler::ProgramHandler() {
	program = new Program();
	std::shared_ptr<Block> base(new Block());

	program->setStatement(base);
	blocks.push(base);
}

FractalProgram::ProgramHandler::~ProgramHandler() {
}

FractalProgram::Program *FractalProgram::ProgramHandler::getProgram() {
	return program;
}

void FractalProgram::ProgramHandler::onDeclaration(std::string name) {
	std::cout << "Declaration: " << name << std::endl;
}

void FractalProgram::ProgramHandler::onAssignment(std::string name) {
	std::cout << "Assignment: " << name << std::endl;
}

void FractalProgram::ProgramHandler::onImaginaryNumber(double num) {
	std::cout << "Imaginary Number: " << num << "i\n";
}

void FractalProgram::ProgramHandler::onNumber(double num) {
	std::cout << "Number: " << num << std::endl;
}

void FractalProgram::ProgramHandler::onVariable(std::string name) {
	std::cout << "Variable: " << name << std::endl;
}

void FractalProgram::ProgramHandler::onOpenParenthesis() {
	std::cout << "Open Parenthesis\n";
}

void FractalProgram::ProgramHandler::onCloseParenthesis() {
	std::cout << "Close Parenthesis\n";
}

void FractalProgram::ProgramHandler::onExponent() {
	std::cout << "Exponent\n";
}

void FractalProgram::ProgramHandler::onMultiplication() {
	std::cout << "Multiplication\n";
}

void FractalProgram::ProgramHandler::onDivision() {
	std::cout << "Division\n";
}

void FractalProgram::ProgramHandler::onAddition() {
	std::cout << "Addition\n";
}

void FractalProgram::ProgramHandler::onSubtraction() {
	std::cout << "Subtraction\n";
}
