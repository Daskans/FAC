#include "head.S"

main:
// Initialiser la pile
	movl $(stack + STACK_SIZE),%esp
	movl %esp,%ebp

// On affiche deux caracteres
	movl $0xb8000,%ebx
	movb charA,%al  // lire la variable charA
	movb %al,(%ebx)
	addl $2,%ebx    // sauter 2 octets: un pour le caractere, l autre pour la couleur
	addb $1,%al     // passer a un B
	movb %al,(%ebx) // et l afficher

	// recuperer un caractere tape au clavier
	call getchar

// On l affiche a l ecran
	movl $0xb8004,%ebx
	movb %al,(%ebx)

// On s arrete
	hlt

	.size main,.-main



// Juste un exemple de variable
charA:
	.byte 65

.comm stack,STACK_SIZE
