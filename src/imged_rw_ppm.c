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
