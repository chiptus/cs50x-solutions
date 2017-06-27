#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

int calculate_padding(int biWidth);
BITMAPFILEHEADER resize_bf(BITMAPFILEHEADER bf, BITMAPINFOHEADER new_bi);
BITMAPINFOHEADER resize_bi(BITMAPINFOHEADER inbi, int n);
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "use: resize n input-file output-file\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "first argument must be a positive integer less then or equal to 100\n");
        return 1;
    }
    
    char *input_filename = argv[2];
    FILE *input_file = fopen(input_filename, "r");
    
    if (input_file == NULL)
    {
        fprintf(stderr, "Can't open %s.\n", input_filename);
        return 1;
    }
    
    
    char *output_filename = argv[3];
    
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        fprintf(stderr, "Can't create %s.\n", output_filename);
        return 1;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inbf;
    fread(&inbf, sizeof(BITMAPFILEHEADER), 1, input_file);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inbi;
    fread(&inbi, sizeof(BITMAPINFOHEADER), 1, input_file);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inbf.bfType != 0x4d42 || inbf.bfOffBits != 54 || inbi.biSize != 40 || 
        inbi.biBitCount != 24 || inbi.biCompression != 0)
    {
        fclose(output_file);
        fclose(input_file);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    BITMAPINFOHEADER outbi = resize_bi(inbi, n);
    BITMAPFILEHEADER outbf = resize_bf(inbf, outbi);
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, output_file);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, output_file);

    // determine padding for scanlines
    int original_padding = calculate_padding(inbi.biWidth);
    int new_padding = calculate_padding(outbi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inbi.biHeight); i < biHeight; i++)
    {
        // repeat this line n times
        for (int k = 0; k < n; k++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < inbi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, input_file);
                
                //repeat this pixel n times
                for (int l = 0; l < n; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, output_file);
                }
            }

            long int offset = (inbi.biWidth * sizeof(RGBTRIPLE));
            fseek(input_file, -offset, SEEK_CUR);
            
            for (int m = 0; m < new_padding; m++)
            {
                fputc(0x00, output_file);
            }
        }

        // skip over padding, if any
        fseek(input_file, inbi.biWidth * sizeof(RGBTRIPLE) + original_padding, SEEK_CUR);

    }

    // close infile
    fclose(input_file);

    // close outfile
    fclose(output_file);

    // success
    return 0;
}


int calculate_padding(int biWidth)
{
    return (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
}

BITMAPFILEHEADER resize_bf(BITMAPFILEHEADER bf, BITMAPINFOHEADER new_bi)
{
    BITMAPFILEHEADER new_header;
    new_header.bfType = bf.bfType;
    new_header.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + new_bi.biSizeImage;
    new_header.bfReserved1 = bf.bfReserved1;
    new_header.bfReserved2 = bf.bfReserved2;
    new_header.bfOffBits = bf.bfOffBits;
    return new_header;
}

BITMAPINFOHEADER resize_bi(BITMAPINFOHEADER inbi, int n)
{
    BITMAPINFOHEADER new_header;
    new_header.biSize = inbi.biSize; 
    new_header.biWidth = n * inbi.biWidth; 
    new_header.biHeight = n * inbi.biHeight; 
    new_header.biPlanes = inbi.biPlanes; 
    new_header.biBitCount = inbi.biBitCount; 
    new_header.biCompression = inbi.biCompression; 
    new_header.biSizeImage = (new_header.biWidth * sizeof(RGBTRIPLE) + calculate_padding(new_header.biWidth)) * abs(new_header.biHeight); 
    new_header.biXPelsPerMeter = inbi.biXPelsPerMeter; 
    new_header.biYPelsPerMeter = inbi.biYPelsPerMeter; 
    new_header.biClrUsed = inbi.biClrUsed; 
    new_header.biClrImportant = inbi.biClrImportant; 
    return new_header;
}