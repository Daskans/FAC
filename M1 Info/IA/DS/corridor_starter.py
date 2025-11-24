from corridor import Corridor
from random import choice

# Fonction joueur aléatoire
def joueur_aleatoire(jeu):
    return choice(jeu.legal_moves())

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
    match(joueur_aleatoire, joueur_aleatoire)
