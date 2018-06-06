import unittest
from caesar import encrypt_char, encrypt


class TestEncryptChar(unittest.TestCase):
    def test_lower_char(self):
        self.assertEqual(encrypt_char('a', 5), 'f')

    def test_upper_char(self):
        self.assertEqual(encrypt_char('G', 4), 'K')

    def test_non_alpha(self):
        self.assertEqual(encrypt_char('5', 10), '5')


class TestEncrypt(unittest.TestCase):
    def test_encrypts_a_as_b_using_key_1(self):
        self.assertEqual(encrypt('a', 1), 'b')

    def test_encrypts_barfoo_as_yxocll_using_23_as_key(self):
        self.assertEqual(encrypt('barfoo', 23), 'yxocll')

    def test_encrypts_BARFOO_as_EDUIRR_using_3_as_key(self):
        self.assertEqual(encrypt('BARFOO', 3), 'EDUIRR')

    def test_encrypts_BaRFoo_as_FeVJss_using_4_as_key(self):
        self.assertEqual(encrypt('BaRFoo', 4), 'FeVJss')

    def test_encrypts_barfoo_as_onesbb_using_65_as_key(self):
        self.assertEqual(encrypt('barfoo', 65), 'onesbb')

    def test_encrypts_world_say_hello_as_iadxp_emk_tqxxa_using_12_as_key(self):
        self.assertEqual(encrypt('world, say hello!', 12), 'iadxp, emk tqxxa!')


if __name__ == "__main__":
    unittest.main()
