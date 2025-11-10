# -*- coding: utf-8 -*-
import time
import chess
from random import randint, choice

def randomMove(b):
    '''Renvoie un mouvement au hasard sur la liste des mouvements possibles. Pour avoir un choix au hasard, il faut
    construire explicitement tous les mouvements. Or, generate_legal_moves() nous donne un itérateur.'''
    return choice([m for m in b.generate_legal_moves()])

def deroulementRandom(b):
    '''Déroulement d'une partie d'échecs au hasard des coups possibles. Cela va donner presque exclusivement
    des parties très longues et sans gagnant. Cela illustre cependant comment on peut jouer avec la librairie
    très simplement.'''
    print("----------")
    print(b)
    if b.is_game_over():
        print("Resultat : ", b.result())
        return
    b.push(randomMove(b))
    deroulementRandom(b)
    b.pop()


def evalue(player : str, board : Tictactoe.Board):
    winner = board.result()
    if winner == player:
        return 100
    elif winner != None:
        return -100
    elif board.is_game_over():
        return 0
    
    score = 0
    # for line in board._alignments:
    #     symbols = [board._board[x][y] for (x,y) in line]
    #     if board._O not in symbols:
    #         score += symbols.count(board._X)
    #     if board._X not in symbols:
    #         score -= symbols.count(board._O)

    # if player == board._O:
    #     score -= score

    return score

def MaxMin(board : chess.Board):
    if board.is_game_over():
        return evalue(1, board)
    best = -999999
    for successor in board.legal_moves():
        board.push(successor)
        best = max(best, MinMax(board))
        board.pop()
        if (best == 1):
            return best
    return best

def MinMax(board : chess.Board):
    if board.is_game_over():
        return getresult(board)
    worst = 999999
    for successor in board.legal_moves():
        board.push(successor)
        worst = min(worst, MaxMin(board))
        board.pop()
        if (worst == -1):
            return worst
    return worst

board = chess.Board()
deroulementRandom(board)

