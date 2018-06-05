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

#include "subtraction.h"

#include "stringutils.h"

using namespace FractalProgram;

FractalProgram::Subtraction::Subtraction() {
}

FractalProgram::Subtraction::~Subtraction() {
}

void Subtraction::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "Subtraction(\n";
	l->toString(s, i + 1);
	s << ",\n";
	r->toString(s, i + 1);
	s << "\n";
	s << indent(i) << ")";
}

std::complex< double > Subtraction::getValue(FractalProgram::RuntimeContext &ctx) {
	return l->getValue(ctx) - r->getValue(ctx);
}

void Subtraction::validate(FractalProgram::ValidationContext &ctx) {
	l->validate(ctx);
	r->validate(ctx);
}

void FractalProgram::Subtraction::setLeft(std::unique_ptr<Statement> l) {
	this->l = std::move(l);
}

void FractalProgram::Subtraction::setRight(std::unique_ptr<Statement> r) {
	this->r = std::move(r);
}
