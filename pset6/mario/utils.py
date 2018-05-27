from cs50 import get_int


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