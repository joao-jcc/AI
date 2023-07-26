"""
Tic Tac Toe Player
"""

from copy import deepcopy
import math
from icecream import ic

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    counter = sum([row.count(EMPTY) for row in board])
    if counter%2==0 and counter!=1:
        return O
    return X


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    available_actions = []
    for i in range(3):
        available_actions += [(i, j) for j in range(3) if board[i][j] == EMPTY]
        
    return available_actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    i, j= action
    new_board = deepcopy(board)
    new_board[i][j] = player(board)
    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    aux_winner = lambda line: X if line.count(X) == 3 else (O if line.count(O) == 3 else None)
    for line in board:
        if aux_winner(line):
            return aux_winner(line)
    
    for j in range(3):
        cols = [rows[j] for rows in board]
        if aux_winner(cols):
            return aux_winner(cols)
    
    main_diagonal = [board[0][0], board[1][1], board[2][2]]
    second_diagonal = [board[2][0], board[1][1], board[0][2]]
    if aux_winner(main_diagonal):
        return aux_winner(main_diagonal)
    
    elif aux_winner(second_diagonal):
        return aux_winner(second_diagonal)
    
    return None
    


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) is not None:
        return True
    
    elif sum([row.count(EMPTY) for row in board]) == 0:
        return True
    
    return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    

    return 0


def minimax(board, status='PARENT'):
    """
    Returns the optimal action for the current player on the board.
    """
    if status == "PARENT" and terminal(board):
        return None
    
    elif status == "CHILD" and terminal(board):
        return utility(board)

    scores, moves = [], []
    for action in actions(board):
        new_board = result(board, action)
        scores.append(minimax(new_board, status="CHILD"))
        if status == "PARENT":
            moves.append(action)

    if player(board) == X and status == "CHILD":
        return max(scores)
    
    elif player(board) == O and status == "CHILD":
        return min(scores)
    
    elif player(board) == X and status == "PARENT":
        max_score = max(scores)
        index_max = scores.index(max_score)
        return moves[index_max]
    
    elif player(board) == O and status == "PARENT":
        min_score = min(scores)
        index_min = scores.index(min_score)
        return moves[index_min]
    
    



