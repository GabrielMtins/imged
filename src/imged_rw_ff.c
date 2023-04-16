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

ImgCanvas* img_loadFF(const char* filename){
	FILE* file = NULL;

	if(filename == NULL){
		file = stdin;
	}
	else{
		file = fopen(filename, "rb");
		if(file == NULL) return NULL;
	}


	char magic_word[9] = "";

	fread(magic_word, 8, 1, file);
	magic_word[8] = '\0';

	if(strcmp(magic_word, "farbfeld")){
		if(file != stdin) fclose(file);
		return NULL;
	}

	uint32_t width, height;

	uint8_t bit_width[4];
	uint8_t bit_height[4];

	fread(bit_width, 1, 4, file);
	fread(bit_height, 1, 4, file);

	width = (bit_width[0]<<24) + (bit_width[1]<<16) + (bit_width[2]<<8) + (bit_width[3]);

	height = (bit_height[0]<<24) + (bit_height[1]<<16) + (bit_height[2]<<8) + (bit_height[3]);

	uint32_t buffer_size = width * height * 8;
	uint8_t* buffer = malloc(buffer_size);

	fread(buffer, buffer_size, 1, file);

	ImgCanvas* canvas = img_createCanvas(width, height);
	
	for(uint32_t j = 0; j < height; j++){
		for(uint32_t i = 0; i < width; i++){
			int offset = 8*(i + j * width);

			ImgColor color = {
				buffer[offset + 0],
				buffer[offset + 2],
				buffer[offset + 4],
				buffer[offset + 6]
			};

			img_putPixel(canvas, i, j, color);
		}
	}

	free(buffer);

	return canvas;
}

void img_saveFF(ImgCanvas* canvas, const char* filename){
	if(canvas == NULL) return;

	FILE* file = NULL;

	if(filename == NULL){
		file = stdout;
	}
	else{
		file = fopen(filename, "wb");
	}

	uint8_t* buffer = malloc(canvas->width * canvas->height * 8);

	for(int i = 0; i < canvas->width; i++){
		for(int j = 0; j < canvas->height; j++){
			ImgColor color = img_getPixelColor(canvas, i, j);

			/* eight bytes per pixel */
			buffer[8*(i + j * canvas->width) + 0] = color.r;
			buffer[8*(i + j * canvas->width) + 1] = 255;
			buffer[8*(i + j * canvas->width) + 2] = color.g;
			buffer[8*(i + j * canvas->width) + 3] = 255;
			buffer[8*(i + j * canvas->width) + 4] = color.b;
			buffer[8*(i + j * canvas->width) + 5] = 255;
			buffer[8*(i + j * canvas->width) + 6] = color.a;
			buffer[8*(i + j * canvas->width) + 7] = 255;
		}
	}

	uint8_t width[] = {
		255 & (canvas->width>>24),
		255 & (canvas->width>>16),
		255 & (canvas->width>>8),
		255 & canvas->width,
	};

	uint8_t height[] = {
		255 & (canvas->height>>24),
		255 & (canvas->height>>16),
		255 & (canvas->height>>8),
		255 & canvas->height,
	};

	fwrite("farbfeld", 8, 1, file);
	fwrite(width, 4, 1, file);
	fwrite(height, 4, 1, file);
	fwrite(buffer, 8 * canvas->width * canvas->height, 1, file);
	
	free(buffer);

	if(file != stdout){
		fclose(file);
	}
}
