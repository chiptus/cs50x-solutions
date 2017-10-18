#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = sizeof(BYTE) * 512;

void recover(FILE *image);
int is_jpeg(BYTE* block);
int is_forth_byte(BYTE byte);

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
        fread(block, BLOCK_SIZE, 1, image);
        // printf("%ld\n",ftell(image));
        if (is_jpeg(block))
        {
           printf("block is jpg\n");
        }
        else
        {
        //   printf("block isn't jpg");
        }
        free(block);
    }
}

int is_jpeg(BYTE* block)
{
    return block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && is_forth_byte(block[3]);
}

int is_forth_byte(BYTE byte)
{
   return byte == 0xe0 || byte == 0xe1 || byte == 0xe2 || byte == 0xe3 || byte == 0xe4
    || byte ==  0xe5 || byte == 0xe6 || byte == 0xe7 || byte == 0xe8 || byte == 0xe9
     || byte == 0xea || byte == 0xeb || byte == 0xec || byte == 0xed || byte == 0xee || byte == 0xef;
}