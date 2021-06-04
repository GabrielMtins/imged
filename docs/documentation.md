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
