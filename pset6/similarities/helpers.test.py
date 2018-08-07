import unittest

from helpers import distances

def print_matrix(m):
    for row in m:
        for col in row:
            print(col[0], end="\t")
        print()

class TestDistance(unittest.TestCase):
    def test_matrix_size_should_be_lenAplus1XlenBplus1(self):
        matrix = distances("hello", "hey")
        self.assertEqual(len(matrix), 6)
        self.assertEqual(len(matrix[5]), 4)
    
    def test_matrix_edit_distance_between_yale_harward_should_be_6(self):
        matrix = distances("Yale", "Harward")
        distance = matrix[4][7][0]
        self.assertEqual(distance, 6)
        
unittest.main()