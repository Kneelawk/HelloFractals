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

#include "programdriver.h"

FractalProgram::ProgramDriver::ProgramDriver() {
}

FractalProgram::ProgramDriver::~ProgramDriver() {
}

FractalProgram::Program *FractalProgram::ProgramDriver::parse(std::istream &is) {
	if (is.good() && !is.eof()) {
		return parse_impl(is);
	}
	return nullptr;
}

FractalProgram::Program *FractalProgram::ProgramDriver::parse_impl(std::istream &is) {
	ProgramLexer lexer(&is);

	ProgramHandler handle;

	ProgramParser parser(lexer, handle);

	if (parser.parse() != 0) {
		std::cerr << "Parse failed\n";
		return nullptr;
	}

	return handle.getProgram();
}
