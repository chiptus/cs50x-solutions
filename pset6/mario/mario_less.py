from utils import get_height, create_pyramid


def main():
    """
    Main Method
    """
    print(create_pyramid(get_height(), create_line))


def create_line(line, height):
    """
    Creates one line of the pyramid
    """
    return " " * (height - line) + "#" * (line + 1)


if __name__ == "__main__":
    main()