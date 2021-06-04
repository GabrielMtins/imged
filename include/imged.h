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

#ifndef IMGED_H
#define IMGED_H

#include <stdint.h>

typedef struct{
	uint8_t* buffer;
	int width, height;
} ImgCanvas;

typedef struct{
	uint8_t r, g, b, a;
} ImgColor;

ImgCanvas* img_createCanvas(int width, int height);

void img_clear(ImgCanvas* canvas, ImgColor color);

ImgColor img_getPixelColor(ImgCanvas* canvas, int x, int y);

void img_putPixel(ImgCanvas* canvas, int x, int y, ImgColor color);

void img_drawLine(ImgCanvas* canvas, int x1, int y1, int x2, int y2, ImgColor color);

void img_destroyCanvas(ImgCanvas* canvas);

#endif
