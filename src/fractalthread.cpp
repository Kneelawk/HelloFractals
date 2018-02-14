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

#include "fractalthread.h"

#include "math_utils.h"

using namespace std;

FractalThread::FractalThread() {
	progress = 0;
	running = false;
	done = false;
	t = nullptr;
}

FractalThread::~FractalThread() {
	if (t != nullptr) {
		t->join();
		delete t;
		t = nullptr;
	}
}

void FractalThread::generateImage(uint8_t **imgData, uint32_t imgWidth, size_t size, size_t offset, size_t skip, ValueGenerator gen) {
	if (!running) {
		running = true;
		t = new thread(&FractalThread::imageThreadFunc, this, imgData, imgWidth, size, offset, skip, gen);
	}
}

void FractalThread::generateMap(uint32_t **mapData, uint32_t mapWidth, size_t size, size_t offset, size_t skip, ValueGenerator gen) {
	if (!running) {
		running = true;
		t = new thread(&FractalThread::mapThreadFunc, this, mapData, mapWidth, size, offset, skip, gen);
	}
}


double FractalThread::getProgress() {
	return progress;
}

bool FractalThread::isDone() {
	return done;
}

void FractalThread::imageThreadFunc(uint8_t **imgData, uint32_t imgWidth, size_t size, size_t offset, size_t skip, ValueGenerator gen) {
	size_t j;
	uint32_t x, y;
	RGB_Color col;

	for (size_t i = 0; i < size; i++) {
		j = i * skip + offset;
		x = j % imgWidth;
		y = j / imgWidth;

		col = gen.genPixel(x, y);

		imgData[y][x * 4] = col.r;
		imgData[y][x * 4 + 1] = col.g;
		imgData[y][x * 4 + 2] = col.b;
		imgData[y][x * 4 + 3] = 0xFF;

		progress = (i + 1) * 100.0 / size;
	}

	done = true;
	running = false;
}

void FractalThread::mapThreadFunc(uint32_t **mapData, uint32_t mapWidth, size_t size, size_t offset, size_t skip, ValueGenerator gen) {
	size_t j;
	uint32_t x, y;
	
	for (size_t i = 0; i < size; i++) {
		j = i * skip + offset;
		x = j % mapWidth;
		
		mapData[y][x] = gen.genPixelValue(x, y);
		
		progress = (i + 1) * 100.0 / size;
	}
	
	done = true;
	running = false;
}
