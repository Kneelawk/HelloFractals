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
 */

#ifndef FRACTALPROGRAM_MULTIPLICATION_H
#define FRACTALPROGRAM_MULTIPLICATION_H

#include <memory>

#include "statement.h"

namespace FractalProgram {

/**
 * @todo write docs
 */
class Multiplication : public FractalProgram::Statement {
public:
	Multiplication();

	virtual ~Multiplication();

	virtual void toString(std::ostream &s, std::size_t i) override;

	virtual std::complex< double > getValue(FractalProgram::RuntimeContext &ctx) override;

	virtual void validate(FractalProgram::ValidationContext &ctx) override;

	void setLeft(std::unique_ptr<Statement> l);

	void setRight(std::unique_ptr<Statement> r);

private:
	std::unique_ptr<FractalProgram::Statement> l;
	std::unique_ptr<FractalProgram::Statement> r;
};

}

#endif // FRACTALPROGRAM_MULTIPLICATION_H
