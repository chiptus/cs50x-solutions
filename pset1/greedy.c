#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_input(void);
int calc_amount_of_coins(int input);
int calc_amount_of_coin(int input, int coin_value);

int main(void)
{
    int input = get_input();
    printf("%i\n", calc_amount_of_coins(input));
}

int get_input()
{
    printf("O hai! How much change is owed?\n");
    float ans = get_float();
    while (ans < 0)
    {
        printf("How much change is owed?\n");
        ans = get_float();
    }
    return (int)(round(ans * 100));
}

int calc_amount_of_coins(int input)
{
    float coins[4] = {25, 10, 5, 1};
    int coe[4];
    int ans = 0;
    int currentCoin = 0;
    while (input > 0)
    {
        int num = calc_amount_of_coin(input, coins[currentCoin]);
        input = input - num * coins[currentCoin];
        coe[currentCoin] = num;
        currentCoin++;
        ans = ans + num;
    }
    return ans;
}

int calc_amount_of_coin(int input, int coin_value)
{
    int ans = 0;
    while (input - coin_value >= 0)
    {
        ans = ans + 1;
        input = input - coin_value;
    }
    return ans;
}