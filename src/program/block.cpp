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

#include "block.h"

#include "validationcontext.h"
#include "runtimecontext.h"
#include "stringutils.h"

using namespace FractalProgram;

FractalProgram::Block::Block() {
}

FractalProgram::Block::~Block() {
}

void FractalProgram::Block::appendStatement(std::unique_ptr<FractalProgram::Statement> s) {
	statements.push_back(std::move(s));
}

void FractalProgram::Block::validate(FractalProgram::ValidationContext &ctx) {
	ValidationScope *scope = ctx.currentScope();
	scope->push();
	for (auto it = statements.begin(); it != statements.end(); it++) {
		it->get()->validate(ctx);
	}
	scope->pop();
}

std::complex<double> FractalProgram::Block::getValue(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope *scope = ctx.currentScope();
	scope->push();
	if (!statements.empty()) {
		for (size_t i = 0; i < statements.size() - 1; i++) {
			statements[i]->getValue(ctx);
		}
	}
	std::complex<double> val = statements.back()->getValue(ctx);
	scope->pop();
	return val;
}

void FractalProgram::Block::toString(std::ostream &s, std::size_t i) {
	s << indent(i) << "Block(\n";
	for (size_t n = 0; n < statements.size() - 1; n++) {
		statements[n]->toString(s, i + 1);
		s << ",\n";
	}
	statements.back()->toString(s, i + 1);
	s << "\n";
	s << indent(i) << ")";
}




