/*
	Copyright (C) 2021  Gabriel Martins

	This file is part of imged

	imged is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	imged is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
    
	You should have received a copy of the GNU Lesser General Public License
	along with imged.  If not, see <https://www.gnu.org/licenses/>
*/

#include "imged_rw.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <png.h>

void img_savePNG(ImgCanvas* canvas, const char* filename){
	if(canvas == NULL) return;

	FILE* file = NULL;

	if(filename == NULL){
		file = stdout;
	}
	else{
		file = fopen(filename, "wb");
	}

	png_struct* png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_info* info = png_create_info_struct(png);

	if(png == NULL || info == NULL){
		if(file != stdout) fclose(file);
		return;
	}

	png_init_io(png, file);
	png_set_IHDR(png, info, canvas->width, canvas->height,
			16, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE,
			PNG_FILTER_TYPE_BASE);
	png_write_info(png, info);

	for(int j = 0; j < canvas->height; j++){
		uint16_t buffer[4*canvas->width];
		for(int i = 0; i < canvas->width; i++){
			ImgColor color = img_getPixelColor(canvas, i, j);
			buffer[4*i + 0] = color.r;
			buffer[4*i + 1] = color.g;
			buffer[4*i + 2] = color.b;
			buffer[4*i + 3] = color.a;
		}
		png_write_row(png, (uint8_t*) buffer);
	}

	png_write_end(png, NULL);
	png_destroy_write_struct(&png, NULL);
}
