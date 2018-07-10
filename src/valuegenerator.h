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

#ifndef VALUEGENERATOR_H
#define VALUEGENERATOR_H

#include <cstdint>
#include <functional>
#include <complex>

#include "math_utils.h"
#include "vectors.h"

typedef std::function<std::complex<double> (std::complex<double>, std::complex<double>)> GeneratorFunction;

class ValueGenerator {
public:

	/**
	 * ValueGenerator constructor.
	 */
	ValueGenerator(std::uint32_t imgWidth, std::uint32_t imgHeight, double planeWidth, double planeHeight,
				   double planeStartX, double planeStartY, bool mandelbrot, std::uint32_t iterations, double cReal, double cImaginary,
				   GeneratorFunction func
				  );

	/**
	 * ValueGenerator destructor.
	 */
	virtual ~ValueGenerator();

	/**
	 * Generate the value on the complex plane.
	 */
	std::uint32_t genValue(double x, double y);

	/**
	 * Generate the value of a pixel.
	 */
	std::uint32_t genPixelValue(std::uint32_t x, std::uint32_t y);

	/**
	 * Generate a color based on the value.
	 */
	RGB_Color genColor(std::uint32_t val);

	/**
	 * Generate a pixel in the image.
	 */
	RGB_Color genPixel(std::uint32_t x, std::uint32_t y);

	/**
	 * Convert complex coordinates to image coordinates.
	 */
	ImageLoc complex2Image(ComplexLoc loc);

	/**
	 * Convert image coordinates to complex coordinates.
	 */
	ComplexLoc image2Complex(ImageLoc loc);

	/**
	 * Gets the image width.
	 */
	std::uint32_t getImgWidth();

	/**
	 * Gets the image height.
	 */
	std::uint32_t getImgHeight();

	/**
	 * Gets the plane width.
	 */
	double getPlaneWidth();

	/**
	 * Gets the plane height.
	 */
	double getPlaneHeight();

	/**
	 * Gets the plane's start x.
	 */
	double getPlaneStartX();

	/**
	 * Gets the plane's start y.
	 */
	double getPlaneStartY();

	/**
	 * Is this generating a mandelbrot set?
	 */
	bool isMandelbrot();

	/**
	 * Gets the max number of iterations before a pixel is colored black.
	 */
	std::uint32_t getIterations();

	/**
	 * Gets the constant's real component.
	 */
	double getCReal();

	/**
	 * Gets the constant's imaginary component.
	 */
	double getCImaginary();

private:

	std::uint32_t imgWidth;
	std::uint32_t imgHeight;
	double planeWidth;
	double planeHeight;
	double planeStartX;
	double planeStartY;
	bool mandelbrot;
	std::uint32_t iterations;
	double cReal;
	double cImaginary;
	GeneratorFunction callback;

};

#endif // VALUEGENERATOR_H
