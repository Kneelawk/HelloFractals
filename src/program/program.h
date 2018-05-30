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

#ifndef FRACTALPROGRAM_PROGRAM_H
#define FRACTALPROGRAM_PROGRAM_H

#include <complex>
#include <memory>

#include "statement.h"
#include "runtimecontext.h"
#include "validationcontext.h"

namespace FractalProgram {

class Program {
public:

	Program();

	virtual ~Program();

	void setStatement(std::shared_ptr<Statement> s);

	std::shared_ptr<Statement> getStatement();

	void validate();

	std::complex<double> run(std::complex<double> z, std::complex<double> c);

private:

	std::shared_ptr<Statement> statement;
};
}

#endif // FRACTALPROGRAM_PROGRAM_H