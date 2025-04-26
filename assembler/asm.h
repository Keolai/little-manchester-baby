#ifndef ASM_H
#define ASM_H

typedef struct instr_t
{
    int instr; //instruction
    int arg; //argument
};

int assign(char *,int, bool*);
int translateInstr(char *);
int translateArg(char *);
int output();

#endif