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

#include <cstdio>
#include <iostream>
#include <png.h>

#include "image_writer.h"

using namespace std;

int writePNG(uint8_t **pixels, size_t width, size_t height, const char *filename) {
	FILE *file = fopen(filename, "wb");
	if (!file) {
		cerr << "Failed to open " << filename << endl;
		return IMG_WRITER_FILE_OPEN_FAILED;
	}
	
	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png) {
		cerr << "Failed to create PNG struct" << endl;
		fclose(file);
		return IMG_WRITER_PNG_STRUCT_FAILED;
	}
	
	png_infop info = png_create_info_struct(png);
	if (!info) {
		cerr << "Failed to create PNG info struct" << endl;
		fclose(file);
		png_destroy_write_struct(&png, nullptr);
		return IMG_WRITER_PNG_INFO_STRUCT_FAILED;
	}
	
	if (setjmp(png_jmpbuf(png))) {
		cerr << "PNG error" << endl;
		fclose(file);
		png_destroy_write_struct(&png, &info);
		return IMG_WRITER_PNG_ERROR;
	}
	
	png_init_io(png, file);
	
	png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_ADAM7, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	
	png_write_info(png, info);
	
	png_write_image(png, pixels);
	
	png_write_end(png, info);
	
	png_destroy_write_struct(&png, &info);
	
	fclose(file);
	
	return IMG_WRITER_SUCCESS;
}
