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

def exhaustiveSearch(depth):
    return

def evalue(board : chess.Board):
    values = {'.':0, 'P':1, 'N':3, 'B':3, 'R':5, 'Q':9, 'K':200}
    score = 0
    for place, piece in board.piece_map().items():
        
        place //= 8
        piece = piece.symbol()
        val = values[piece.upper()]
        
        if (piece == piece.upper()):
            score += val
        else:
            score -= val
        if (piece == 'P'):
            score += (1 + place) * 0.05
        elif (piece == 'p'):
            score -= (8 - place) * 0.05
    return score

def MaxMin(board : chess.Board, maxDepth, blanc = True):
    if board.is_game_over():
        if board.result() == "1-0":
            return 400 if blanc else -400
        elif board.result() == "0-1":
            return -400 if blanc else 400
        else:
            return 0

    if maxDepth == 0:
        return evalue(board) if blanc else -evalue(board)
    
    best = -999999
    
    for successor in board.generate_legal_moves():
        board.push(successor)
        best = max(best, MinMax(board, maxDepth - 1, blanc))
        board.pop()
    return best

def MinMax(board : chess.Board, maxDepth, blanc = True):
    if board.is_game_over():
        if board.result == "1-0":
            return 400 if blanc else -400
        elif board.result == "0-1":
            return -400 if blanc else 400
        else:
            return 0

    if maxDepth == 0:
        return evalue(board) if blanc else -evalue(board)
    
    worst = 999999
    
    for successor in board.generate_legal_moves():
        board.push(successor)
        worst = min(worst, MaxMin(board, maxDepth - 1, blanc))
        board.pop()
    return worst

def ABMaxMin(board : chess.Board, maxDepth, blanc = True, alpha, beta):
    if board.is_game_over():
        if board.result() == "1-0":
            return 400 if blanc else -400
        elif board.result() == "0-1":
            return -400 if blanc else 400
        else:
            return 0

    if maxDepth == 0:
        return evalue(board) if blanc else -evalue(board)
    
    alpha = -999999
    
    for successor in board.generate_legal_moves():
        board.push(successor)
        alpha = max(alpha, ABMinMax(board, maxDepth - 1, blanc))
        board.pop()
        if alpha >= beta:
            continue
    return alpha

def ABMinMax(board : chess.Board, maxDepth, blanc = True, alpha, beta):
    if board.is_game_over():
        if board.result == "1-0":
            return 400 if blanc else -400
        elif board.result == "0-1":
            return -400 if blanc else 400
        else:
            return 0

    if maxDepth == 0:
        return evalue(board) if blanc else -evalue(board)
    
    beta = 999999
    
    for successor in board.generate_legal_moves():
        board.push(successor)
        beta = min(beta, ABMaxMin(board, maxDepth - 1, blanc))
        board.pop()
        if alpha >= beta:
            continue
    return beta

def bestMoves(board : chess.Board, maxDepth, blanc = True):
    best = -999999
    allPossibleMoves = []
    
    for move in board.generate_legal_moves():
        
        board.push(move)
        moveScore = MaxMin(board, maxDepth - 1, blanc)
        
        if (moveScore > best):
            best = moveScore
            allPossibleMoves = [move]
        elif (moveScore == best):
            allPossibleMoves.append(move)
        board.pop()
    return choice(allPossibleMoves)

def MiniMaxVSRandom(board : chess.Board, maxDepth, blanc = True):
    print(board)
    move = bestMoves(board, maxDepth, blanc)
    print("player 1 MiniMax plays ", move)
    board.push(move)
    if board.is_game_over():
        print("Resultat : ", board.result())
        return
    move = randomMove(board)
    print("player 2 random plays ", move)
    board.push(move)
    if board.is_game_over():
        print("Resultat : ", board.result())
        return
    MiniMaxVSRandom(board, maxDepth, blanc)
    board.pop()
    board.pop()

board = chess.Board()
# deroulementRandom(board)
MiniMaxVSRandom(board, 3)

