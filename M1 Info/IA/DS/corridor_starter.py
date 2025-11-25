from corridor import Corridor
from random import choice

def can_move(board, r1, c1, r2, c2):
    """
    Vérifie si on peut se déplacer de (r1,c1) vers (r2,c2) sans mur.
    board : instance de Corridor
    """
    N = board.N
    if not (0 <= r2 < N and 0 <= c2 < N):
        return False
    # murs horizontaux
    if r2 == r1 + 1 and (r1, c1) in board._H:
        return False
    if r2 == r1 - 1 and (r2, c2) in board._H:
        return False
    # murs verticaux
    if c2 == c1 + 1 and (r1, c1) in board._V:
        return False
    if c2 == c1 - 1 and (r2, c2) in board._V:
        return False
    return True


from collections import deque

def shortest_path(board, player):
    """
    Calcule le chemin le plus court du joueur donné jusqu'à sa ligne de victoire.
    Retourne une liste de positions [(r0,c0), (r1,c1), ...].
    """
    N = board.N
    start = board._p1 if player == board._P1 else board._p2
    goal_row = N - 1 if player == board._P1 else 0

    visited = set()
    queue = deque()
    queue.append((start, [start]))

    while queue:
        (r, c), path = queue.popleft()
        if r == goal_row:
            return path
        visited.add((r, c))

        for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
            nr, nc = r + dr, c + dc
            if (nr, nc) not in visited and can_move(board, r, c, nr, nc):
                queue.append(((nr, nc), path + [(nr, nc)]))

    return None


def heuristic(board):
    """
    Heuristique : distance du joueur courant à sa ligne de victoire
    moins distance de l’adversaire à sa ligne de victoire.
    """
    current = board._nextPlayer
    opponent = board._P2 if current == board._P1 else board._P1

    path_current = shortest_path(board, current)
    path_opponent = shortest_path(board, opponent)

    dist_current = len(path_current) if path_current else float('inf')
    dist_opponent = len(path_opponent) if path_opponent else float('inf')

    return dist_opponent - dist_current

def maxMin(board : Corridor, maxDepth):
    if board.is_game_over() or maxDepth == 0:
        return heuristic(board), None
    
    best = -999999
    bestMove = None
    for move in board.legal_moves():
        board.play(move)
        eval, _ = minMax(board, maxDepth - 1)
        board.undo()
        if eval > best:
            best = eval
            bestMove = move

    return best, bestMove

def minMax(board : Corridor, maxDepth):
    if board.is_game_over() or maxDepth == 0:
        return -heuristic(board), None
    
    worst = 999999
    bestMove = None
    for move in board.legal_moves():
        board.play(move)
        eval, _ = maxMin(board, maxDepth - 1)
        board.undo()
        if eval < worst:
            worst = eval
            bestMove = move

    return worst, bestMove

# Fonction joueur aléatoire
def joueur_aleatoire(jeu):
    return choice(jeu.legal_moves())

def joueur_miniMax(jeu):
    return maxMin(jeu, 3)[1]

# Fonction principale de match entre deux joueurs
def match(joueur1, joueur2, verbose=True):
    jeu = Corridor()

    while not jeu.is_game_over():
        if verbose:
            print(jeu)

        if jeu._nextPlayer == '1':
            move = joueur1(jeu)
        else:
            move = joueur2(jeu)

        if verbose:
            print(f"Joueur {jeu._nextPlayer} joue {move}")

        jeu.play(move)

    if verbose:
        print(jeu)
        print("Gagnant:", jeu.result())

    return jeu.result()

if __name__ == "__main__":
    match(joueur_miniMax, joueur_aleatoire)
