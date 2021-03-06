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

#ifndef FRACTALPROGRAM_RUNTIMECONTEXT_H
#define FRACTALPROGRAM_RUNTIMECONTEXT_H

#include <map>
#include <stack>
#include <memory>

#include "runtimescope.h"
#include "runtimeexception.h"

namespace FractalProgram {

class RuntimeContext {
public:

	RuntimeContext();

	virtual ~RuntimeContext();

	void push(std::shared_ptr<RuntimeScope> newScope);

	void pop();

	RuntimeScope *currentScope();

private:

	std::stack<std::shared_ptr<RuntimeScope> > scopes;
};
}

#endif // FRACTALPROGRAM_RUNTIMECONTEXT_H
