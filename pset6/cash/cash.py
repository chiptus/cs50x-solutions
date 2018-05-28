from cs50 import get_float

coin_types = [25, 10, 5, 1]

def main():
    """
    Main function
    """
    cash = get_input()
    print(calc_amount_of_coins(cash))
    

def get_input():
    ans = -1
    while ans < 0:
        ans = get_float("Change owed: ")
    return ans


def calc_amount_of_coins(cash):
    cehts = int(cash*100)
    coins = 0
    for t in coin_types:
        coins = coins + (cents//t)

if __name__ == "__main__":
    main()