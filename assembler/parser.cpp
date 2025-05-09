#include "asm.cpp"
#include <stdlib.h>
#include <string.h> //this is for memset
#include <stdio.h>

void reverseString(char *);
void intToBinaryString(int, char *);

int main(int argc, char *argv[])
{

    char *filename = argv[1];
    FILE *file = fopen(filename, "r"); // Open the file for reading
    char *outputName = argv[2];
    if (outputName == NULL)
    {
        outputName = "output.txt"; // default
        printf("output.txt will countain output\n");
    }

    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    bool error = false;
    char line[256]; // Buffer to store each line from the file
    int i = 0;
    char buffer[34];
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen(outputName, "w");

    while (fgets(line, sizeof(line), file) && i < 32)
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';
        if (line[0] != ';' && strlen(line) > 0 && line[0] != '#'){ //if not a comment or only newline

        int output = assign(line,i,&error);
        if (error){
             fclose(file);
             fclose(fptr);
            remove(outputName);
            printf("error found in line: %d\n", i + 1);  
            printf("\naborting...\n");
        }
        // printf("%d\n",output);
        intToBinaryString(output, buffer);
        if (i < 31)
        {
            buffer[32] = '\n';
            buffer[33] = 0;
        }
        else
        {
            buffer[32] = 0;
        }
        // reverseString(buffer);
        fprintf(fptr, buffer);
        // printf(buffer);
        i++;
        } else if (line[0] == '#'){
            //define line
            addSymbol(line, &error);
            if (error == true){
                printf("invalid symbol found, aborting...\n");
            }
        }


    }

    if (i < 31)
    {
        for (int j = 0; j < 32 - i; j++)
        {
            // fill out rest of program with 0
            if (j != 31 - i)
            {
                fprintf(fptr, "00000000000000000000000000000000\n");
            }
            else
            {
                fprintf(fptr, "00000000000000000000000000000000");
            }
        }
    }
    for (int j = 0; j < 64; j++)
    {
        // printf("%d\n",program[j]);
    }
    fclose(file);
    fclose(fptr);

    // run(program);
}

void intToBinaryString(int num, char *buffer)
{
    unsigned int mask = 1U << 31;
    int i;
    for (i = 31; i > -1; i--)
    {
        int tmp = (num & mask) ? 1 : 0;
        if (tmp == 0)
        {
            buffer[i] = '0';
        }
        else
        {
            buffer[i] = '1';
        }
        num <<= 1;
        // printf("%c",buffer[i]);
    }
}
