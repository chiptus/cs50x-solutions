import unittest
import unittest.mock
import io
from random import randint

import mario_less


# class TestMarioLessPrintPyramid(unittest.TestCase):
#     @unittest.mock.patch('sys.stdout', new_callable=io.StringIO)
#     def assert_stdout(self, height, expected, mock_stdout):
#         mario_less.print_pyramid(height)
#         self.assertEqual(expected, mock_stdout.getvalue())

#     def test_print_pyramid_with_1_height(self):
#         self.assert_stdout(1, "##\n")

#     def test_print_pyramid_with_0_height(self):
#         self.assert_stdout(0, "")

#     def test_print_pyramid_with_2_height(self):
#         self.assert_stdout(2, " ##\n###\n")

def create_pyramid(height):
    return mario_less.create_pyramid(height, mario_less.create_line)


class TestMarioLessPrintPyramid(unittest.TestCase):
    def test_print_pyramid_with_1_height(self):
        self.assertEqual(create_pyramid(1), "##")

    def test_print_pyramid_with_0_height(self):
        self.assertEqual(create_pyramid(0), "")

    def test_print_pyramid_with_2_height(self):
        self.assertEqual(create_pyramid(2), " ##\n###")


class TestMarioLessCreateLine(unittest.TestCase):
    def test_when_line_equals_height_return_full_line(self):
        self.assertEqual("#######", mario_less.create_line(6, 6))

    def test_regular_input(self):
        self.assertEqual("    ###", mario_less.create_line(2, 6))

    def test_return_string_length_height_plus_one(self):
        height = 10
        line = randint(0, 10)
        self.assertEqual(len(mario_less.create_line(line, height)), height + 1)


if __name__ == '__main__':
    unittest.main()
