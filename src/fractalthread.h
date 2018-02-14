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

#include "valuegenerator.h"

class FractalThread
{
public:
	
	/**
	 * FractalThread constructor.
	 */
	FractalThread();
	
	/**
	 * FractalThread destructor.
	 */
	virtual ~FractalThread();
	
	/**
	 * Generate a fractal RGBA image.
	 * Assumes imgData is [height][width * 4] (4 bytes per pixel).
	 */
	void generateImage(std::uint8_t **imgData, std::uint32_t imgWidth, std::size_t size, std::size_t offset, std::size_t skip, ValueGenerator gen);
	
	/**
	 * Generate a fractal value map.
	 * Assumes mapData is [height][width].
	 */
	void generateMap(std::uint32_t **mapData, std::uint32_t mapWidth, std::size_t size, std::size_t offset, std::size_t skip, ValueGenerator gen);
	
	/**
	 * Gets the progress out of 100.
	 */
	double getProgress();
	
	/**
	 * Is this FractalThread done generating.
	 */
	bool isDone();
	
private:
	
	std::atomic<double> progress;
	std::atomic_bool running;
	std::atomic_bool done;
	std::thread *t;
	
	void imageThreadFunc(uint8_t **imgData, uint32_t imgWidth, std::size_t size, std::size_t offset, std::size_t skip, ValueGenerator gen);
	void mapThreadFunc(uint32_t **mapData, uint32_t mapWidth, std::size_t size, std::size_t offset, std::size_t skip, ValueGenerator gen);
	
};

#endif // FRACTALTHREAD_H

