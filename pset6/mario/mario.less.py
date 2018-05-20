from cs50 import get_int

def main():
    print_pyramid(get_int("Height:"))
    
def print_pyramid(height):
    for i in range(height):
        print(create_line(i, height))
        
def create_line(line, height):
    return " " * (height - line) + "#" * (line + 1)

main()