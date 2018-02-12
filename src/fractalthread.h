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

#ifndef FRACTALTHREAD_H
#define FRACTALTHREAD_H

#include <thread>
#include <atomic>

#include "math_utils.h"
#include "valuegenerator.h"

class FractalThread
{
public:
	
	/**
	 * FractalThread constructor.
	 * Assumes imgData is ARGB 8 bit per color pixel data.
	 */
	FractalThread(char *imgData, uint32_t imgWidth, size_t size, size_t offset, size_t skip, ValueGenerator &gen);
	
	/**
	 * FractalThread destructor.
	 */
	virtual ~FractalThread();
	
	/**
	 * Start the fractal generator.
	 */
	void start();
	
	double getProgress();
	
private:
	
	char *imgData;
	uint32_t imgWidth;
	size_t size;
	size_t offset;
	size_t skip;
	ValueGenerator &gen;
	
	std::atomic<double> progress;
	std::thread *t;
	
	void threadFunc();
	
};

#endif // FRACTALTHREAD_H

