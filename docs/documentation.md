# Documentation

## Structures

### ImgCanvas

```
typedef struct{
	uint8_t* buffer;
	int width, height;
} ImgCanvas;
```

A canvas that is used to draw images.

### ImgColor

```
typedef struct{
	uint8_t r, g, b, a;
} ImgColor;
```

A color structure. It has 4 variables: r, g, b, a, which represents the red,
green, blue and alpha channel. This variables can vary from 0 to 255.

## General Functions

### img\_createCanvas

`ImgCanvas* img_createCanvas(int width, int height);`

Create a canvas with given width and height.

### img\_clear

`void img_clear(ImgCanvas* canvas, ImgColor color);`

Paints a canvas with given color.

### img\_getPixelColor

`ImgColor img_getPixelColor(ImgCanvas* canvas, int x, int y);`

Returns the color of a pixel at the given x and y coordinates.

### img\_putPixel

`void img_putPixel(ImgCanvas* canvas, int x, int y, ImgColor color);`

Puts a pixel with given color at given x and y coordinates.

### img\_drawLine

`void img_drawLine(ImgCanvas* canvas, int x1, int y1, int x2, int y2, ImgColor color);`

Draws a line between two given pixels with a given color.
The line starts at the coordinates (x1, y2) and ends at the coordinates (x2, y2)


### img\_destroyCanvas

`void img_destroyCanvas(ImgCanvas* canvas);`

Frees a memory from a given canvas.

## Loading functions

### img\_loadFF

`ImgCanvas* img_loadFF(const char* filename);`

Loads a farbfeld image file to a canvas and returns it. If filename is NULL,
then it will read from standard input.

### img\_loadBMP

`ImgCanvas* img_loadBMP(const char* filename);`

Loads a bmp image to a canvas and returns it. The image needs to be 24bpp.
If filename is NULL, then it will read from standard input.


### img\_saveFF

`void img_saveFF(ImgCanvas* canvas, const char* filename);`

Saves the image of the canvas to a farbfeld file. If filename is NULL, then
it will save to standard output.

### img\_saveBMP

`void img_saveBMP(ImgCanvas* canvas, const char* filename);`

Saves the image of the canvas to a BMP file. If filename is NULL, then
it will save to standard output.

### img\_savePPM

`void img_savePPM(ImgCanvas* canvas, const char* filename);`

Saves the image of the canvas to a PPM file. If filename is NULL, then
it will save to standard output.
