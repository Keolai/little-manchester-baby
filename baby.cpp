
#include "baby.h"
#include <string.h> //this is for memset
#include <stdio.h>

/* computer memory and program memory are in same place */

struct sys_t baby; // I dont like global variable
int opcount = 0;

int run(int *arr)
{

    /* initialize */
    baby.pc = 0;
    baby.acc = 0;
    memset(baby.mem, 0, sizeof(baby.mem));
    program_inject(arr);
    baby.program_end = false;
    /* done initializing */

    /* run loop */
    while (baby.program_end == false)
    {
        step();
        opcount++;
    }
    printf("result:%d\n", baby.mem[27]);
    printf("opcount:%d\n", opcount);

    printf("memory dump at time of completion:\n");
    for (int i = 0; i < 32; i++){
        printf("%d: %x\n",i,baby.mem[i]); 
    }

    return 0;
}

int step()
{
    baby.pc++; // update pc
    int line = baby.mem[baby.pc];

    int instr = (line & 0x0000e000) >> 13;
    int operand = line & 0x1f;
    int mem = baby.mem[operand] & 0xffffffff;

    /* run instruction */
    switch (instr)
    {
    case 0: // jump
        baby.pc = mem;
        break;
    case 1: // jrp
        baby.pc = baby.pc + mem;
        break;
    case 2: // ldn
        baby.acc = -mem;
        break;
    case 3: // sto
        baby.mem[operand] = baby.acc;
        break;
    case 4:
    case 5: // sub
        baby.acc = baby.acc - mem;
        break;
    case 6: // cmp
        if (baby.acc < 0)
        {
            baby.pc++;
            opcount++;
        }
        break;
    case 7: // stop
        baby.program_end = true;
        printf("program will now end.\n");
        break;
    default:
        baby.program_end = true;
        printf("error: bad instruction\n");
        return 1;
    }

    if (baby.pc > 63)
    {
        baby.program_end = true;
        printf("pc went out of range\n");
        return 1;
    }
}

/* HELPERS */

int program_inject(int *arr)
{
    for (int i = 0; i < 32; i++)
    {
        baby.mem[i] = arr[i];
        if (baby.mem[i] > 0x7fffffff)
        {
            baby.mem[i] = -0x80000000 + (baby.mem[i] & 0x7fffffff);
        }
        // printf("%d\n",baby.mem[i]);
    }
}
