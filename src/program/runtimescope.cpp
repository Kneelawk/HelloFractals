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

#include "runtimescope.h"

FractalProgram::RuntimeScope::RuntimeScope() {
	instances.push_back(RuntimeScopeInstance());
}

FractalProgram::RuntimeScope::~RuntimeScope() {
}

void FractalProgram::RuntimeScope::defineVariable(std::string name, std::complex<double> value) {
	instances.back().defineVariable(name, value);
}

bool FractalProgram::RuntimeScope::isVariableDefined(std::string name) {
	for (auto it = instances.rbegin(); it != instances.rend(); it++) {
		if (it->isVariableDefined(name)) {
			return true;
		}
	}
	return false;
}

std::complex<double> *FractalProgram::RuntimeScope::getVariable(std::string name) {
	for (auto it = instances.rbegin(); it != instances.rend(); it++) {
		if (it->isVariableDefined(name)) {
			return &it->getVariable(name);
		}
	}
	return nullptr;
}

void FractalProgram::RuntimeScope::push() {
	instances.push_back(RuntimeScopeInstance());
}

void FractalProgram::RuntimeScope::pop() {
	if (instances.size() <= 1) {
		throw RuntimeException("Scope Block Stack Underflow");
	}
	instances.pop_back();
}
