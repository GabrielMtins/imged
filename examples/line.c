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

/* include the library */
#include <imged/imged.h>
#include <imged/imged_rw.h>

/* compile this program with:
 * $ gcc line.c -limged -o main
 * Then run it with:
 * $ ./main
*/

/* this program generates a line that goes across the screen */

#define CANVAS_WIDTH 1280
#define CANVAS_HEIGHT 720

int main(){
	/* create a canvas */
	ImgCanvas* canvas = img_createCanvas(CANVAS_WIDTH, CANVAS_HEIGHT);

	/* sets the background color to be black */
	ImgColor background = {0, 0, 0, 255};
	/* creates a red color */
	ImgColor red = {255, 0, 0, 255};

	/* cleans the canvas with background color */
	img_clear(canvas, background);

	/* draws a line between the two extremes of the canvas */
	img_drawLine(canvas, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, red);

	/* saves the image as bmp with the name being "canvas.bmp" */
	img_saveBMP(canvas, "canvas.bmp");

	/* frees the memory used by the canvas */
	img_destroyCanvas(canvas);

	return 0;
}
