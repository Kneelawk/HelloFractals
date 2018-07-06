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

#include "runtimeprogramfunction.h"
#include "runtimescope.h"
#include "runtimecontext.h"

using namespace FractalProgram;

FractalProgram::RuntimeProgramFunction::RuntimeProgramFunction() : name(""), argumentNames(), body(nullptr) {
}

FractalProgram::RuntimeProgramFunction::RuntimeProgramFunction(std::string name, std::vector<std::string> args, FractalProgram::Statement *body, std::shared_ptr<RuntimeScope> scope)
	: name(name), argumentNames(args), body(body), scope(scope) {
}

FractalProgram::RuntimeProgramFunction::~RuntimeProgramFunction() {
}

void FractalProgram::RuntimeProgramFunction::setName(std::string name) {
	this->name = name;
}

std::string FractalProgram::RuntimeProgramFunction::getName() {
	return name;
}

void FractalProgram::RuntimeProgramFunction::setArguments(std::vector<std::string> args) {
	this->argumentNames = args;
}

std::vector<std::string> FractalProgram::RuntimeProgramFunction::getArguments() {
	return argumentNames;
}

void FractalProgram::RuntimeProgramFunction::setBody(FractalProgram::Statement *body) {
	this->body = body;
}

FractalProgram::Statement *FractalProgram::RuntimeProgramFunction::getBody() {
	return body;
}

void FractalProgram::RuntimeProgramFunction::setScope(std::shared_ptr<RuntimeScope> scope) {
	this->scope = scope;
}

std::shared_ptr<RuntimeScope> FractalProgram::RuntimeProgramFunction::getScope() {
	return scope;
}

std::complex<double> FractalProgram::RuntimeProgramFunction::invoke(FractalProgram::RuntimeContext &ctx, std::vector<std::complex<double> > arguments) {
	ctx.push(scope);
	scope->push();

	for (size_t i = 0; i < argumentNames.size(); i++) {
		scope->defineVariable(argumentNames[i], arguments[i]);
	}

	std::complex<double> value = body->getValue(ctx);

	scope->pop();
	ctx.pop();

	return value;
}
