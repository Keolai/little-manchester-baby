#include "asm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define INSTRNUM 9

char *instructionsUpper[INSTRNUM] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP", "NUM"};
struct instr_t line;
struct symbol_t symbols[32];

static char *delimeter = " ";

int assign(char *input, int lineNum, bool *error)
{

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
        bool notPresent = false;
        int tmp = checkTable(argToken, &notPresent);

        if (notPresent)
        {
            // bool error = false;
            // need to check if its even a number
            bool argError = false;
            line.arg = translateArg(argToken, &argError);
            if (argError)
            {
                *error = true;
                return -1;
            }
        }
        else
        {
            line.arg = tmp;
        }
        // printf("%d\n",line.arg);
    }
    else
    {
        line.arg = 0;
    }

    line.instr = translateInstr(instrToken);
    if (line.instr == -1)
    {
        *error = true;
        return -1; // return error
    }
    // printf("%d\n",line.instr);

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

int translateArg(char *instrArg, bool *error)
{
    // if number is base 10
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
        int tmp = ((int)arg[i - 1] - 48);
        if (tmp < 0 || tmp > 9)
        {
            // throw error
            // printf("invalid number\n");
            *error = true;
        }
        total = total + tmp * (power);
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

void addSymbol(char *input, bool *error)
{
    char *tmp;
    char *name;
    char *val;
    char *define = "define";
    tmp = strtok(input, delimeter);
    if (tmp != NULL && strlen(tmp) > 1)
    {   // #define
        // printf(tmp + 1);
        if (strcmp((tmp + 1), define) == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                tmp = strtok(NULL, delimeter);
                // printf(tmp);
                switch (i)
                {
                case 0:
                    name = tmp;
                    break;
                case 1:
                    val = tmp;
                    break;
                }
            }
        }
        else
        { // #notDefine
            *error = true;
            return;
        }
    }
    else
    { // # define
        for (int i = 0; i < 3; i++)
        {
            tmp = strtok(NULL, delimeter);
            // printf(tmp);
            switch (i)
            {
            case 0:
                if (strcmp(define, tmp) != 0)
                {
                    *error = true;
                    return;
                }
                break;
            case 1:
                name = tmp;
                break;
            case 2:
                val = tmp;
                break;
            }
        }
    }
    int value = translateArg(val, error);
    placeIntoTable(name, value);
}

int placeIntoTable(char *name, int val)
{
    for (int i = 0; i < 32; i++)
    {
        if (symbols[i].used == false)
        { // unused
            copyStr(symbols[i].name, name);
            symbols[i].val = val;
            symbols[i].used = true;
            // printf(curSymbol.name);
            // printf(" %d\n", i);
            return 0;
        }
    }
    return -1; // no room left
}

void copyStr(char *dest, char *start)
{
    for (int i = 0; i < strlen(start); i++)
    {
        dest[i] = start[i];
        // printf("%c\n", dest[i]);
    }
}

int checkTable(char *name, bool *notPresent)
{
    // printf("checking name: ");
    // printf(name);
    // printf("\n");
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(symbols[i].name, name) == 0)
        {
            return symbols[i].val;
        }
    }
    *notPresent = true;
    return -1;
}