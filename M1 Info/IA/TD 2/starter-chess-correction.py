# -*- coding: utf-8 -*-
import time
from types import TracebackType
from typing import NoReturn
import chess
from random import randint, choice

def randomMove(b):
    '''Renvoie un mouvement au hasard sur la liste des mouvements possibles. Pour avoir un choix au hasard, il faut
    construire explicitement tous les mouvements. Or, generate_legal_moves() nous donne un itÃ©rateur.'''
    return choice([m for m in b.generate_legal_moves()])

def deroulementRandom(b):
    '''DÃ©roulement d'une partie d'Ã©checs au hasard des coups possibles. Cela va donner presque exclusivement
    des parties trÃ¨s longues et sans gagnant. Cela illustre cependant comment on peut jouer avec la librairie
    trÃ¨s simplement.'''
    print("----------")
    print(b)
    if b.is_game_over():
        print("Resultat : ", b.result())
        return
    b.push(randomMove(b))
    deroulementRandom(b)
    b.pop()

nbNoeuds = 0
def exploreToutHorizon(b, maxdepth=3, compter=False, limittime=None):
    '''Explore toutes les parties jusquÃ  une profondeur maxDepth
        et compte (si compte est Ã  True)
    '''
    global nbNoeuds
    if compter:
        nbNoeuds += 1
    if limittime is not None and time.time() > limittime:
        raise TimeoutError    
    #print('----------')
    if b.is_game_over() or maxdepth==0:
        return
        #print(b)
    for m in b.generate_legal_moves():
        b.push(m)
        if limittime is not None:
            exploreToutHorizon(b, maxdepth-1,  compter, limittime = limittime)# - time.time())
        else:
            exploreToutHorizon(b, maxdepth-1,  compter)
        b.pop()

def evalBoard(b):
    valpieces = {'.':0,'P':1,'R':5,'N':3,'B':3,'Q':9,'K':200}
    score = 0
    for k, p in b.piece_map().items():
        #print('(k, p)=(',k, p,')')
        line = k >> 3 # k // 8 -> line in [0..7]
        symb = p.symbol() # 'r', 'R', 'b', ...
        #print(line,symb,symb.upper(),symb==symb.upper(), valpieces[symb.upper()], score)
        v = valpieces[symb.upper()] # Valeur de la piece
        if symb == symb.upper(): # C'est pour BLANC
            score += v
        else:
            score -= v
        if symb == "P":
            score += (1+line) * 0.05
        elif symb == "p":
            score -= (8-line) * 0.05
    return score

#MiniMax
def maxMin(b, maxdepth, compter=False, blanc=True):
    global  nbNoeuds
    if compter:
        nbNoeuds += 1
    if b.is_game_over():
        if b.result() == '1-0':
            return 400 if blanc else -400
        elif b.result() == '0-1':
            return -400 if blanc else 400
        else:
            return 0
    if maxdepth==0:
        return evalBoard(b) if blanc else -evalBoard(b)
    meilleur = -1000
    for m in b.generate_legal_moves():
        b.push(m)
        meilleur = max(meilleur, minMax(b, maxdepth-1, compter, blanc))
        b.pop()
    return meilleur

def minMax(b, maxdepth, compter=False, blanc=True):
    global  nbNoeuds
    if compter:
        nbNoeuds += 1
    if b.is_game_over():
        if b.result() == '1-0':
            return 400 if blanc else -400
        elif b.result() == '0-1':
            return -400 if blanc else 400
        else:
            return 0
    if maxdepth==0:
        return evalBoard(b) if blanc else -evalBoard(b)
    pire = 1000
    for m in b.generate_legal_moves():
        b.push(m)
        pire = min(pire, maxMin(b, maxdepth-1, compter, blanc))
        b.pop()
    return pire

def IAMiniMax(b, maxdepth, compter=False, blanc=True):
    global nbNoeuds
    if compter:
        nbNoeuds += 1
    meilleur = -1000
    meilleurcoup = None
    listemeilleurscoups = [] 
    for m in b.generate_legal_moves():
        b.push(m)
        val = minMax(b, maxdepth-1, compter, blanc)
        if val > meilleur or meilleurcoup is None:
            meilleur = val
            meilleurcoup = m
            listemeilleurscoups = [m]
        elif val == meilleur:
            listemeilleurscoups.append(m)
        b.pop()
    return choice(listemeilleurscoups)

#Alpha-Beta
def maxValue(b, alpha, beta, maxdepth, compter=False, limittime=None): 
    #Je ne mets pas ici la variable blanc car, on ne fera pas jouer l'alpha-beta
    #contre lui mÃªme
    global  nbNoeuds
    if compter:
        nbNoeuds += 1
    if limittime is not None and time.time() > limittime:
        raise TimeoutError
    if b.is_game_over():
        if b.result() == '1-0':
            return 400 
        elif b.result() == '0-1':
            return -400 
        else:
            return 0
    if maxdepth==0:
        return evalBoard(b) 
    for m in b.generate_legal_moves():
        b.push(m)
        try:
            val = minValue(b, alpha, beta, maxdepth-1, compter, limittime)
        except TimeoutError:
            b.pop()
            raise TimeoutError
        b.pop()
        if val > alpha:
            alpha = val
        if alpha >= beta:
            return beta
    return alpha

