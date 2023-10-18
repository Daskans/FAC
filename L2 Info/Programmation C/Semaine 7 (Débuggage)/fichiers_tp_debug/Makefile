# l'option -g est essentielle pour pouvoir débugguer
CFLAGS=-std=c99 -Wall -Werror -g -m32

#Liste des exécutables à générer
EXECS=binomial debug dichotomic_search gdbSegFault_2free gdbSegFault_struct masquage1 rotateTrio stack

# Par défaut (lorsqu'on tape juste 'make') on va générer tous les exécutables
all: $(EXECS)

binomial: binomial.c
	$(CC) -std=c99 -Wall -Werror -g $^ -o $@
#Ici à chaque exécutable conrespond un unique fichier .c. Il n'y a donc pas de dépendances à gérer. On utilise juste les règles implicites.


# Les cibles all et clean sont (comme d'habitude) des cicles virtuelles
.PHONY: clean all


clean:
	rm -f $(EXECS)