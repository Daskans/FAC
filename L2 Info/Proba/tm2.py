#!/usr/bin/python3

### Préliminaires
### Les fonctions qui suivent proviennent des exercices du TM1 (sauf facto
### et Catalan)

# factorielle
def facto(n):
    if n<=0:
        return 1
    return n*facto(n-1)

def binomial(n,k):
    return facto(n)//(facto(k)*facto(n-k))

# nombres de Catalan
def Catalan(n):
    return facto(2*n)//facto(n)//facto(n+1)

# Toutes sequences binaires de longueur k (récursive)
def ToutesSequencesBinaires(k):
    if k<=0:
        return [()]
    L = ToutesSequencesBinaires(k-1)
    M = []
    for s in L:
        M.append(s+(0,))
        M.append(s+(1,))
    return M

# Séquences sous-diagonales (fonction récursive)
def ToutesSeqSousDiago(n):
    if n<=0:
        return [()]
    L = ToutesSeqSousDiago(n-1)
    M = []
    for s in L:
        for k in range(1,n+1):
            M.append(s+(k,))
    return M

# Conversion (bijective) entre séquences sous-diagonales
# et permutations
def SeqVersPerm(s):
    n = len(s)
    L = [i for i in range(1,n+1)]
    for j in range(n):
        pos = s[j] -1 # Pour ramener à un indice
        if pos != j:
            temp = L[pos]
            L[pos] = L[j]
            L[j] = temp
    return tuple(L)

# Toutes permutations de taille n
def ToutesPermutations(n):
    L = ToutesSeqSousDiago(n)
    M = []
    for s in L:
        M.append(SeqVersPerm(s))
    return M

# Nombre de points fixe d'une permutation s
# Attention au décalage entre indices et valeurs
def NbPointsFixes(s):
    cpt = 0
    n = len(s)
    for i in range(n):
        if s[i] == i+1: #Les indices commencent à 0, les valeurs à 1
            cpt += 1
    return cpt

############################################
# Les exercices commencent ici.            #
# Vous ne devez mettre que des définitions #
# de fonctions, jusqu'à la partie prévue   #
# pour votre code de démonstration (après  #
# la partie optionnelle)                   #
############################################

#### Exercice 2.1: permutations

## 2.1.1: cycles de longueur 2

# Nombre de cycles de longueur 2 dans une permutation s.
# la valeur i est la première d'un cycle de longueur 2
# si s(i)>i et s(s(i))=i
# Attention au décalage entre indices et valeurs
def Nb2Cycles(s):
    compteur = 0
    for i in range(len(s)):
        if s[i]>i and s[s[i]]==i:
            compter += 1
    return compteur


### Code pour compter les 2-cycles dans toutes les permutations
### de longueur n
# for n in range(2,10):
#     L = ToutesPermutations(n)
#     cpt = 0
#     for s in L:
#         cpt += Nb2Cycles(s)
#     print("Longueur %d: %d permutations, %d 2-cycles"%(n,len(L),cpt))

## 2.1.2: cycles de longueur autre

# Longueur du cycle contenant i
# s(i), c'est s[i-1] à cause du décalage des indices
# Idée: itérer la fonction représentée par s, jusqu'à revenir en i
def LongueurCycle(s,i):
    return None

# La liste retournée donne, pour chaque entier de 1 à n (les longueurs
# possibles de cycles), le nombre de permutations de taille n où 1 est
# dans un cycle de cette longueur
def Longueurs(n):
    return None

#### Exercice 2.2: mots de Dyck

## 2.2.1:  EstDyck
# True si s est un mot de Dyck, False sinon
def EstDyck(s):
    return None

## 2.2.2: tous les mots de Dyck de longueur 2n
def TousMotsDyck(n):
    return None

## 2.2.3: comptage des pics

# Nombre de pics dans un mot (de Dyck)
# (On ne demande pas de vérifier que c'est un mot de Dyck)
def Pics(s):
    return None

## 2.2.4:  nombre moyen de pics dans les mots de Dyck
# On compte le nombre total de pics, on divisera par Catalan(n)

# Retourne le nombre total de pics dans l'ensemble des mots de Dyck
# de longueur 2n
def TotalPics(n):
    return None
    
#####################################################################
n = 5
k = 3
s = (1,2,2,3,3,3,4,4,4,4,5,5,5,5,5)
print("facto(n) : ",facto(n))
print("binomial(n, k) : ",binomial(n, k))
print("Catalan(n) : ",Catalan(n))
print("ToutesSequencesBinaires(k) : ",ToutesSequencesBinaires(k))        
print("ToutesSeqSousDiago(k) : ",ToutesSeqSousDiago(k))
print("SeqVersPerm(s) : ",SeqVersPerm(s))         
print("ToutesPermutations(k) : ",ToutesPermutations(k))                
print("NbPointsFixes(s) : ",NbPointsFixes(s))
print("NbPointsFixes(SeqVersPerm(s)) : ",NbPointsFixes(SeqVersPerm(s)))
#####################################################################

print("\nExercice 2.1: permutations")

print("Question 2.1.1): comptage des cycles de longueur 2")

##
##

## Formule proposée pour le nombre toal de cycles de longueur 2 dans
## l'ensemble des permutations de taille n:
##

print("\nQuestion 2.1.2: comptage des permutations en fonction de la longueur du cycle contenant 1")

##
##

## Formule proposée pour le nombre total de permutations de taille n dans
## lesquelles 1 est dans un cycle de longueur k:
##

print("\n\nExercice 2.2: mots de Dyck")
print("Question 2.2.1: dire si un mot est un mot de Dyck")

##
##

print("\nQuestion 2.2.2: génération de tous les mots de Dyck de longueur donnée")

print("\nQuestion 2.2.3: comptage des pics")

print("\nQuestion 2.2.4: nombre moyen de pics dans les mots de Dyck de longueur 2n")

##
##

## Formule proposée pour le nombe moyen de pics:
##
