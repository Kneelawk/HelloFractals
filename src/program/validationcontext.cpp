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

#include "validationcontext.h"

using namespace FractalProgram;

FractalProgram::ValidationContext::ValidationContext() {
	scopes.push(std::make_unique<ValidationScope>());
}

FractalProgram::ValidationContext::~ValidationContext() {
}

void FractalProgram::ValidationContext::push(std::unique_ptr<ValidationScope> newScope) {
	scopes.push(std::move(newScope));
}

std::unique_ptr<ValidationScope> FractalProgram::ValidationContext::pop() {
	if (scopes.size() <= 1) {
		throw ValidationException("Scope Stack Underflow");
	}
	std::unique_ptr<ValidationScope> oldScope = std::move(scopes.top());
	scopes.pop();
	return oldScope;
}

FractalProgram::ValidationScope *FractalProgram::ValidationContext::currentScope() {
	return scopes.top().get();
}
