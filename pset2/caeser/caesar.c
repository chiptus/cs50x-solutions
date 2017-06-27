#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>

string print_encryption(string text, int key);
char encrypt_char(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Number of supplied arguments is illegal\n");
        return 1;
    }
    printf("plaintext:");
    string plaintext = get_string();
    printf("ciphertext:%s\n", print_encryption(plaintext, atoi(argv[1])));
    return 0;
}

string print_encryption(string text, int key)
{
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        text[i] = encrypt_char(text[i], key);
    }
    return text;
}

char encrypt_char(char c, int key)
{
    if (!isalpha(c))
    {
        return c;
    }
    int base = isupper(c) ? 'A' : 'a';
    int letter = (c % base + key) % 26;
    return base + letter;
}