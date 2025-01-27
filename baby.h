#ifndef BABY_H
#define BABY_H
#define CHAR_SIZE 8

typedef struct sys_t
{
    int pc; //program counter
    int acc;    //accumulator
    int mem[32];    //memory
    bool program_end;   //if program has ended
};
int program_inject(int *);
int step();
int run(int *);

#endif
