from cs50 import get_int


def main():
    """
    Main Method
    """
    print_pyramid(get_height())


def print_pyramid(height):
    """
    Prints the pyramid with `height`
    """
    for i in range(1, height + 1):
        print(create_line(i, height), end="\n" if i < height else "")


def create_line(line, height):
    """
    Prints one line of the pyramid
    """
    if height < line:
        return ""
    return " " * (height - line) + "#" * (line + 1)


def get_height():
    """
    Gets `height` input from the user
    """
    while True:
        val = get_int("Height: ")
        if 0 <= val <= 23:
            return val


if __name__ == "__main__":
    main()