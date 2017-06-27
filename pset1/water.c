#include <stdio.h>
#include <cs50.h>

int convertMinutesToBottles(int);

int main(void) 
{
    printf("Minutes:");
    int mins = get_int();
    printf("Bottles: %i\n", convertMinutesToBottles(mins));
}

int convertMinutesToBottles(int minutes) 
{
    float gallons_per_minute=1.5;
    int ounces_per_gallon = 128;
    int ounces_per_bottle = 16;
    return (minutes * gallons_per_minute * ounces_per_gallon) / ounces_per_bottle;
}