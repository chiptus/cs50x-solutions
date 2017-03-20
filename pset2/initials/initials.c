#import <stdio.h>
#import <cs50.h>
#import <string.h>
#import <ctype.h>

void print_initials(string name);

int main(void)
{
    string name = get_string();
    print_initials(name);
}

void print_initials(string name)
{
    for (int i=0, n=strlen(name); i < n; i++) {
        if ((i == 0 || name[i-1] == ' ') && name[i] != ' ')
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
}

