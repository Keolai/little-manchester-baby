#include "asm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define INSTRNUM 9

char *instructionsUpper[INSTRNUM] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP", "NUM"};
struct instr_t line;
int assign(char *input, int lineNum, bool* error)
{

    char *delimeter = " ";

    char *instrToken;
    char *argToken;
    char *tmp;

    line.instr = 0; // clear them
    line.arg = 0;

    tmp = strtok(input, delimeter);

    if (atoi(tmp) != 0 || tmp[0] == 0)
    {
        // printf("line number found\n");

        for (int i = 0; i < 2; i++)
        {
            tmp = strtok(NULL, delimeter);
             printf(tmp);
            switch (i)
            {
            case 0:
                instrToken = tmp;
                break;
            case 1:
                argToken = tmp;
                break;
            }
        }
    }
    else
    {
        // line number not found
        instrToken = tmp;
        tmp = strtok(NULL, delimeter);
        argToken = tmp;
    }

    if (argToken != NULL)
    {
        line.arg = translateArg(argToken);
       // printf("%d\n",line.arg);
    }
    else
    {
        line.arg = 0;
    }

    line.instr = translateInstr(instrToken);
    if (line.instr == -1)
    { 
        printf("error found in line %d\n", lineNum);  
        *error = true;
        return -1; // return error
    }
    //printf("%d\n",line.instr);

    return output();
}

// translate line
int translateInstr(char *instrLine)
{
    // convert ascii to all uppercase
    for (int i = 0; i < strlen(instrLine); i++)
    {
        if ((int)instrLine[i] > 96)
        {
            instrLine[i] = (char)((int)instrLine[i] - 32);
        }
    }
    for (int i = 0; i < INSTRNUM; i++)
    {
        if (strcmp(instrLine, instructionsUpper[i]) == 0)
        {
            // printf("%d\n",i);
            return i;
        }
    }
    return -1; // error
}

int translateArg(char *instrArg)
{
    int sign = 1;
    char *arg = instrArg;
    if (instrArg[0] == '-')
    {
        sign = -1;
        arg += 1;
    }
    int length = strlen(arg);
    int total = 0;
    int power = 1;
    for (int i = length; i > 0; i--)
    {
        total = total + ((int)arg[i - 1] - 48) * (power);
        power *= 10;
    }
    // printf("%d\n",total);
    return total * sign;
}

// return binary code
int output()
{

    int finalInstr = 0;
    if (line.instr != 8)
    { // NUM
        finalInstr += line.instr << 13;
        finalInstr += line.arg;
    }
    else
    {
        finalInstr = line.arg;
    }

    return finalInstr;
}