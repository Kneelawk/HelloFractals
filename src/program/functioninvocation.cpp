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

#include <iostream>

#include "functioninvocation.h"

#include "stringutils.h"
#include "runtimecontext.h"
#include "validationcontext.h"
#include "functiondescription.h"
#include "runtimefunction.h"

using namespace FractalProgram;

FractalProgram::FunctionInvocation::FunctionInvocation() {
}

FractalProgram::FunctionInvocation::~FunctionInvocation() {
}

void FunctionInvocation::validate(FractalProgram::ValidationContext &ctx) {
	ValidationScope *scope = ctx.currentScope();
	if (!scope->isFunctionDefined(FunctionDescription(name, arguments.size()))) {
		throw ValidationException("Function '" + name + "' with " + std::to_string(arguments.size()) + " arguments is not defined", loc);
	}

	for (auto it = arguments.begin(); it != arguments.end(); it++) {
		(*it)->validate(ctx);
	}
}

std::complex< double > FunctionInvocation::getValue(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope *scope = ctx.currentScope();

	std::vector<std::complex<double> > argumentValues;
	for (auto it = arguments.begin(); it != arguments.end(); it++) {
		argumentValues.push_back((*it)->getValue(ctx));
	}

	RuntimeFunction *func = scope->getFunction(FunctionDescription(name, arguments.size()));
	return func->invoke(ctx, argumentValues);
}

void FunctionInvocation::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "FunctionInvocation(\n";
	s << indent(i + 1) << '"' << name << '"';
	if (!arguments.empty()) {
		s << ",\n";
		for (size_t n = 0; n < arguments.size() - 1; n++) {
			arguments[n]->toString(s, i + 1);
			s << ",\n";
		}
		arguments.back()->toString(s, i + 1);
	}
	s << '\n';
	s << indent(i) << ')';
}

void FractalProgram::FunctionInvocation::setName(std::string name) {
	this->name = name;
}

void FractalProgram::FunctionInvocation::setArguments(std::vector<std::unique_ptr<Statement> > arguments) {
	this->arguments = std::move(arguments);
}
