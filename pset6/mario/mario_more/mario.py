from cs50 import get_int


def main():
    """
    Main Method
    """
    height = get_height()
    if not height:
        return
    print(create_pyramid(height, create_line))


def create_line(line, height):
    """
    Creates one line of the pyramid
    """
    stars = "#" * line
    return " " * (height - line) + stars + "  " + stars


def get_height():
    """
    Gets `height` input from the user
    """
    while True:
        val = get_int("Height: ")
        if 0 <= val <= 23:
            return val


def create_pyramid(height, line_gen):
    """
    Creates the pyramid with `height`
    """
    return "\n".join([line_gen(i + 1, height) for i in range(height)])


if __name__ == "__main__":
    main()