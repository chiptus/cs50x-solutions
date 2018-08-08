import unittest
from helpers import unique_lines, unique_sentences, unique_substrings


class TestUniqueLines(unittest.TestCase):
    def test_returns_set(self):
        self.assertIsInstance(unique_lines(""), set)

    def test_returns_one_element_for_a_regular_string(self):
        self.assertEqual(len(unique_lines("hello world")), 1)

    def test_returns_two_elements_with_line_break(self):
        ans = unique_lines("hello\nworld")
        self.assertEqual(len(ans), 2)
        self.assertEqual(ans, set(["hello", "world"]))


class TestUniqueSentences(unittest.TestCase):
    def test_returns_set(self):
        self.assertIsInstance(unique_sentences(""), set)

    def test_returns_one_element_for_a_regular_string(self):
        self.assertEqual(len(unique_sentences("hello world")), 1)

    def test_returns_two_elements_with_line_break(self):
        ans = unique_sentences("hello\nworld. how are you?")
        self.assertEqual(len(ans), 2)
        self.assertEqual(ans, set(["hello\nworld.", "how are you?"]))


class TestUniqueSubstrings(unittest.TestCase):
    def test_returns_set(self):
        self.assertIsInstance(unique_substrings("", 2), set)

    def test(self):
        self.assertEqual(unique_substrings("hello", 1),
                         set(["h", "e", "l", "o"]))


if __name__ == "__main__":
    unittest.main()
