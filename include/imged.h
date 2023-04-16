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

void img_drawAALine(ImgCanvas* canvas, int x1, int y1, int x2, int y2, ImgColor color);

void img_destroyCanvas(ImgCanvas* canvas);

#endif
