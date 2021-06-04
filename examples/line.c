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
