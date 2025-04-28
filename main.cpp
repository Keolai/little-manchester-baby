#include "baby.cpp"
#include <stdlib.h>

void reverseString(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int binaryStringToInt(const char *binaryStr)
{
    int value = 0;
    while (*binaryStr)
    {
        if (*binaryStr == '1')
        {
            value = (value << 1) | 1;
        }
        else if (*binaryStr == '0')
        {
            value = value << 1;
        }
        else
        {
            fprintf(stderr, "Error: Invalid character in binary string\n");
            // return -1; // Return an error value
        }
        binaryStr++;
    }
    return value;
}

int main(int argc, char *argv[])
{
    int program[64];
    memset(program, 0, 64 * (sizeof(int)));

    if (argc < 2)
    {
        printf("no file given, aborting...\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r"); // Open the file for reading

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

        // Reverse the binary string
        reverseString(line);

        // Convert the reversed binary string to an integer
        int value = binaryStringToInt(line);
        // printf("Parsed integer: %d\n", value);
        program[i] = value;
        i++;
    }
    for (int j = 0; j < 64; j++)
    {
        printf("%d\n",program[j]);
    }
    fclose(file);

    run(program);
}
