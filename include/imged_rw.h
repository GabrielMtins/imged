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

#ifndef IMGED_RW_H

#include "imged.h"

ImgCanvas* img_loadFF(const char* filename);

ImgCanvas* img_loadBMP(const char* filename);

void img_saveFF(ImgCanvas* canvas, const char* filename);

void img_saveBMP(ImgCanvas* canvas, const char* filename);

void img_savePPM(ImgCanvas* canvas, const char* filename);

void img_savePNG(ImgCanvas* canvas, const char* filename);

#endif
