        .pos 0                  # le programme démarre naturellement au début de la mémoire
init:   irmovl  t, %esp         # %esp devient l'adresse du début de la liste
        mrmovl  nbr,%ebx        # %ebx devient un buffer pour retenir le nombre à calculer
        
loop:   isubl   31,%ebx         # on vérifie si les 31 premiers nombres ont été calculés
        je      end             # si oui, teminer le programme
        mrmovl  nbr,%ebx        # on réinitialise %ebx qu'on avait modifier lors de la vérification
      
                                # calculons (nbr+1)² =  nbr²+2*nbr+1
        mrmovl  (%esp),%eax     # on donne à %eax la dernière valeur de la liste, à savoir "nbr²"
        addl    %ebx,%eax       # on ajoute la valeur à calculer précédente à %eax
        addl    %ebx,%eax       # idem pour terminer la partie "+2x"
        iaddl   1,%eax          # on termine la calcule avec "+1"

        iaddl   4,%esp          # on incrémente la liste (4 pour 1 emplacement)
        rmmovl  %eax,(%esp)     # %eax est placer en tête de liste
        iaddl   1,%ebx          # on passe au nombre suivant
        rmmovl  %ebx,nbr        # sauvegarde du nombre dans la mémoire
        jmp     loop            # on refait le calculer pour (nbr+1)²
        
end:    halt


        .pos 0x300              # éloignement des donnee du programme pour éviter tout incident
donnees:  
        nbr:.long   1           # on garde en mémoire le nombre précédent calculé
        t:  .long   1           # début de la liste