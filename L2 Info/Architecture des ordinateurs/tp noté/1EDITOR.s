        .pos 0                  # le programme démarre naturellement au début de la mémoire
init:   irmovl  stack, %esp         
        irmovl  t,%esi          # %ebp devient l'adresse du début de la liste
        mrmovl  nbr,%ebx        # %ebx devient un buffer pour retenir le nombre à calculer
        
loop:   isubl   67,%ebx         # on vérifie si les 31 premiers nombres ont été calculés
        jg      end             # si oui, teminer le programme
        mrmovl  nbr,%ebx        # on réinitialise %ebx qu'on avait modifier lors de la vérification
        pushl   %ebx            # le deuxième argument argument de la fonction est nbr
        call    raccar          # on appelle la fonction seulement après avoir rentré dans la pile ses 3 arguments 

        iaddl   4,%esp          # reset du pointeur de pile pour préparer le prochain passage
        iaddl   4,%esi          # on incrémente le pointeur de tableau
        rmmovl  %eax,(%esi)     # on place la valeur de retour de fonction à la tête du tableau
        mrmovl  nbr,%ebx        # on reset %ebx
        incl    %ebx          # on passe au nombre suivant
        rmmovl  %ebx,nbr        # sauvegarde du nombre dans la mémoire
        jmp     loop            # on recommence tout avec nbr + 1
        
  
raccar: 
        mrmovl  4(%esp),%eax    # %ebx obtient la valeur de nbr
        irmovl  0,%ecx          # %ecx sera la valeur x à mettre au carré
        irmovl  0,%edx          # %edx sera le carré calculé
        
carloop:                        # le calcul ic est (x+1)² = x²+2x+1 ou (%edx+1)² = %edx²+2*%edx+1
        addl    %ecx,%edx       # on ajoute la valeur à calculer précédente à %eax
        addl    %ecx,%edx       # idem pour terminer la partie "+2x"
        incl    %edx          # on termine le calcule avec "+1"
        pushl   %edx            # on push %edx pour pouvoir le récupérer après la comparaison

        subl    %eax,%edx       # on regarde la différence entre %eax et %edx
        jg      stopTooBig      # si %edx est plus grand, alors il faut renvoyer la valeur x
        je      stopGood        # si ils sont égaux, renvoyer x+1

                                # s'il est plus petit, continuer avec (x+1)+1 :
        popl    %edx            # on récupère le %edx pré comparaison
        incl    %ecx          # on incrémente x
        jmp     carloop         # on test le carré du nouveau x
        
stopTooBig:
        decl    %ecx          # si le carré de (x+1) est plus grand que nbr, alors il faut renvoyer x

stopGood:
        popl    %edx            # il faut sortir la dernière entrée de la pile car on saute le popl qui s'en charge normalement
        incl    %ecx          # on incrémente x car le calcul juste était celui de (x+1)²
        rrmovl  %ecx,%eax       # par convention, on donne la valeur de sortie à %eax
        irmovl  0,%edx          # reset des 2 autres registres utilisés dans la fonction
        irmovl  0,%ecx
        ret                     # fin de la fonction, %eax



end:    halt

        .pos 0x200              # éloignement des donnee du programme pour éviter tout incident
donnees:  
        nbr:    .long   1       # on garde en mémoire le nombre à calculé
        t:      .long   0       # début de la liste
        
        .pos 0x400              # on éloigne encore plus la pile car elle se déplace vers le tableau t
stack: