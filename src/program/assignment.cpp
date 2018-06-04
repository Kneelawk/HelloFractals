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

#include "assignment.h"

#include "stringutils.h"

using namespace FractalProgram;

Assignment::Assignment() {
}

FractalProgram::Assignment::~Assignment() {
}

void Assignment::validate(FractalProgram::ValidationContext &ctx) {
	ValidationScope scope = ctx.currentScope();
	if (!scope.isVariableDefined(name)) {
		throw ValidationException("Variable '" + name + "' is not defined", loc);
	}
	statement->validate(ctx);
}

std::complex< double > Assignment::getValue(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope scope = ctx.currentScope();
	std::complex<double> value = statement->getValue(ctx);
	*scope.getVariable(name) = value;
	return value;
}

void Assignment::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "Assignment(\n";
	s << indent(i + 1) << "\"" << name << "\",\n";
	statement->toString(s, i + 1);
	s << "\n";
	s << indent(i) << ")";
}

void FractalProgram::Assignment::setName(std::string name) {
	this->name = name;
}

void FractalProgram::Assignment::setStatement(std::unique_ptr<Statement> statement) {
	this->statement = std::move(statement);
}
