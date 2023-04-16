/*
	Copyright (C) 2021-2023 Gabriel Martins
  
	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
  
	1. The origin of this software must not be misrepresented; you must not
   	claim that you wrote the original software. If you use this software
   	in a product, an acknowledgment in the product documentation would be
   	appreciated but is not required. 
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
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

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);

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
	png_destroy_write_struct(&png, &info);

	if(file != stdout) fclose(file);
}
