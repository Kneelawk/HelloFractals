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

#include "valuegenerator.h"

ValueGenerator::ValueGenerator(uint32_t imgWidth, uint32_t imgHeight, double planeWidth, double planeHeight, double planeStartX,
							   double planeStartY, bool mandelbrot, uint32_t iterations, double cReal, double cImaginary) :
	imgWidth(imgWidth), imgHeight(imgHeight), planeWidth(planeWidth), planeHeight(planeHeight), planeStartX(planeStartX),
	planeStartY(planeStartY), mandelbrot(mandelbrot), iterations(iterations), cReal(cReal), cImaginary(cImaginary) {
}

ValueGenerator::~ValueGenerator() {
}

uint32_t ValueGenerator::genValue(double x, double y) {
	double a = x, b = y, aa, bb, twoab;
	uint32_t n = 0;

	if (mandelbrot) {
		for (; n < iterations; n++) {
			aa = a * a;
			bb = b * b;
			twoab = 2 * a * b;

			a = aa - bb + x;
			b = twoab + y;

			if (aa + bb > 16) {
				break;
			}
		}
	} else {
		for (; n < iterations; n++) {
			aa = a * a;
			bb = b * b;
			twoab = 2 * a * b;

			a = aa - bb + cReal;
			b = twoab + cImaginary;

			if (aa + bb > 16) {
				break;
			}
		}
	}

	return n;
}

RGB_Color ValueGenerator::genColor(uint32_t n) {
	if (n < iterations) {
		return fromHSB(mod2(n * 3.3, 0, 256) / 256.0, 1.0, mod2(n * 16.0, 0, 256) / 256.0);
	} else {
		return {0, 0, 0};
	}
}

RGB_Color ValueGenerator::genPixel(uint32_t x, uint32_t y) {
	return (genColor(genValue(x * planeWidth / imgWidth + planeStartX, y * planeHeight / imgHeight + planeStartY)));
}

uint32_t ValueGenerator::getImgWidth() {
	return imgWidth;
}

uint32_t ValueGenerator::getImgHeight() {
	return imgHeight;
}

double ValueGenerator::getPlaneWidth() {
	return planeWidth;
}

double ValueGenerator::getPlaneHeight() {
	return planeHeight;
}

double ValueGenerator::getPlaneStartX() {
	return planeStartX;
}

double ValueGenerator::getPlaneStartY() {
	return planeStartY;
}

bool ValueGenerator::isMandelbrot() {
	return mandelbrot;
}

uint32_t ValueGenerator::getIterations() {
	return iterations;
}

double ValueGenerator::getCReal() {
	return cReal;
}

double ValueGenerator::getCImaginary() {
	return cImaginary;
}
