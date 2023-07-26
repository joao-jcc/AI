from tkinter import E
import unittest
from tictactoe import *
from icecream import ic
ic.disable()

X, O, EMPTY = 'X', 'O', None
state_0 = [
          [X, X, X],
          [O, O, EMPTY],
          [EMPTY, EMPTY, EMPTY]
          ]

state_1 = [
          [X, X, EMPTY],
          [O, O, O],
          [EMPTY, EMPTY, EMPTY]
          ]

state_2 = [
          [X, X, EMPTY],
          [O, O, EMPTY],
          [EMPTY, EMPTY, EMPTY]
          ]

state_3 = [
    [X, O, X],
    [X, O, O],
    [O, X, X]
]

class TestTTT(unittest.TestCase):
     
    def test_player(self):
        expected = O
        self.assertEqual(player(state_0), expected)
    
    def test_actions(self):
        expected = [(1, 2), (2, 0), (2, 1), (2, 2)]
        ic(actions(state_0))
        self.assertEqual(actions(state_0), expected)
    
    def test_result(self):
        action = (2, 0)
        expected = [
            [X, X, X],
            [O, O, EMPTY],
            [O, EMPTY, EMPTY]
        ]
        self.assertEqual(result(state_0, action), expected)
    
    def test_winner(self):
        expected_0, expected_1, expected_2 = X, O, None
        self.assertEqual(winner(state_0), expected_0)
        self.assertEqual(winner(state_1), expected_1)
        self.assertEqual(winner(state_2), expected_2)

    def test_terminal(self):
        expected_0, expected_1, expected_2, expected_3 = True, True, False, True
        self.assertEqual(terminal(state_0), expected_0)
        self.assertEqual(terminal(state_1), expected_1)
        self.assertEqual(terminal(state_2), expected_2)
        self.assertEqual(terminal(state_3), expected_3)
    
    def test_utility(self):
        expected_0, expected_1, expected_2, expected_3 = 1, -1, 0, 0
        self.assertEqual(utility(state_0), expected_0)
        self.assertEqual(utility(state_1), expected_1)
        self.assertEqual(utility(state_2), expected_2)
        self.assertEqual(utility(state_3), expected_3)
    

unittest.main()
