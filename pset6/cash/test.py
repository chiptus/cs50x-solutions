import unittest


import cash


class TestCalcAmountOfCoins(unittest.TestCase):
    def test_input_of_0_41_yields_output_of_4(self):
        self.assertEqual(cash.calc_amount_of_coins(0.41), 4)


    def test_input_of_0_01_yields_output_of_1(self):
        self.assertEqual(cash.calc_amount_of_coins(0.01), 1)

    
    def test_input_of_0_15_yields_output_of_2(self):
        self.assertEqual(cash.calc_amount_of_coins(0.15), 2)


    def test_input_of_1_6_yields_output_of_7(self):
        self.assertEqual(cash.calc_amount_of_coins(1.6), 7)

    def test_input_of_23_yields_output_of_92(self):
        self.assertEqual(cash.calc_amount_of_coins(23), 92)

    def test_input_of_4_2_yields_output_of_18(self):
        self.assertEqual(cash.calc_amount_of_coins(4.2), 18)


if __name__=="__main__":
    unittest.main()