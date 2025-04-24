#include "asm.h"
#include <string.h> 
#include <stdio.h>

struct instr_t line; 
//main 
int assign(char *input){

    char* delimeter = " ";

    char * instrToken;
    char * argToken;
    char *tmp;

    tmp = strtok(input,delimeter);

    for (int i = 0; i < 2; i++){
        tmp = strtok(NULL,delimeter);
        //printf(tmp);
        switch(i){
            case 0:
            instrToken = tmp;
            break;
            case 1:
            argToken = tmp;
            break;
        }
    }

    if (argToken != NULL){
        line.arg = translateArg(argToken);
       // printf("%d\n",line.arg);
    } else {
        line.arg = 0; 
    }


    return 0;
}

//translate line
int translateInstr(char * instrLine){

    return 0;
}

int translateArg(char * instrArg){
    int length = strlen(instrArg);
    int total = 0;
    int power = 1; 
    for (int i = length; i > 0; i--){
        total = total + ((int)instrArg[i - 1] - 48)* (power);
        power *= 10; 
    }
   // printf("%d\n",total);
    return total;
}

//return binary code
int output(){

    return 0;
}