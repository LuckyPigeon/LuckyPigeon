# -*- coding: utf-8 -*-
import unittest
from cal import appleAndPen

class TestCal(unittest.TestCase):
    '''Test cal.py'''
    def test_addstr(self):
        '''Test method addstr(str1, str2)'''
        self.assertEqual('bananapen', appleAndPen('apple', 'pen'))

if __name__ == '__main__':
    unittest.main()
