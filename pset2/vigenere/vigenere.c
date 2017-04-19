#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>

bool str_is_only_letters(string text);

string encrypt(string text, string key);
char encrypt_char(char c, char key);
// char* convert_to_key_array(string key, int len);
// string string_to_lower(string s);
// string make_string(int len);
int convert_char_to_key(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Number of supplied arguments is illegal, there should be only one argument\n");
        return 1;
    }
    string key = argv[1];
    if (!str_is_only_letters(key))
    {
        printf("Key contains characters that aren't letters\n");
        return 1;
    }
    //key is only letters
    
    printf("plaintext:");
    string plaintext = get_string();
    
    printf("ciphertext:%s\n", encrypt(plaintext, key));
    return 0;
}

string encrypt(string text, string key)
{
    int n = strlen(text);
    int key_len = strlen(key);
    int key_index  = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = encrypt_char(text[i], convert_char_to_key(key[key_index]));
            key_index = (key_index + 1) % key_len;
        }
        
    }
    return text;
}

char encrypt_char(char c, char key)
{
    if (!isalpha(c))
    {
        return c;
    }
    int base = isupper(c) ? 'A' : 'a';
    int letter = (c % base + key) % 26;
    return base + letter;
}

bool str_is_only_letters(string text)
{
    for (int i=0, n = strlen(text); i<n; i++)
    {
        if (!isalpha(text[i]))
        {
            return false;
        }
    }
    return true;
}

int convert_char_to_key(char c)
{
    char c_low = tolower(c);
    return c_low - 'a';
}

// char* convert_to_key_array(string key, int len)
// {
//     string low_key = string_to_lower(key);
//     string key_arr = make_string(len);
//     // printf("%s", key_arr);
//     int key_len = strlen(key);
//     for (int i=0; i<len; i++)
//     {
//         key_arr[i] = (char)(low_key[i % key_len] - 'a');
//     }
//     return key_arr;
// }

// string string_to_lower(string s)
// {
//     for (int i=0, n=strlen(s); i<n; i++)
//     {
//         s[i] = tolower(s[i]);
//     }
//     return s;
// }

// string make_string(int len)
// {
//     string ans = NULL;
//     return memset(ans, 0, len);
// }