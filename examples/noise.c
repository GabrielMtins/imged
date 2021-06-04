/*
	Copyright (C) 2021  Gabriel Martins
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* imged library */
#include <imged/imged.h>
#include <imged/imged_rw.h>

/* compile this program with:
 * $ gcc noise.c -limged -o main
 * Then run it with:
 * $ ./main
*/

/* this program generates a random noise */

#define CANVAS_WIDTH 200
#define CANVAS_HEIGHT 200

int main(){
	/* since we are using rand(), we need to set srand */
	srand(time(NULL));

	/* create canvas */
	ImgCanvas* canvas = img_createCanvas(CANVAS_WIDTH, CANVAS_HEIGHT);

	/* create colors black and white */
	ImgColor white = {255, 255, 255, 255};
	ImgColor black = {0, 0, 0, 255};

	/* now we pass by each pixel and determine randomly what color the pixel
	 * will be */
	for(int i = 0; i < CANVAS_WIDTH; i++){
		for(int j = 0; j < CANVAS_HEIGHT; j++){
			int isWhite = rand() % 2;
			ImgColor current_color;

			/* sets the current color to be black or white depending on the
			 * random value */
			if(isWhite == 1)
				current_color = white;
			else
				current_color = black;

			img_putPixel(canvas, i, j, current_color);
		}
	}

	/* save as bmp */
	img_saveBMP(canvas, "noise.bmp");

	/* frees the memory */
	img_destroyCanvas(canvas);

	return 0;
}
