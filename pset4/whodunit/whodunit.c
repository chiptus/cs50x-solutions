#include <cs50.h>
#include <stdio.h>

#include "bmp.h"

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: whodunit input-file output-file\n");
        return 1;
    }
    
    string input_file_name = argv[1];
    string output_file_name = argv[2];
    
    FILE* input_file = fopen(input_file_name, "r");
    
    if (input_file == NULL) 
    {
        fprintf(stderr, "ERROR: %s isn't available for reading \n", input_file_name);
        return 2;
    }
    
    FILE* output_file = fopen(output_file_name, "w");
    
    if (output_file == NULL) 
    {
        fclose(input_file);
        fprintf(stderr, "ERROR: %s isn't available for writing \n", output_file_name);
        return 3;
    }
    
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input_file);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input_file);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(output_file);
        fclose(input_file);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output_file);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output_file);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, input_file);
            
            //check for reds
            if (triple.rgbtBlue == 0x00 && triple.rgbtRed == 0xff && triple.rgbtGreen == 0x00)
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
            }
            //check for not full or empty reds
            else if (triple.rgbtRed != 0x00 && triple.rgbtRed != 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
            }
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, output_file);
        }

        // skip over padding, if any
        fseek(input_file, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, output_file);
        }
    }

    // close infile
    fclose(input_file);

    // close outfile
    fclose(output_file);

    return 0;
}