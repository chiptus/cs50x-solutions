from cs50 import get_float

coin_types = [25, 10, 5, 1]


def main():
    """
    Main function
    """
    cash = get_input()
    print(calc_amount_of_coins(cash))


def get_input():
    """
    Handle getting input and validating that it's a positive float
    """
    ans = -1
    while ans < 0:
        ans = get_float("Change owed: ")
    return ans


def calc_amount_of_coins(cash):
    """
    Calculates amount of coins needed to return `cash`
    """
    cents = int(cash * 100)
    coins = 0
    for t in coin_types:
        # Add how much coins of this type is needed
        coins = coins + (cents // t)
        # remove the coins from cents
        cents = cents % t
    return coins


if __name__ == "__main__":
    main()
