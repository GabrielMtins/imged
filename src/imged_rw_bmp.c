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

#define HEADER_SIZE 54
#define BPP_OFFSET 0x1C
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define COLORS_USED 0x2E
#define DATA_OFFSET 0x0A
#define SIGNATURE_OFFSET 0x00
#define FILESIZE_OFFSET 0x04
#define SIZE_OFFSET 0x0E

static uint32_t read_4bytesLE(uint8_t* buffer, uint32_t offset);
static uint16_t read_2bytesLE(uint8_t* buffer, uint32_t offset);

static void write_4bytesLE(uint8_t* buffer, uint32_t offset, uint32_t value);
static void write_2bytesLE(uint8_t* buffer, uint32_t offset, uint16_t value);

static uint32_t read_4bytesLE(uint8_t* buffer, uint32_t offset){
	return buffer[offset] + (buffer[offset + 1] << 8) + 
		(buffer[offset + 2] << 16) + (buffer[offset + 3] << 24);
}

static uint16_t read_2bytesLE(uint8_t* buffer, uint32_t offset){
	return buffer[offset] + (buffer[offset + 1] << 8);
}

static void write_4bytesLE(uint8_t* buffer, uint32_t offset, uint32_t value){
	buffer[offset + 0] = value & 255;
	buffer[offset + 1] = (value >> 8) & 255;
	buffer[offset + 2] = (value >> 16) & 255;
	buffer[offset + 3] = (value >> 24) & 255;
}

static void write_2bytesLE(uint8_t* buffer, uint32_t offset, uint16_t value){
	buffer[offset + 0] = value & 255;
	buffer[offset + 1] = (value >> 8) & 255;
}

ImgCanvas* img_loadBMP(const char* filename){
	FILE* file = NULL;

	if(filename == NULL){
		file = stdin;
	}
	else{
		file = fopen(filename, "rb");
		if(file == NULL) return NULL;
	}

	uint8_t header[HEADER_SIZE];

	fread(header, HEADER_SIZE, 1, file);

	/* gets information from the header */
	uint32_t width = read_4bytesLE(header, WIDTH_OFFSET);
	uint32_t height = read_4bytesLE(header, HEIGHT_OFFSET);
	uint16_t bpp = read_2bytesLE(header, BPP_OFFSET); 
	/* this tests if we are dealing with a rgb image */
	if(bpp != 24){
		if(file != stdin) fclose(file);
		return NULL;
	}

	ImgCanvas* canvas = img_createCanvas(width, height);

	for(uint32_t j = 0; j < height; j++){
		int new_width = width * 3;

		/* each line in a bmp file is multiple of 4, so we need to
		 * count with that */

		if((width*3) % 4 != 0){
			new_width = (int) ((width*3) / 4 + 1) * 4;
		}

		/* read a line */
		uint8_t buffer[new_width];
		fread(buffer, new_width, 1, file);

		for(uint32_t i = 0; i < width; i++){

			/* bmp files stores in BGR instead of RGB */
			ImgColor color = {
				buffer[i*3 + 2],
				buffer[i*3 + 1],
				buffer[i*3 + 0],
				255
			};

			img_putPixel(canvas, i, j, color);
		}
	}

	if(file != stdin) fclose(file);
	return canvas;
}

void img_saveBMP(ImgCanvas* canvas, const char* filename){
	if(canvas == NULL) return;

	FILE* file = NULL;

	if(filename == NULL){
		file = stdout;
	}
	else{
		file = fopen(filename, "wb");
	}

	uint8_t header[HEADER_SIZE];
	for(int i = 0; i < HEADER_SIZE; i++) header[i] = 0;

	/* write informations to header file */
	write_2bytesLE(header, SIGNATURE_OFFSET, 0x4D42);
	write_4bytesLE(header, DATA_OFFSET, HEADER_SIZE);
	write_4bytesLE(header, SIZE_OFFSET, 40);
	write_4bytesLE(header, WIDTH_OFFSET, canvas->width);
	write_4bytesLE(header, HEIGHT_OFFSET, canvas->height);
	write_2bytesLE(header, BPP_OFFSET, 24);

	int real_width = canvas->width * 3;

	/* each width on a bmp file needs to be a multiple of 4
	 * so we need to account to that */
	if((canvas->width*3) % 4 != 0){
		real_width = (int) (canvas->width*3 / 4 + 1) * 4;
	}

	/* set up pixel data */
	int pixel_array_size = real_width * canvas->height;
	uint8_t* pixel_array = malloc(pixel_array_size);
	for(int i = 0; i < pixel_array_size; i++) pixel_array[i] = 0;

	/* write up pixel data. BMP files doesn't have alpha, so we don't use it */
	for(int j = 0; j < canvas->height; j++){
		for(int i = 0; i < canvas->width; i++){
			ImgColor color = img_getPixelColor(canvas, i, canvas->height - j - 1);
			pixel_array[j*real_width + 3*i + 0] = color.b;
			pixel_array[j*real_width + 3*i + 1] = color.g;
			pixel_array[j*real_width + 3*i + 2] = color.r;
		}
	}

	/* write the size of the file to the header */
	write_4bytesLE(header, FILESIZE_OFFSET, HEADER_SIZE + pixel_array_size);
	fwrite(header, HEADER_SIZE, 1, file);
	fwrite(pixel_array, pixel_array_size, 1, file);

	free(pixel_array);
	if(file != stdout) fclose(file);
}
