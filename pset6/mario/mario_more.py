from utils import get_height


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
        print(create_line(i, height))


def create_line(line, height):
    """
    Creates one line of the pyramid
    """
    if height < line:
        return ""
    s = " " * (height - line) + "#" * (line)
    return s + "  " + s[::-1]


if __name__ == "__main__":
    main()