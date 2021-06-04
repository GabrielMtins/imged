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

void img_savePPM(ImgCanvas* canvas, const char* filename){
	if(canvas == NULL) return;

	FILE* file = NULL;

	if(filename == NULL){
		file = stdout;
	}
	else{
		file = fopen(filename, "wb");
	}

	/* set up header
	 * P6 indicates that the file is PPM raw */
	fprintf(file, "P6\n");
	fprintf(file, "%i %i\n", canvas->width, canvas->height);
	fprintf(file, "255\n");

	/* we write the raw data to the file */
	for(int j = 0; j < canvas->height; j++){
		for(int i = 0; i < canvas->width; i++){
			ImgColor color = img_getPixelColor(canvas, i, j);
			fwrite(&color.r, 1, 1, file);
			fwrite(&color.g, 1, 1, file);
			fwrite(&color.b, 1, 1, file);
		}
	}

	if(file != stdout){
		fclose(file);
	}
}
