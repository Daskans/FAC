#!/usr/bin/python3

# NOM:
# PRENOM:
# GROUPE:


# Probabilités, Statistiques, Combinatoire (Licence 2)
# TM1

# Certaines fonctions sont fournies comme exemples; celles dont le
# corps est seulement "return None" sont celles qu'il faut écrire soi-même.
# Il est possible que pour certains exercices, il soit judicieux d'écrire
# des fonctions en plus!

# pour vérifier qu'une liste ne contient pas de doublons
# (il faut que python arrive à trier... pas des choses trop inhomogènes donc)
# Des listes ou tuples d'entiers sont triés dans l'ordre lexicographique
def TousDifferents(L):
    LL = sorted(L)
    m = len(LL)
    for i in range(m-1):
        if LL[i]==LL[i+1]:
            return False
    return True

# Exercice 1

# Codage de n comme séquence binaire de longueur k
def EntierVersBinaire(k,n):
    L=[0 for i in range(k)]
    for i in range(k-1, -1, -1):
        L[-i-1]=n//(2**i)
        n=n%(2**i)
    return tuple(L)
    

# Décodage: à partir de la séquence binaire, retrouver n
# NOTE: on n'a pas besoin de calculs de puissances
def BinaireVersEntier(t):
    n=0
    for i in range(len(t)):
        n+=t[-i-1]*(2**i)
    return n

# Liste de toutes les séquences binaires de longueur k
# Algorithme suggéré: prendre les entiers entre 0 et 2**k -1
# et les convertir en séquences binaires
def ToutesSequencesBinaires(k):
    L=[]
    for i in range(2**(k)):
        L.append(EntierVersBinaire(k, i))
    return L

# Nombre maximum de 1 consécutifs dans un tuple t
def NbConsecutifs(t):
    n=0
    max_n=0
    for i in range(len(t)):
        if t[i]==1:
            n+=1
            if n>max_n:
                max_n=n
        elif t[i]==0:
            n=0
    return max_n

# Nombre de séquences dans L sans au moins m 1 consecutifs
# On donne la liste pour éviter de la calculer une fois pour chaque m 
def NbSansKConsecutifs(L,m):
    cpt = 0
    for x in L:
        if NbConsecutifs(x)<l:
            cpt += 1
    return cpt

# Pour chaque valeur l de 1 à m: affiche combien de séquences binaires
# de longueur k n'ONT PAS au moins l 1 consécutifs
def Comptages(k,m):
    L = ToutesSequencesBinaires(k)
    for l in range(1,m+1):
        n = NbSansKConsecutifs(L,l)
        print("Longueur %d, il y a %d mots qui n'ont pas %d 1 consecutifs"%(k,n,l))
    return
    

# Plus petit m, entre 0 et k, tel que moins de la moitié des séquences
# de longueur k ait m 1 consécutifs
def MinConsecutifs(k):
    pass # gné ?
    

# Version récursive de ToutesSequencesBinaires
def ToutesSequencesBinairesRec(k):
    if k<=0:
        return [()]
    L = ToutesSequencesBinairesRec(k-1)
    M = []
    for x in L:
        M.append(x+(0,))
        M.append(x+(1,))
    return M

    
# Exercice 2

# Conversion d'une séquence binaire de longueur k en une partie de [[1,k]]
def SequenceVersPartie(t):
    return None

# Liste de toutes les parties de cardinal k de [[1,n]]
def Parties(n,k):
    return None

# Première partie de [[1,n]] de cardinal k, dans l'ordre lexicographique
def PremierePartie(n,k): 
    return None

#############################################
# Expliquer ici (en commentaires) comment est calculée la
# partie suivante
#
#
#
#############################################

# Retourne la partie qui suit s dans l'ordre lexicographique; on n'a pas
# besoin de k (c'est la longueur de s) mais on a besoin de n
def Suivante(n,s):
    return None

# Comme la fonction Parties, mais avec PremierePartie() et Suivante()
def PartiesBis(n,k):
    L=[]
    s = PremierePartie(n,k)
    while s!=None:
        L.append(s)
        s = Suivante(n,s)
    return L

# Exercice 3
# Permutations

# Toutes les séquences sous-diagonales, version récursive
# Convention: il existe une seule séquence sous-diagonale de longueur 0
# (correspond au mot vide)
def ToutesSeqSousDiagoRec(n):
    if n<=0:
        return [()]
    L = ToutesSeqSousDiagoRec(n-1)
    M = []
    for s in L:
        for k in range(1,n+1):
            M.append(s+(k,))
    return M

# Version itérative, à écrire
def ToutesSeqSousDiago(n):
    return None

# Conversion d'une sequence sous-diagonale en permutation
# S'inspirer de l'ex. 1.10 feuille TD1
def SeqVersPerm(s):
    return None

# Toutes les permutations: par conversion depuis les séquences
# sous-diagonales
def ToutesPermutations(n):
    L = [SeqVersPerm(s) for s in ToutesSeqSousDiago(n)]
    return L

# Nombre de points fixe d'une permutation s
def NbPointsFixes(s):
    return None

# Nombre total de points fixes dans toutes les permutations
# de taille n
def ComptePointsFixes(n):
    L = ToutesPermutations(n)
    total = 0
    for s in L:
        total = total + PointsFixes(s)
    return total

# Nombre de dérangements parmi les permutations de taille n
# Un dérangement est une permutation qui n'a aucun point fixe
def NbDerangements(n):
    return None



#######
# Mettre ici tous les appels de fonctions et affichages pour
# répondre aux questions posées dans le sujet (sous forme d'affichages)

print("Exercice 1: séquences binaires")
EntierVersBinaire(8,15)
BinaireVersEntier((0,0,0,1,1,1))
ToutesSequencesBinaires(4)
NbConsecutifs((1,1,1,0,1,1,0,1,1,1,1,1,0,1))

print("\n\nExercice 2: parties d'un ensemble")
#...

print("\n\nExercice 3: permutations")
#...
