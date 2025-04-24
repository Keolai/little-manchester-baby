#include "asm.cpp"
#include <stdlib.h>
#include <string.h> //this is for memset
#include <stdio.h>

int main(int argc, char *argv[])
{

    char *filename = argv[1];
    FILE *file = fopen(filename, "r"); // Open the file for reading
    char *outputName = argv[2];
    if (outputName == NULL){
        outputName = "output.txt"; //default
        printf("output.txt will countain output\n");

    }

    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256]; // Buffer to store each line from the file
    int i = 0;

    while (fgets(line, sizeof(line), file))
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        assign(line);
        //printf(line);
        i++;
    }
    for (int j = 0; j < 64; j++)
    {
        // printf("%d\n",program[j]);
    }
    fclose(file);

   // run(program);
}