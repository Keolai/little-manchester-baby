#include "asm.h"
#include <string.h> 
#include <stdio.h>

char * instructionsLower[7] = {"jmp", "jrp","ldn","sto","sub","sub","cmp"}; 
char * instructionsUpper[7] = {"JMP", "JRP","LDN","STO","SUB","SUB","CMP"}; 
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

    line.instr = translateInstr(instrToken); 
    //printf("%d\n",line.instr);

    return 0;
}

//translate line
int translateInstr(char * instrLine){
    //int result = 0;
    for (int i = 0; i < 7; i++){
        if (strcmp(instrLine,instructionsLower[i]) == 0 || strcmp(instrLine,instructionsUpper[i]) == 0){
             //printf("%d\n",i);
            return i; 
        }
    }
    return -1; //error
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