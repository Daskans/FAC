#define MULTIBOOT_HEADER_MAGIC  0x1BADB002
#define MULTIBOOT_HEADER_FLAGS  0x00010003
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002
#define STACK_SIZE 0x10000

.text
.globl _start
.align 4
multiboot_header:
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long -(MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEADER_FLAGS)
.long multiboot_header
.long multiboot_header
.long _edata
.long _end
.long _start
.type _start,@function

_start:
// On commence par nettoyer l ecran
	movl $0xb8000,%edi
	movw $0x0720,%ax
	movl $80*25,%ecx

        cld
	rep stosw

        // Effacer le curseur

        // start
        movw $0x3d4,%dx
        movb $0xa,%al
        outb %al,%dx
        movw $0x3d5,%dx
        inb %dx,%al
        andb $0xc0,%al
        orb  $0x1f,%al
        outb %al,%dx

        // end
        movw $0x3d4,%dx
        movb $0xb,%al
        outb %al,%dx
        movw $0x3d5,%dx
        inb %dx,%al
        andb $0xe0,%al
        orb  $0x1f,%al
        outb %al,%dx

        jmp main

// char getchar(void);

getchar:
// Nettoyer le haut de eax
	movl $0,%eax
// On attend qu un caractere arrive sur le port serie
	movw $0x3f8+5,%dx
	movb $1,%cl
loop:
	inb  %dx,%al
	andb %cl,%al    // tester l arrivee
	je   loop

// Il est arrive, on le lit
	movw $0x3f8,%dx
	inb  %dx,%al
	ret

	.size getchar,.-getchar

// void putchar(char);

putchar:
// On emet un charactere sur le port serie
	movl 4(%esp),%eax
	movw $0x3F8,%dx
	outb %al,%dx
	ret

	.size putchar,.-putchar

