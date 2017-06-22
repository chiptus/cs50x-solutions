
What it means to resize a bmp by a factor of n
if n=1 it's only to copy
if n>1 it's to enlarge
0<n<1 it's to shrink it

assume n>1
each pixel become n*n pixels
that means that if a file is I pixels width and J pixels height
its enlargment would be nI pixels wide and nJ pixels high

## Padding
`(4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4`


Let's think what happens to its headers:

## BITMAPINFOHEADER:
```
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
```

### List of changed keys:
- `biWidth` - has we said should be `n*biWidth`
- `biHeight` - `n*biWidth`

## BITMAPFILEHEADER

```
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
```

### List of changed keys:
- `bfSize` - 


