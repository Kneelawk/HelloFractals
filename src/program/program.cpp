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

#include <sstream>

#include "program.h"

FractalProgram::Program::Program() {
}

FractalProgram::Program::~Program() {
}

void FractalProgram::Program::setStatement(std::unique_ptr<FractalProgram::Statement> s) {
	statement = std::move(s);
}

FractalProgram::Statement *FractalProgram::Program::getStatement() {
	return statement.get();
}

void FractalProgram::Program::validate() {
	ValidationContext ctx;

	ctx.currentScope()->defineVariable("z");
	ctx.currentScope()->defineVariable("c");

	statement->validate(ctx);
}

std::complex<double> FractalProgram::Program::run(std::complex<double> z, std::complex<double> c) {
	RuntimeContext ctx;

	ctx.currentScope()->defineVariable("z", z);
	ctx.currentScope()->defineVariable("c", c);

	return statement->getValue(ctx);
}

void FractalProgram::Program::validate(FractalProgram::ValidationContext &ctx) {
	statement->validate(ctx);
}

std::complex<double> FractalProgram::Program::run(FractalProgram::RuntimeContext &ctx) {
	return statement->getValue(ctx);
}

std::string FractalProgram::Program::to_string() {
	std::stringstream ss;
	ss << "Program(\n";
	statement->toString(ss, 1);
	ss << "\n)";
	return ss.str();
}