def minValue(b, alpha, beta, maxdepth, compter=False, limittime=None): 
    #Je ne mets pas ici la variable blanc car, on ne fera pas jouer l'alpha-beta
    #contre lui mÃªme
    global  nbNoeuds
    if compter:
        nbNoeuds += 1
    if limittime is not None and time.time() > limittime:
        raise TimeoutError    
    if b.is_game_over():
        if b.result() == '1-0':
            return 400 
        elif b.result() == '0-1':
            return -400 
        else:
            return 0
    if maxdepth==0:
        return evalBoard(b) 
    for m in b.generate_legal_moves():
        b.push(m)
        try:
            val = maxValue(b, alpha, beta, maxdepth-1, compter, limittime)
        except TimeoutError:
            b.pop()
            raise TimeoutError
        b.pop()
        if val < beta:
            beta = val
        if alpha >= beta:
            return alpha
    return beta

def IAAlphaBeta(b, maxdepth=3, compter=False, limittime=None):
    #Je ne mets pas ici la variable blanc car, on ne fera pas jouer l'alpha-beta
    #contre lui mÃªme
    global nbNoeuds
    if compter:
        nbNoeuds += 1 
    alpha = -1000
    meilleurcoup = None
    for m in b.generate_legal_moves():
        b.push(m)
        try:
            val = minValue(b, alpha, 1000, maxdepth-1, compter, limittime)
        except TimeoutError:
            b.pop()
            raise(TimeoutError)
        if val > alpha or meilleurcoup is None:
            alpha = val
            meilleurcoup = m
        b.pop()
    return meilleurcoup

#Iterative deepening:

def IDAlphaBeta(b, compter=False, limittime=10):
    depth = 1
    res = None
    t = 0
    timemax = time.time()+limittime
    while True:
        try:
            t =  time.process_time() 
            #limittime = limittime - t
            res = IAAlphaBeta(b, maxdepth=depth, compter=compter, limittime=timemax)
            t =  time.process_time() - t 
            #print('depth: ', depth, 'res: ', res, ' in ', t, '(s)')
        except TimeoutError:
            return res
        depth += 1
        t = time.process_time()

#board = chess.Board()
#deroulementRandom(board)

#Jusqu'oÃ¹ on peut aller en 30 s: 
# board = chess.Board()
# print(time.process_time())
# maxdepth=1
# while(True):
#     print('current depth: ', maxdepth)
#     try:
#        exploreToutHorizon(board, maxdepth, limittime=30+time.time())
#     except TimeoutError:
#         board.pop()
#         print('Depth: ', maxdepth)
#         break
#     maxdepth += 1
#Le maximum que l'on peut atteindre en 30 secondes est maxdepth=5



#Compter le nombre de neoeuds :
# for depth in range(1, 5):
#    nbNoeuds = 0
#    exploreToutHorizon(board, maxdepth=depth, compter=True, limittime=50)
#    print('Profondeur: ', depth, 'Nombre de noeuds: ', nbNoeuds)
    
#print(evalBoard(board))

#IAMiniMax : test
#print(IAMiniMax(board, maxdepth=3, compter=True))
#print('Nombre de noeuds : ', nbNoeuds)

#Un premier match : IAMiniMax vs JoueurAlearoire:
#board = chess.Board()
#while not board.is_game_over():
#    print(board)
#    coup = IAMiniMax(board,maxdepth=3)
#    print('IAMiniMax joue : ', coup)
#    board.push(coup)
#    if board.is_game_over():
#        break
#    coup = randomMove(board)
#    print('Joueur AlÃ©a joue : ', coup)
#    board.push(coup)
#    if board.is_game_over():
#        break
#print('Resultat : ', board.result())  

# Un deuxiÃ¨me match : IAMiniMax 1 contre IAMiniMax 3:
#board = chess.Board()
# while not board.is_game_over():
#     print(board)
#     coup = IAMiniMax(board,maxdepth=1)
#     print('IAMiniMax 1 joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
#     coup = IAMiniMax(board,maxdepth=3, blanc=False)
#     print('IAMiniMax 3 joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
# print('Resultat : ', board.result())    

# Le GRAND match : IAMiniMax 3 contre IAAlphaBeta 3:
# board = chess.Board()
# while not board.is_game_over():
#     print(board)
#     coup = IAMiniMax(board,maxdepth=3)
#     print('IAMiniMax 3 joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
#     coup = IAAlphaBeta(board,maxdepth=3)
#     print('IAAlphaBeta 3 joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
# print('Resultat : ', board.result())    

# Un autre match : IAMiniMax 3 contre IDAlphaBeta 3:
# board = chess.Board()
# while not board.is_game_over():
#     print(board)
#     coup = IDAlphaBeta(board,limittime=10)
#     print('IDAlphaBeta joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
#     coup = IAMiniMax(board,maxdepth=3, blanc=False)
#     print('IAMiniMax 3 joue : ', coup)
#     board.push(coup)
#     if board.is_game_over():
#         break
# print('Resultat : ', board.result())  
# print(board)  

# Un match contre un joueur
# board = chess.Board()
# while not board.is_game_over():
#     print('-----------------------------')
#     print(board)
#     coup = IAAlphaBeta(board,maxdepth=3)
#     print('IAAlphaBeta joue : ', coup)
#     board.push(coup)
#     #print(board)
#     if board.is_game_over():
#         break
#     # print('quelle est la case selectionnee ?')
#     # case = input()
#     # print("Ou voulez-vous l'envoyer ?")
#     # move = input()
#     # try :
#     #     move = chess.Move(int(case), int(move))
#     #     print(move)
#     # except:
#     #     print("Move interdit")   
#     # board.push(move)
#     move = input("Entrez un coup : ")
#     move = chess.Move.from_uci(str(move))
#     board.push(move)    
#     #print(board)
#     if board.is_game_over():
#         break
# print('Resultat : ', board.result())  
# print(board)  