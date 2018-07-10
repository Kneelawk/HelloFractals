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

using namespace std;

ValueGenerator::ValueGenerator(uint32_t imgWidth, uint32_t imgHeight, double planeWidth, double planeHeight, double planeStartX,
							   double planeStartY, bool mandelbrot, uint32_t iterations, double cReal, double cImaginary,
							   GeneratorFunction func
							  ) :
	imgWidth(imgWidth), imgHeight(imgHeight), planeWidth(planeWidth), planeHeight(planeHeight), planeStartX(planeStartX),
	planeStartY(planeStartY), mandelbrot(mandelbrot), iterations(iterations), cReal(cReal), cImaginary(cImaginary), callback(func) {
}

ValueGenerator::~ValueGenerator() {
}

uint32_t ValueGenerator::genValue(double x, double y) {
	std::complex<double> z(x, y), c;
	uint32_t n = 0;

	if (mandelbrot) {
		c = std::complex<double>(x, y);
	} else {
		c = std::complex<double>(cReal, cImaginary);
	}

	for (; n < iterations; n++) {
		if (std::norm(z) > 16) {
			break;
		}

		z = callback(z, c);
	}

	return n;
}

std::uint32_t ValueGenerator::genPixelValue(std::uint32_t x, std::uint32_t y) {
	return genValue(x * planeWidth / imgWidth + planeStartX, y * planeHeight / imgHeight + planeStartY);
}


RGB_Color ValueGenerator::genColor(uint32_t n) {
	if (n < iterations) {
		return fromHSB(mod2(n * 3.3, 0, 256) / 256.0, 1.0, mod2(n * 16.0, 0, 256) / 256.0);
	} else {
		return {0, 0, 0};
	}
}

RGB_Color ValueGenerator::genPixel(uint32_t x, uint32_t y) {
	return genColor(genValue(x * planeWidth / imgWidth + planeStartX, y * planeHeight / imgHeight + planeStartY));
}

ImageLoc ValueGenerator::complex2Image(ComplexLoc loc) {
	return ImageLoc((loc.r - planeStartX) * imgWidth / planeWidth, (loc.i - planeStartY) * imgHeight / planeHeight);
}

ComplexLoc ValueGenerator::image2Complex(ImageLoc loc) {
	return ComplexLoc(loc.x * planeWidth / imgWidth + planeStartX, loc.y * planeHeight / imgHeight + planeStartY);
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
