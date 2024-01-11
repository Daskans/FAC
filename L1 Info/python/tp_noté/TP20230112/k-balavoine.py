# -*- coding: utf-8 -*-
"""
@author: ______________________
"""

from PIL.Image import *

def recupereImage(img:Image,ligne:int,colonne:int) -> Image:
    size=img.size
    New=new("RGB",(size[0]//ligne,size[1]//colonne))
    for i in range(size[0]//ligne):
        for j in range(size[1]//colonne):
            New.putpixel((i,j),(img.getpixel((i*ligne,j*colonne))))
    return New
#==============================================================================

# Décommenter pour tester
#img=open("hidden_tiger.png")
#img.show()
#img_cache = recupereImage(img,5,5)
#img_cache.show()

#==============================================================================

def cacheImage(img:Image, img_a_cacher:Image,ligne:int,colonne:int)-> None :
    size_img=img.size
    size_cache=img_a_cacher.size
    while size_cache[0]>size_img[0]:
        size_cache[0]=size_cache[0]//2
        
    while size_cache[1]>size_img[1]:
        size_cache[1]=size_cache[1]//2
        
    for i in range(size_cache[0]):
        for j in range(size_cache[1]):
            img.putpixel((i*ligne,j*colonne),(img_a_cacher.getpixel((i,j))))
            
    return img
#==============================================================================

# Décommenter pour tester
#img_cache=open("petite_panthere.png")
#img=open("tiger.png")
#cacheImage(img, img_cache,5,5)
#img.show()
#img.save("mon_hidden_tiger.png")
#img=open("mon_hidden_tiger.png")
#img_cache = recupereImage(img,5,5)
#img_cache.show()

#==============================================================================

def recupereBienImage(img:Image,ligne:int,colonne:int) -> Image:
    size=img.size
    New=new("RGB",(size[0]//ligne,size[1]//colonne))
    for i in range(size[0]//ligne):
        for j in range(size[1]//colonne):
            pixel=img.getpixel((i*ligne,j*colonne))
            if pixel[2]%2==0:
                pixel=(0,0,0)
            else:
                pixel=(255,255,255)
            New.putpixel((i,j),(pixel))
    return New    

#==============================================================================

# Décommenter pour tester
#img=open("hidden_tiger2.png")
#img.show()
#img_cache = recupereBienImage(img,1,1)
#img_cache.show()

#==============================================================================

def cacheBienImage(img, img_a_cacher,ligne,colonne)-> None :
    size_img=img.size
    size_cache=img_a_cacher.size
    while size_cache[0]>size_img[0]:
        size_cache[0]=size_cache[0]//2
        
    while size_cache[1]>size_img[1]:
        size_cache[1]=size_cache[1]//2
        
    for i in range(size_cache[0]):
        for j in range(size_cache[1]):
            pixel_cache=img_a_cacher.getpixel((i,j))
            pixel=img.getpixel((i*ligne,j*colonne))
            if pixel_cache==(0,0,0) and pixel[2]%2!=0:
                pixel[2]+=1
            elif pixel_cache==(255,255,255) and pixel[2]%2==0:
                pixel[2]+=1
            img.putpixel((i*ligne,j*colonne),(pixel))
    return img

#==============================================================================

# Décommenter pour tester    
img_cache=open("sens_vie.png")
img=open("tiger.png")
cacheBienImage(img, img_cache,1,1)
img.show()
img.save("mon_hidden_tiger2.png")

mon_img_cache = recupereBienImage(img,1,1)
mon_img_cache.show()
           
#==============================================================================

from bibgraphes import *

#==============================================================================

# Rappel des fonctions du TP sur les graphes

def sommetAccessible(G:graphe)->sommet:
    """ retourne un sommet non marqué ayant au moins un voisin marqué, ou bien
    retourne None s’il n’existe pas de tel sommet """
    
    for s in listeSommets(G):
        if not estMarqueSommet(s):
            for v in listeVoisins(s):
                if estMarqueSommet(v):
                    return s
            
    return None

def marquerAccessibles(G:graphe,s:sommet):
    """ 1 - elle marque d’abord le sommet  𝑠 ,
        2 - elle utilise ensuite une boucle while : tant que sommetAccessible
            retourne un sommet (et non None), elle le marque. """
    
    marquerSommet(s)
    
    s = sommetAccessible(G)
    while s != None:
        marquerSommet(s)
        s = sommetAccessible(G)

from random import randint as rd

def elementAleatoireListe(L):
    return L[rd(0,len(L)-1)]
                              
def estConnexe(G):
    """ teste si le graphe G est connexe. Cette fonction tire un sommet de
    manière aléatoire. Attention à bien démarquer tous les sommets dès le
    départ. """
    marquerAccessibles(G,elementAleatoireListe(listeSommets(G)))

#==============================================================================

def toutDemarquer(G:graphe):
    for i in listeSommets(G):
        demarquerSommet(i)
    

def trouveNonMarque(G:graphe) -> sommet:
    for i in listeSommets(G):
        if estMarqueSommet(i):
            return True
    return None
    
def nombreComposanteConnexe(G:graphe) -> int:
    connexe=1
    for i in listeSommets(G):
        if listeVoisins(i)==[]:
            connexe+=1
    return connexe
#fonction pas finis, j'avais prévu de marqué les sommets déjà analysé pour prévenir les doublons (exemple Ecosse/Pays de Galles)
#==============================================================================

# Décommenter pour tester    
# Test sur europe.dot

#europe = ouvrirGraphe("europe.dot")
#print(nombreComposanteConnexe(europe))
#afficherGraphe(europe)
