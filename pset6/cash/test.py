import unittest


import cash


class TestCalcAmountOfCoins(unittest.TestCase):
    def test(self):
        self.assertEqual(cash.calc_amount_of_coins(41), 4)
        
if __name__=="__main__":
    unittest.main()