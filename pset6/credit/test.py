import unittest
import credit


class TestCheckType(unittest.TestCase):
    def test_amex_cards(self):
        self.assertEqual(credit.check_type(378282246310005), 1)
        self.assertEqual(credit.check_type(371449635398431), 1)
        self.assertEqual(credit.check_type(378734493671000), 1)
        
    def test_visa_cards(self):
        self.assertEqual(credit.check_type(4111111111111111), 3)
        self.assertEqual(credit.check_type(4012888888881881), 3)
        self.assertEqual(credit.check_type(4222222222222), 3)
    
    def test_mastercard_cards(self):
        # self.assertEqual(credit.check_type(2223000048400011), 2)
        self.assertEqual(credit.check_type(5105105105105100), 2)
        self.assertEqual(credit.check_type(5555555555554444), 2)    

class TestIsValid(unittest.TestCase):
    def test_valid_cards(self):
        self.assertEqual(credit.is_valid(378282246310005), True)
        self.assertEqual(credit.is_valid(378282246310005), True)
        self.assertEqual(credit.is_valid(371449635398431), True)
        self.assertEqual(credit.is_valid(378734493671000), True)
        self.assertEqual(credit.is_valid(4111111111111111), True)
        self.assertEqual(credit.is_valid(4012888888881881), True)
        self.assertEqual(credit.is_valid(4222222222222), True)
        self.assertEqual(credit.is_valid(2223000048400011), True)
        self.assertEqual(credit.is_valid(2223016768739313), True)
        self.assertEqual(credit.is_valid(5555555555554444), True) 

class TestSumDigits(unittest.TestCase):
    def test(self):
        self.assertEqual(credit.sum_digits(10), 1)
        self.assertEqual(credit.sum_digits(5555555555554444), 76) 


if __name__ == "__main__":
    unittest.main()
