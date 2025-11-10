# -*- coding: utf-8 -*-

import time
import Tictactoe 
from random import randint,choice

def RandomMove(b):
    '''Renvoie un mouvement au hasard sur la liste des mouvements possibles'''
    return choice(b.legal_moves())

def deroulementRandom(b):
    '''Effectue un déroulement aléatoire du jeu de morpion.'''
    print("----------")
    print(b)
    if b.is_game_over():
        res = getresult(b)
        if res == 1:
            print("Victoire de X")
        elif res == -1:
            print("Victoire de O")
        else:
            print("Egalité")
        return
    b.push(RandomMove(b))
    deroulementRandom(b)
    b.pop()


def getresult(b):
    '''Fonction qui évalue la victoire (ou non) en tant que X. Renvoie 1 pour victoire, 0 pour 
       égalité et -1 pour défaite. '''
    if b.result() == b._X:
        return 1
    elif b.result() == b._O:
        return -1
    else:
        return 0

games = {"number of games":0, "win":0, "loss":0, "tie":0}
winning_strat = 0

def nb_games(b):
    if b.is_game_over():
        res = getresult(b)
        if res == 1:
            games["win"]+=1
        elif res == -1:
            games["loss"]+=1
        else:
            games["tie"]+=1
        games["number of games"]+=1
        print()
        return
    for m in b.legal_moves():
        b.push(m)
        nb_games(b)
        b.pop()
    
def nb_noeuds(b):
    if b.is_game_over():
        return 1
    n = 1
    for m in b.legal_moves():
        b.push(m)
        n+=nb_noeuds(b)
        b.pop()
    return n

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

def MaxMin(board : Tictactoe.Board):
    if board.is_game_over():
        return getresult(board)
    best = -999999
    for successor in board.legal_moves():
        board.push(successor)
        best = max(best, MinMax(board))
        board.pop()
        if (best == 1):
            return best
    return best

def MinMax(board : Tictactoe.Board):
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


def choose_best_move(board : Tictactoe.Board):
    best = -999999
    best_move = None
    
    for move in board.legal_moves():
        board.push(move)
        score = MinMax(board)
        board.pop()
    
        if score > best:
            best = score
            best_move = move
    
    return best_move

board = Tictactoe.Board()
print(MaxMin(board))



### Deroulement d'une partie aléatoire
# deroulementRandom(board)

# print(games)
# nb_games(board)
# print(games)

# print(nb_noeuds(board))


print("Apres le match, chaque coup est défait (grâce aux pop()): on retrouve le plateau de départ :")
print(board)

