//https://cs50.stackexchange.com/questions/9956/hacker4-resize-cant-resize-when-factor-is-a-decimal-number?newreg=f106bd3f8cde414487831f2787ce3371

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bmp.h"


typedef struct FILEDATA
{
   FILE* file;
   BITMAPINFOHEADER bi;
   BITMAPFILEHEADER bf;
   int padding;
} FILEDATA;


void upscale(FILE* input_file, FILE* output_file, float n, BITMAPFILEHEADER inbf, BITMAPINFOHEADER inbi);
// void downscale(FILE* input_file, FILE* output_file, float n, BITMAPFILEHEADER inbf, BITMAPINFOHEADER inbi);

int calculate_padding(int biWidth);
BITMAPFILEHEADER resize_bf(BITMAPFILEHEADER bf, BITMAPINFOHEADER new_bi);
BITMAPINFOHEADER resize_bi(BITMAPINFOHEADER inbi, float n);
int resize(FILE* input_file, FILE* output_file, float n);
FILEDATA create_file_meta( FILE* file,   BITMAPINFOHEADER bi, BITMAPFILEHEADER bf,  int padding);
void process_line(FILEDATA input, FILEDATA output, float n);
void process_pixel(FILE* input_file, FILE* output_file, float n);
void go_to_begining(FILEDATA file);
void add_padding(FILEDATA file_meta);
void skip_line(FILEDATA file_meta);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "use: resize n input-file output-file\n");
        return 1;
    }
    
    float n = atof(argv[1]);
    
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "first argument must be a positive float between 0 to 100\n");
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
    
    return resize(input_file, output_file, n);
}


int resize(FILE* input_file, FILE* output_file, float n)
{
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
        return 1;
    }
    
    if (n >= 1)
    {
        upscale(input_file, output_file, n, inbf, inbi);
    } else {
    //    downscale(input_file, output_file, n, inbf, inbi);
    }

    // close infile
    fclose(input_file);

    // close outfile
    fclose(output_file);

    // success
    return 0;
}

void upscale(FILE* input_file, FILE* output_file, float n, BITMAPFILEHEADER inbf, BITMAPINFOHEADER inbi) {
    
    
    BITMAPINFOHEADER outbi = resize_bi(inbi, n);
    BITMAPFILEHEADER outbf = resize_bf(inbf, outbi);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, output_file);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, output_file);

    float height_ratio = (float)inbi.biHeight / outbi.biHeight;
    float width_ratio = (float)inbi.biWidth / outbi.biWidth;
    

    // determine padding for scanlines
    int original_padding = calculate_padding(inbi.biWidth);
    int new_padding = calculate_padding(outbi.biWidth);

    FILEDATA input = create_file_meta(input_file, inbi, inbf, original_padding);
    FILEDATA output = create_file_meta(output_file, outbi, outbf, new_padding);

    // printf("hratiow: %f\n", height_ratio);
    // printf("wration: %f\n", width_ratio);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(outbi.biHeight); i < biHeight; i++)
    {
        //calc the line to copy
        int scanline_index = floor(i * height_ratio);
        // printf("newline %i, scanline %i\n", i, scanline_index);
        // go to that line
        int line_location = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + scanline_index * (inbi.biWidth * sizeof(RGBTRIPLE) + original_padding);
        fseek(input.file, line_location, SEEK_SET);
        printf("location of %i is %i, current location: %ld\n", scanline_index, line_location, ftell(input.file));
        
        //copy the line into an array
        RGBTRIPLE* triples = malloc(sizeof(RGBTRIPLE) * inbi.biWidth);
        for (int j = 0; j < inbi.biWidth; j++) {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, input.file);
            triples[j] = triple;
        }
        
        
        for (int j = 0; j < outbi.biWidth; j++) {
            int pixel_index = floor(j * width_ratio);
            // if (pixel_index < 0 || pixel_index > inbi.biWidth) {
            //     fprintf(stderr, "Pixel %i is out of bounds: %i", pixel_index, inbi.biWidth);
            // }
            // printf("newpixel %i, pixel %i\n", j, pixel_index);
            fwrite(&triples[pixel_index], sizeof(RGBTRIPLE), 1, output.file);
        }
        add_padding(output);
        
    }
}

// void downscale(FILE* input_file, FILE* output_file, float n, BITMAPFILEHEADER inbf, BITMAPINFOHEADER inbi) {
    
// }

FILEDATA create_file_meta( FILE* file,   BITMAPINFOHEADER bi, BITMAPFILEHEADER bf,  int padding)
{
    FILEDATA file_meta;
    file_meta.file = file;
    file_meta.bi = bi;
    file_meta.bf = bf;
    file_meta.padding = padding;
    return file_meta;
}

void process_line(FILEDATA input, FILEDATA output, float n)
{
    
    // iterate over pixels in scanline
    for (int j = 0; j < output.bi.biWidth; j++)
    {
        process_pixel(input.file, output.file, n);
    }

    //go to beginning of input file line and to the next line of output
    go_to_begining(input);
    
    add_padding(output);
    
    skip_line(input);
}

void skip_line(FILEDATA file_meta)
{
    // skip over padding, if any
    fseek(file_meta.file, file_meta.bi.biWidth * sizeof(RGBTRIPLE) + file_meta.padding, SEEK_CUR);
}

void add_padding(FILEDATA file_meta)
{
    for (int m = 0; m < file_meta.padding; m++)
    {
        fputc(0x00, file_meta.file);
    }
}

void go_to_begining(FILEDATA file)
{
    //go to beginning of input file line and to the next line of output
    long int offset = (file.bi.biWidth * sizeof(RGBTRIPLE));
    fseek(file.file, -offset, SEEK_CUR);
}

void process_pixel(FILE* input_file, FILE* output_file, float n)
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

BITMAPINFOHEADER resize_bi(BITMAPINFOHEADER inbi, float n)
{
    BITMAPINFOHEADER new_header;
    new_header.biSize = inbi.biSize; 
    new_header.biWidth = floor(n * inbi.biWidth); 
    new_header.biHeight = floor(n * inbi.biHeight); 
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