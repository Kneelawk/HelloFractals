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

#include "runtimescopeinstance.h"

#include "functiondescription.h"
#include "runtimefunction.h"

FractalProgram::RuntimeScopeInstance::RuntimeScopeInstance() {
}

FractalProgram::RuntimeScopeInstance::~RuntimeScopeInstance() {
}

void FractalProgram::RuntimeScopeInstance::defineVariable(std::string name, std::complex<double> value) {
	variables[name] = std::make_shared<std::complex<double> >(value);
}

void FractalProgram::RuntimeScopeInstance::addVariableReference(std::string name, std::shared_ptr<std::complex<double> > ref) {
	variables[name] = ref;
}

bool FractalProgram::RuntimeScopeInstance::isVariableDefined(std::string name) {
	return variables.count(name);
}

std::shared_ptr<std::complex<double> > FractalProgram::RuntimeScopeInstance::getVariable(std::string name) {
	return variables[name];
}

void FractalProgram::RuntimeScopeInstance::defineFunction(FractalProgram::FunctionDescription desc, std::unique_ptr<FractalProgram::RuntimeFunction> func) {
	functions[desc] = std::move(func);
}

void FractalProgram::RuntimeScopeInstance::addFunctionReference(FractalProgram::FunctionDescription desc, std::shared_ptr<RuntimeFunction> ref) {
	functions[desc] = ref;
}

bool FractalProgram::RuntimeScopeInstance::isFunctionDefined(FractalProgram::FunctionDescription desc) {
	return functions.count(desc);
}

std::shared_ptr<FractalProgram::RuntimeFunction> FractalProgram::RuntimeScopeInstance::getFunction(FractalProgram::FunctionDescription desc) {
	return functions[desc];
}
