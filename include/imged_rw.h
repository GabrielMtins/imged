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

#ifndef IMGED_RW_H

#include "imged.h"

ImgCanvas* img_loadFF(const char* filename);

ImgCanvas* img_loadBMP(const char* filename);

void img_saveFF(ImgCanvas* canvas, const char* filename);

void img_saveBMP(ImgCanvas* canvas, const char* filename);

void img_savePPM(ImgCanvas* canvas, const char* filename);

void img_savePNG(ImgCanvas* canvas, const char* filename);

#endif
