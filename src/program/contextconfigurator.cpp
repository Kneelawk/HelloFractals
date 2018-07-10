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

#include "contextconfigurator.h"

using namespace FractalProgram;

FractalProgram::ContextConfigurator::ContextConfigurator() {
}

FractalProgram::ContextConfigurator::~ContextConfigurator() {
}

void FractalProgram::ContextConfigurator::enableStandardFunctions() {
	// real - set the imaginary part to 0, leaving only the real part
	addFunction(FunctionDescription("real", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::complex<double>(args[0].real(), 0);
	});

	// imag - set the real part to 0, leaving only the imaginary part
	addFunction(FunctionDescription("imag", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::complex<double>(0, args[0].imag());
	});

	// swap - swap the real and imaginary parts
	addFunction(FunctionDescription("swap", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::complex<double>(args[0].imag(), args[0].real());
	});

	// abs - find the absolute value of the complex number (magnitude via pothagorian theorm)
	addFunction(FunctionDescription("abs", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::complex<double>(std::abs(args[0]));
	});

	// arg - find the phase angle of the complex number
	addFunction(FunctionDescription("arg", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::complex<double>(std::arg(args[0]));
	});

	// sin - find the complex sine of the complex number
	addFunction(FunctionDescription("sin", 1), [](RuntimeContext & ctx, std::vector<std::complex<double> > args) {
		return std::sin(args[0]);
	});
}

void FractalProgram::ContextConfigurator::addVariable(std::string name, std::complex<double> value) {
	variables[name] = value;
}

void FractalProgram::ContextConfigurator::addFunction(FractalProgram::FunctionDescription desc, FractalProgram::RuntimeBuiltinFunction func) {
	functions[desc] = func;
}

void FractalProgram::ContextConfigurator::addFunction(FractalProgram::FunctionDescription desc, FractalProgram::RuntimeBuiltinFunctionTarget func) {
	addFunction(desc, RuntimeBuiltinFunction(func));
}

void FractalProgram::ContextConfigurator::apply(FractalProgram::RuntimeContext &ctx) {
	RuntimeScope *scope = ctx.currentScope();

	for (auto it = variables.begin(); it != variables.end(); it++) {
		scope->defineVariable(it->first, it->second);
	}

	for (auto it = functions.begin(); it != functions.end(); it++) {
		scope->defineFunction(it->first, std::make_unique<RuntimeBuiltinFunction>(it->second));
	}
}

void FractalProgram::ContextConfigurator::apply(FractalProgram::ValidationContext &ctx) {
	ValidationScope *scope = ctx.currentScope();

	for (auto it = variables.begin(); it != variables.end(); it++) {
		scope->defineVariable(it->first);
	}

	for (auto it = functions.begin(); it != functions.end(); it++) {
		scope->defineFunction(it->first);
	}
}





