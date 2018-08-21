import unittest

from helpers import distances, Operation


def print_matrix(m):
    for row in m:
        for col in row:
            print(col[0], end="\t")
        print()


class TestDistance(unittest.TestCase):
    def test_matrix_size_should_be_lenAplus1XlenBplus1(self):
        s1 = "sdfsdf"
        s2 = "asdrwe"
        matrix = distances(s1, s2)
        self.assertEqual(len(matrix), len(s1) + 1)
        self.assertEqual(len(matrix[len(s1)]), len(s2) + 1)

    def test_matrix_edit_distance_between_yale_harward_should_be_6(self):
        matrix = distances("Yale", "Harward")
        distance = matrix[4][7][0]
        self.assertEqual(distance, 6)

    def test_matrix_of_harward_and_yale(self):
        expected = [
            [(0, None),                 (1, Operation.INSERTED),    (2, Operation.INSERTED),    (3, Operation.INSERTED),
             (4, Operation.INSERTED),    (5, Operation.INSERTED), (6, Operation.INSERTED),   (7, Operation.INSERTED)],
            [(1, Operation.DELETED),    (1, Operation.SUBSTITUTED), (2, Operation.SUBSTITUTED), (3, Operation.SUBSTITUTED),
             (4, ),    (5, Operation.INSERTED), (6, Operation.INSERTED),   (7, Operation.INSERTED)],
            [(2, Operation.DELETED),    (2, Operation.SUBSTITUTED), (1, Operation.SUBSTITUTED), (2, Operation.SUBSTITUTED),
             (3, Operation.INSERTED),    (4, Operation.INSERTED), (5, Operation.INSERTED),   (6, Operation.INSERTED)],
            [(3, Operation.DELETED),    (3, Operation.SUBSTITUTED), (2, Operation.DELETED),
             (2, ),    (3,),    (4, ), (5, ),   (6, Operation.INSERTED)],
            [(4, Operation.DELETED),    (4, Operation.SUBSTITUTED), (3, Operation.DELETED),
             (3, ),    (3, ),    (4, ), (5, ),   (6, Operation.INSERTED)]
        ]
        calculated = distances("Yale", "Harvard")
        self.assertStepsAreEqual(calculated, expected)

    def assertStepsAreEqual(self, calc, expected):
        self.assertEqual(len(calc), len(expected))
        self.assertEqual(len(calc[len(calc) - 1]),
                         len(expected[len(expected) - 1]))
        for i in range(len(calc)):
            for j in range(len(calc[i])):
                self.assertEqual(calc[i][j][0], expected[i][j][0],
                                 f"({i},{j}): ({calc[i][j]},{expected[i][j]})")


unittest.main()
