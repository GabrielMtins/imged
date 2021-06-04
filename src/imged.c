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

#include "imged.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OUT_OF_BOUNDS(canvas, x, y) \
	(x < 0 || y < 0 || x >= canvas->width || y >= canvas->height)

ImgCanvas* img_createCanvas(int width, int height){
	ImgCanvas* canvas = malloc(sizeof(ImgCanvas));

	canvas->width = width;
	canvas->height = height;
	canvas->buffer = malloc(width * height * 4);

	return canvas;
}

void img_clear(ImgCanvas* canvas, ImgColor color){
	if(canvas == NULL) return;

	for(int i = 0; i < canvas->width; i++){
		for(int j = 0; j < canvas->height; j++){
			img_putPixel(canvas, i, j, color);
		}
	}
}

ImgColor img_getPixelColor(ImgCanvas* canvas, int x, int y){
	ImgColor ret_color = {0, 0, 0, 0};

	if(canvas == NULL) return ret_color;
	if(OUT_OF_BOUNDS(canvas, x, y)) return ret_color;

	ret_color.r = canvas->buffer[4*(x + y * canvas->width) + 0];
	ret_color.g = canvas->buffer[4*(x + y * canvas->width) + 1];
	ret_color.b = canvas->buffer[4*(x + y * canvas->width) + 2];
	ret_color.a = canvas->buffer[4*(x + y * canvas->width) + 3];

	return ret_color;
}

void img_putPixel(ImgCanvas* canvas, int x, int y, ImgColor color){
	if(canvas == NULL) return;
	if(OUT_OF_BOUNDS(canvas, x, y)) return;

	canvas->buffer[4*(x + y * canvas->width) + 0] = color.r;
	canvas->buffer[4*(x + y * canvas->width) + 1] = color.g;
	canvas->buffer[4*(x + y * canvas->width) + 2] = color.b;
	canvas->buffer[4*(x + y * canvas->width) + 3] = color.a;
}

void img_drawLine(ImgCanvas* canvas, int x1, int y1, int x2, int y2, ImgColor color){
	if(canvas == NULL) return;
	double dx, dy, steps, start_x, start_y;

	dx = (x2-x1);
	dy = (y2-y1);
	steps = 0;

	if(fabs(dx) > fabs(dy)) steps = fabs(dx);
	else steps = fabs(dy);

	start_x = x1, start_y = y1;

	for(int i = 0; i < steps; i++){
		start_x += (double)dx/steps;
		start_y += (double)dy/steps;
		img_putPixel(canvas, start_x, start_y, color);
	}
}

void img_destroyCanvas(ImgCanvas* canvas){
	if(canvas == NULL) return;

	free(canvas->buffer);
	free(canvas);
}
