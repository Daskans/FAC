import unittest
import os

from numpy import number
from Parser import ParserCSV

class test_parser(unittest.TestCase):

    def setUp(self) -> None:
        self.parser1 = ParserCSV("data/dataWithoutComment.csv", " ")
        self.parser2 = ParserCSV("data/dataWithComment.csv", " ") 
        
    def tearDown(self) -> None:
        pass

    def test_readColCSVwithoutComment(self):
        self.assertEqual([1.0, 3.0, 5.0, 7.0, 9.0], self.parser1.readColCSV(0))
        self.assertEqual([2.0, 4.0, 6.0, 8.0, 10.0], self.parser1.readColCSV(1))

    def test_readColCSVwithComment(self):
        self.assertEqual([1.0, 3.0, 5.0, 7.0, 9.0], self.parser2.readColCSV(0))
        self.assertEqual([2.0, 4.0, 6.0, 8.0, 10.0], self.parser2.readColCSV(1))

    def test_numberElementInColumnWithoutComment(self):
        numberOfElement = len(self.parser1.readColCSV(0))
        listElement = open(self.parser1.file_path_name).readlines()
        self.assertTrue(numberOfElement == len(listElement))

    """ 
    def test_numberElementInColumnWithComment(self):
        numberOfElement = len(self.parser2.readColCSV(0))
        listElement = open(self.parser2.file_path_name).readlines()
        self.assertTrue(numberOfElement == len(listElement)) 
    """
