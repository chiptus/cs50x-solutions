#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = sizeof(BYTE) * 512;

void recover(FILE *image);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "use: resize image\n");
        return 1;
    }
    
    char * image = argv[1];
    
    FILE *file = fopen(image, "r");
    
    if (file == NULL)
    {
        fprintf(stderr, "Can't open %s.\n", image);
        return 2;
    }
    
    recover(file);
    fclose(file);
    return 0;
}


void recover(FILE *image)
{
    
    while (feof(image) == 0)
    {
        BYTE* block = malloc(BLOCK_SIZE);
        fread(&block, BLOCK_SIZE, 1, image);
        // if (is_jpeg(block))
        // {
        //     //start a new file
        // }
        // else
        // {
        //   // add to old file
        // }
        free(block);
    }
}