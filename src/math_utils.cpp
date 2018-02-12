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

#include <cmath>

#include "math_utils.h"

double mod2(double value, double min, double max) {
	double size = max - min;

	while (value < min) {
		value += size;
	}
	while (value >= max) {
		value -= size;
	}

	return value;
}

RGB_Color fromHSB(double hue, double saturation, double brightness) {
	uint32_t r = 0, g = 0, b = 0;
	if (saturation == 0) {
		r = g = b = (uint32_t)(brightness * 255.0 + 0.5);
	} else {
		double h = (hue - std::floor(hue)) * 6.0;
		double f = h - std::floor(h);
		double p = brightness * (1.0 - saturation);
		double q = brightness * (1.0 - saturation * f);
		double t = brightness * (1.0 - (saturation * (1.0 - f)));
		switch ((uint32_t) h) {
		case 0:
			r = (uint32_t)(brightness * 255.0 + 0.5);
			g = (uint32_t)(t * 255.0 + 0.5);
			b = (uint32_t)(p * 255.0 + 0.5);
			break;
		case 1:
			r = (uint32_t)(q * 255.0 + 0.5);
			g = (uint32_t)(brightness * 255.0 + 0.5);
			b = (uint32_t)(p * 255.0 + 0.5);
			break;
		case 2:
			r = (uint32_t)(p * 255.0 + 0.5);
			g = (uint32_t)(brightness * 255.0 + 0.5);
			b = (uint32_t)(t * 255.0 + 0.5);
			break;
		case 3:
			r = (uint32_t)(p * 255.0 + 0.5);
			g = (uint32_t)(q * 255.0 + 0.5);
			b = (uint32_t)(brightness * 255.0 + 0.5);
			break;
		case 4:
			r = (uint32_t)(t * 255.0 + 0.5);
			g = (uint32_t)(p * 255.0 + 0.5);
			b = (uint32_t)(brightness * 255.0 + 0.5);
			break;
		case 5:
			r = (uint32_t)(brightness * 255.0 + 0.5);
			g = (uint32_t)(p * 255.0 + 0.5);
			b = (uint32_t)(q * 255.0 + 0.5);
			break;
		}
	}
	RGB_Color data;
	data.r = (uint8_t) r;
	data.g = (uint8_t) g;
	data.b = (uint8_t) b;
	return data;
}

