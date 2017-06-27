#define _XOPEN_SOURCE
#include <unistd.h>
#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>

string get_salt(string hash);
string decrypt(string hash, string salt);
string brute(string hash, string salt, string test, int rec);
string copy_string(string str, int len);
/*
input: hashed password
out: 
    -print cracked password + \n
    - return 0

check:
- one and only one argument
- if more or less than one -> return 1


assume
- password has been hashed with c's DES-based 'crypt' function
- password is no longer than 4 chars
- password is made of only alphabetical characters (upper and/or lower)
*/

const int MAX_NUMBER_OF_CHAR = 4;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Number of supplied arguments is illegal, there should be only one argument\n");
        return 1;
    }
    string hash = argv[1];

    if (strlen(hash) < 2 )
    {
        printf("Number of characters in hash is illegal\n");
        return 1;
    }

    string salt = get_salt(hash);
    string pass = decrypt(hash, salt);
    if (strlen(pass) == 0)
    {
        printf("failed :(");
        return 1;
    }
    printf("%s\n", pass);
    return 0;
}

string get_salt(string hash)
{
    //make place for a string with length 2
    string salt = malloc(3 * sizeof(char));
    //copy the salt part of hash into salt
    strncpy(salt, hash, 2);
    //add terminating char
    salt[2] = '\0';
    //remove salt from hash
    hash = hash + 2;
    // printf("hash: %s\n", hash);
    return salt;
}

string decrypt(string hash, string salt)
{
    string test = "";
    
    string ans = brute(hash, salt, test, 0);
    
    return ans;
}

string brute(string hash, string salt, string test_org, int rec)
{   
    //check if test string is the right passowrd - otherwise continue to look
    if (strcmp(crypt(test_org, salt),hash) == 0){
        return test_org;
    }
    //if this is already the max number of characters then we should fail
    if (rec == MAX_NUMBER_OF_CHAR)
    {
        // printf("brute failed at start %s, %i\n", test_org, rec);
        return "";
    }
    //make copy of test - to handle case of need to use lower case
    string test = copy_string(test_org, rec);
    for (int i0 = 'A', j0 = 'a'; i0<='Z' && j0 <='z'; i0++, j0++)
    {
        test[rec] = i0;
        string test_upper = brute(hash, salt, test, rec + 1);
        if (strlen(test_upper) > 0)
        {
            return test_upper;
        }
        test[rec] = j0;
        string test_lower = brute(hash, salt, test, rec + 1);
        if (strlen(test_lower) > 0)
        {
            return test_lower;
        }
        
    }
    // printf("brute failed at end %s, %i, %s\n", test_org, rec, hash);
    return "";
}

//copy the string with additional character
string copy_string(string str, int len)
{
    string new_str = malloc((len + 1) * sizeof(char));
    strcpy(new_str, str);
    return new_str;
}