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

#ifndef FRACTALPROGRAM_FUNCTIONDESCRIPTION_H
#define FRACTALPROGRAM_FUNCTIONDESCRIPTION_H

#include <cstddef>
#include <string>

namespace FractalProgram {

class FunctionDescription {
public:
	FunctionDescription();

	FunctionDescription(std::string name, std::size_t numArgs);

	virtual ~FunctionDescription();

	void setName(std::string name);

	std::string getName();

	void setNumberOfArguments(std::size_t numArgs);

	std::size_t getNumberOfArguments();

	bool operator<(const FunctionDescription &other) const;

private:
	std::string name;
	std::size_t numArgs;
};
}

#endif // FRACTALPROGRAM_VALIDATIONFUNCTION_H







