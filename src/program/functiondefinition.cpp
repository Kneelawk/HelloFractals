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

#include "functiondefinition.h"

#include "validationcontext.h"
#include "runtimecontext.h"
#include "stringutils.h"
#include "runtimeprogramfunction.h"

using namespace FractalProgram;

FractalProgram::FunctionDefinition::FunctionDefinition() {
}

FractalProgram::FunctionDefinition::~FunctionDefinition() {
}

void FractalProgram::FunctionDefinition::setArguments(std::vector<std::string> arguments) {
	this->arguments = arguments;
}

void FractalProgram::FunctionDefinition::setName(std::string name) {
	this->name = name;
}

void FractalProgram::FunctionDefinition::setStatement(std::unique_ptr<Statement> statement) {
	this->statement = std::move(statement);
}

void FractalProgram::FunctionDefinition::validate(FractalProgram::ValidationContext &ctx) {
	ValidationScope *scope = ctx.currentScope();

	FunctionDescription desc(name, arguments.size());
	if (scope->isTopFunctionDefined(desc)) {
		throw ValidationException("Function '" + name + "' is already defined", loc);
	}
	scope->push();
	for (auto it = arguments.begin(); it != arguments.end(); it++) {
		scope->defineVariable(*it);
	}
	statement->validate(ctx);
	scope->pop();
	scope->defineFunction(desc);
}

std::complex<double> FractalProgram::FunctionDefinition::getValue(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope *scope = ctx.currentScope();

	FunctionDescription desc(name, arguments.size());
	std::unique_ptr<RuntimeFunction> f = std::make_unique<RuntimeProgramFunction>(name, arguments, statement.get(), scope->makeReferringCopy());

	scope->defineFunction(desc, std::move(f));

	return std::complex<double>(0, 0);
}

void FractalProgram::FunctionDefinition::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "FunctionDefinition(\n";
	s << indent(i + 1) << '"' << name << "\",\n";
	for (auto it = arguments.begin(); it != arguments.end(); it++) {
		s << indent(i + 1) << '"' << *it << "\",\n";
	}
	statement->toString(s, i + 1);
	s << "\n";
	s << indent(i) << ")";
}

