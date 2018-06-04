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

#ifndef FRACTALPROGRAM_PARSINGEXCEPTION_H
#define FRACTALPROGRAM_PARSINGEXCEPTION_H

#include <exception>
#include <string>
#include "programparser.tab.hpp"

namespace FractalProgram {

class ParsingException : public std::exception {
public:

	ParsingException(std::string msg, const FractalProgram::ProgramParser::location_type loc);

	virtual ~ParsingException();

	virtual const char *what() const noexcept override;

	std::string getMsg();

	FractalProgram::ProgramParser::location_type getLoc();

private:
	std::string msg;
	FractalProgram::ProgramParser::location_type loc;
	std::string whatString;
};
}

#endif // FRACTALPROGRAM_PARSINGEXCEPTION_H
