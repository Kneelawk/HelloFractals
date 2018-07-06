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

#ifndef FRACTALPROGRAM_RUNTIMEPROGRAMFUNCTION_H
#define FRACTALPROGRAM_RUNTIMEPROGRAMFUNCTION_H

#include <string>
#include <vector>
#include <memory>

#include "statement.h"
#include "runtimefunction.h"

namespace FractalProgram {

class RuntimeScope;

class RuntimeProgramFunction : public FractalProgram::RuntimeFunction {
public:
	RuntimeProgramFunction();

	RuntimeProgramFunction(std::string name, std::vector<std::string> args, Statement *body, std::shared_ptr<RuntimeScope> scope);

	virtual ~RuntimeProgramFunction();

	void setName(std::string name);

	std::string getName();

	void setArguments(std::vector<std::string> args);

	std::vector<std::string> getArguments();

	void setBody(Statement *body);

	Statement *getBody();

	void setScope(std::shared_ptr<RuntimeScope> scope);

	std::shared_ptr<RuntimeScope> getScope();

	virtual std::complex<double> invoke(FractalProgram::RuntimeContext &ctx, std::vector<std::complex<double> > arguments);

private:
	std::string name;
	std::vector<std::string> argumentNames;
	Statement *body;
	std::shared_ptr<RuntimeScope> scope;
};
}

#endif // FRACTALPROGRAM_RUNTIMEFUNCTION_H
