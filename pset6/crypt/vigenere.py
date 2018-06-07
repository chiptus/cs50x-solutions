from sys import argv
from cs50 import get_string


def main():
    """Main Method"""
    if len(argv) != 2:
        print("Number of supplied arguments is illegal")
        exit(1)
    key = argv[1]
    if not key.isalpha():
        print("Key contains characters that aren't letters")
        exit(1)
    plaintext = get_string("plaintext: ")
    ciphertext = encrypt(plaintext, key)
    print("ciphertext: {ciphertext}".format(ciphertext=ciphertext))


def encrypt(text, key):
    """
    Encrypts a text by the caeser algorithm
    """
    encrypted_text = ""
    keys = [convert_char_to_key(k) for k in key]
    key_index = 0
    for i in range(len(text)):
        current_char = text[i]
        if not current_char.isalpha():
            encrypted_text += current_char
        else:
            encrypted_text += encrypt_char(current_char, keys[key_index])
            key_index = (key_index + 1) % len(key)
    return encrypted_text


def encrypt_char(c, key):
    """
    Encrypts a single char by the caeser algorithm
    """
    # set the base of the alhpabet (upper or lowercase)
    base = ord("A") if c.isupper() else ord("a")
    letter_code = (ord(c) % base + key) % 26
    return chr(base + letter_code)


def convert_char_to_key(key_char):
    c_low = key_char.lower()
    return ord(c_low) - ord('a')


if __name__ == "__main__":
    main()
