#ifndef ASM_H
#define ASM_H

typedef struct instr_t
{
    int instr; //instruction
    int arg; //argument
};

typedef struct symbol_t
{
    char name[32]; //name can be up to 31 characters long
    int val;
    bool used; 
};

int assign(char *,int, bool*);
int translateInstr(char *);
int translateArg(char *, bool*);
int output();
void addSymbol(char*, bool*);
int placeIntoTable(char*, int);
void copyStr(char*,char*);
int checkTable(char*, bool*);

#endif