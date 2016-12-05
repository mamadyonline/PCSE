#ifndef __START_H__
#define __START_H__

#define FIRST_STACK_SIZE 16384

#ifndef ASSEMBLER

extern char first_stack[FIRST_STACK_SIZE];

extern void ecrit_haut_droite(char * car);

/* The kernel entry point */
void kernel_start(void);

#endif

#endif
