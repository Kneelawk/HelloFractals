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

#include "pixel_utils.h"

void setColor(std::uint8_t **pixels, std::size_t x, std::size_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    pixels[y][x * 4] = r;
    pixels[y][x * 4 + 1] = g;
    pixels[y][x * 4 + 2] = b;
    pixels[y][x * 4 + 3] = a;
}

void setCrosshair(std::uint8_t **pixels, std::size_t width, std::size_t height, std::size_t x, std::size_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    for (int i = 0; i < x; i++) {
        setColor(pixels, i, y, r, g, b, a);
    }
    for (int i = 0; i < y; i++) {
        setColor(pixels, x, i, r, g, b, a);
    }
    for (int i = width - 1; i > x; i--) {
        setColor(pixels, i, y, r, g, b, a);
    }
    for (int i = height - 1; i > y; i--) {
        setColor(pixels, x, i, r, g, b, a);
    }
}

