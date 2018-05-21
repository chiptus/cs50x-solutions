import unittest
import unittest.mock
import io

import mario_less

class TestMarioLess(unittest.TestCase):
    @unittest.mock.patch('sys.stdout', new_callable=io.StringIO)
    def assert_stdout(self, test, expected, mock_stdout):
        test()
        self.assertEqual(expected, mock_stdout.getvalue())
    
    def test_print_pyramid_with_1_height(self):
        self.assert_stdout(lambda : mario_less.print_pyramid(1), "##")
    
    def test_print_pyramid_with_0_height(self):
        self.assert_stdout(lambda: mario_less.print_pyramid(0), "")
    
    
if __name__ == '__main__':
    unittest.main()