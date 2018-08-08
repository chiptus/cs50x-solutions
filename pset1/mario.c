#include <stdio.h>
#include <cs50.h>


int get_height(void);
void print_pyramid(int);
void print_line(int line, int height);
void print_empty(int length);
void print_stars(int length);
void repeat_char(char c, int times);

int main(void)
{
    int height = get_height();
    print_pyramid(height);
}

int get_height()
{
    printf("Height: ");
    int ans = get_int();
    while (ans > 23 || ans < 0)
    {
        printf("Retry: ");
        ans = get_int();
    }
    return ans;
}

void print_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        print_line(i, height);
    }
}

void print_line(int line, int height)
{
    print_empty(height - line);
    print_stars(line + 1);
    printf("\n");
}

void print_empty(int length)
{
    repeat_char(' ', length);
}

void print_stars(int length)
{
    repeat_char('#', length);
}

void repeat_char(char c, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%c", c);
    }
}