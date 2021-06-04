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
