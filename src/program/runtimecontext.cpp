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

#include "runtimecontext.h"

using namespace FractalProgram;

FractalProgram::RuntimeContext::RuntimeContext() {
	scopes.push(std::make_shared<RuntimeScope>());
}

FractalProgram::RuntimeContext::~RuntimeContext() {
}

void FractalProgram::RuntimeContext::push(std::shared_ptr<RuntimeScope> newScope) {
	scopes.push(newScope);
}

void FractalProgram::RuntimeContext::pop() {
	if (scopes.size() <= 1) {
		throw RuntimeException("Scope Stack Underflow");
	}
	scopes.pop();
}

FractalProgram::RuntimeScope *FractalProgram::RuntimeContext::currentScope() {
	return scopes.top().get();
}
