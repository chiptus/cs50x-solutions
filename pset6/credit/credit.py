from cs50 import get_int

types = ["INVALID", "AMEX", "MASTERCARD", "VISA"]
types_map = dict(zip(types, range(len(types))))

def main():
    number = get_int("Number: ")
    possible_type = check_type(number)
    if possible_type != types_map["INVALID"] and not is_valid(number):
        possible_type = types_map["INVALID"]
    print(types[possible_type])
    
def check_type(number):
    if 34e13 <= number <= 35e13 or 37e13 <= number < 38e13:
        return types_map["AMEX"]
    if 51e14 <= number <= 56e14:
        return types_map["MASTERCARD"]
    if 4e12 <= number < 5e12 or 4e15 <= number < 5e15:
        return types_map["VISA"]
    return types_map["INVALID"]
    
def is_valid(n):
    i = 0
    sum = 0
    while n > 0:
        n, d = divmod(n, 10)
        if i % 2 == 0:
            sum = sum + d
        else:
            sum = sum + sum_digits(2 * d)
        i = i + 1
    return sum % 10 == 0

def sum_digits(n):
    sum = 0
    while n > 0:
        n, r = divmod(n, 10)
        sum = sum + r
    return sum

    
if __name__ == "__main__":
    main()