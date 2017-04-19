#define _XOPEN_SOURCE
#include <unistd.h>
#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Number of supplied arguments is illegal, there should be only two argument\n");
        return 1;
    }
    printf("hash of %s with salt %s: %s\n", argv[1], argv[2], crypt(argv[1], argv[2]));
}