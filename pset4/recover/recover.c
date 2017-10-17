#include <stdlib.h>
#include <stdio.h>

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
    
}