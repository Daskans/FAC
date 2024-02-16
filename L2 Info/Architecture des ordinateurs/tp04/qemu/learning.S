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

	movl $0xb8004,%ebx
fun:
	// recuperer un caractere tape au clavier
	call getchar

// tester si char est "entrée"
	cmpb $13,%al
	je entree
	movb %al,(%ebx)
	addl $2,%ebx
	jmp stop


// On l affiche a l ecran
entree:
	movl $160,%ecx
	movl $0xb8000,%eax
	movl %ebx,%edx
	
	addl %ecx,%ebx

// On s arrete
stop:
	jmp fun

	.size main,.-main



// Juste un exemple de variable
charA:
	.byte 65

.comm stack,STACK_SIZE
