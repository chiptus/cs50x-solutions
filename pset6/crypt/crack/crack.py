from sys import argv
from crypt import crypt
from itertools import permutations
from string import ascii_letters


def main():
    """Main Function"""
    if len(argv) != 2:
        print("Number of supplied arguments is illegal, there should be only one argument")
        exit(1)
    hash = argv[1]
    print(decrypt_pass(hash))


def decrypt_pass(hash):
    """
    Try to decrypt `hash` using brute force
    """
    max_length = 4

    for i in range(1, max_length + 1):
        # run on all options of length `i`
        options = permutations(ascii_letters, i)
        for option in options:
            # check if option is the origin of `hash`
            word = "".join(option)
            if crypt(word, hash) == hash:
                return word


if __name__ == "__main__":
    main()
