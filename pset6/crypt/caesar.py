from sys import argv
from cs50 import get_string


def main():
    """Main Method"""
    if len(argv) != 2:
        print("Number of supplied arguments is illegal\n")
        exit(1)
    is_number, key = is_number_string(argv[1])
    if not is_number:
        print("Key is not a number\n")
        exit(1)
    plaintext = get_string("plaintext: ")
    ciphertext = encrypt(plaintext, key)
    print("ciphertext: {ciphertext}".format(ciphertext=ciphertext))


def is_number_string(s):
    """
    Checks if provided string `s` is a number
    """
    try:
        n = int(s)
        return True, n
    except ValueError:
        return False, 0


def encrypt(text, key):
    """
    Encrypts a text by the caeser algorithm
    """
    return "".join(map(lambda c: encrypt_char(c, key), text))


def encrypt_char(c, key):
    """
    Encrypts a single char by the caeser algorithm
    """
    # ignoring non alphabetical characters
    if not c.isalpha():
        return c
    # set the base of the alhpabet (upper or lowercase)
    base = ord("A") if c.isupper() else ord("a")
    letter_code = (ord(c) % base + key) % 26
    return chr(base + letter_code)


if __name__ == "__main__":
    main()
