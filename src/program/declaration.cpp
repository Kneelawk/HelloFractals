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

#include "declaration.h"

#include "validationcontext.h"
#include "runtimecontext.h"
#include "stringutils.h"

using namespace FractalProgram;

Declaration::Declaration() {

}

FractalProgram::Declaration::~Declaration() {
}

void Declaration::validate(FractalProgram::ValidationContext &ctx) {
	ValidationScope *scope = ctx.currentScope();
	if (scope->isTopVariableDefined(name)) {
		throw ValidationException("Variable '" + name + "' is already defined", loc);
	}
	statement->validate(ctx);
	scope->defineVariable(name);
}

std::complex< double > Declaration::getValue(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope *scope = ctx.currentScope();
	std::complex<double> value = statement->getValue(ctx);
	scope->defineVariable(name, value);
	return value;
}

void Declaration::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "Declaration(\n";
	s << indent(i + 1) << "\"" << name << "\",\n";
	statement->toString(s, i + 1);
	s << "\n";
	s << indent(i) << ")";
}

void FractalProgram::Declaration::setName(std::string name) {
	this->name = name;
}

void FractalProgram::Declaration::setStatement(std::unique_ptr<FractalProgram::Statement> statement) {
	this->statement = std::move(statement);
}
