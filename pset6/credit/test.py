import unittest
import credit


class TestCheckType(unittest.TestCase):
    def test(self):
        self.assertEqual(credit.check_type(378282246310005), 1)

class TestIsValid(unittest.TestCase):
    def test(self):
        self.assertEqual(credit.is_valid(378282246310005), True)
        
class TestSumDigits(unittest.TestCase):
    def test(self):
        self.assertEqual(credit.sum_digits(10), 1)

class TestIsValidNoStr(unittest.TestCase):
    def test(self):
        self.assertEqual(credit.is_valid_no_str(378282246310005), True)
    
if __name__=="__main__":
    unittest.main()