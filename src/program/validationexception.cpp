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

#include <sstream>

#include "validationexception.h"

using namespace FractalProgram;

FractalProgram::ValidationException::ValidationException(std::string s) : msg(s), whatString(s) {
}

FractalProgram::ValidationException::ValidationException(std::string s, ProgramParser::location_type loc) : msg(s), loc(loc) {
	std::stringstream ss;
	ss << msg << " at: " << loc;
	whatString = ss.str();
}

FractalProgram::ValidationException::~ValidationException() {
}

const char *FractalProgram::ValidationException::what() const noexcept {
	return whatString.c_str();
}

std::string FractalProgram::ValidationException::getMsg() {
	return msg;
}

ProgramParser::location_type FractalProgram::ValidationException::getLoc() {
	return loc;
}
