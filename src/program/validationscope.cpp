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

#include "validationscope.h"

FractalProgram::ValidationScope::ValidationScope() {
	instances.push_back(ValidationScopeInstance());
}

FractalProgram::ValidationScope::~ValidationScope() {
}

void FractalProgram::ValidationScope::defineVariable(std::string name) {
	instances.back().defineVariable(name);
}

bool FractalProgram::ValidationScope::isVariableDefined(std::string name) {
	for (auto it = instances.rbegin(); it != instances.rend(); it++) {
		if (it->isVariableDefined(name)) {
			return true;
		}
	}
	return false;
}

bool FractalProgram::ValidationScope::isTopVariableDefined(std::string name) {
	return instances.back().isVariableDefined(name);
}

void FractalProgram::ValidationScope::push() {
	instances.push_back(ValidationScopeInstance());
}

void FractalProgram::ValidationScope::pop() {
	if (instances.size() <= 1) {
		throw ValidationException("Scope Block Stack Underflow");
	}
	instances.pop_back();
}
