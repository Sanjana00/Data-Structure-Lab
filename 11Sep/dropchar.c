#include <stdio.h>

// function to check if character is present in the given string or not, returns 1 if present else 0
int isPresent(char c, char* s)
{
    int i = 0;
    for (i = 0; s[i] != '\0'; i++) // loop iterating over all characters in the string
        if (c == s[i]) // character is present in string
            return 1;
    return 0; // character not found
}

int main(int argc, char* argv[])
{
    if (argc != 4) // incorrect number of command line arguments
    {
        printf("Incorrect number of command line arguments provided\n");
        return 0;
    }
    FILE *fps, *fpd; 
    fps = fopen(argv[1], "r"); // opening input file for reading
    if (fps == NULL) // input file could not be opened
    {
        printf("Input file could not be opened\n");
        return 0;
    }
    fpd = fopen(argv[2], "w"); // opening output file for writing
    if (fpd == NULL) // output file could not be opened
    {
        printf("Output file could not be opened\n");
        return 0;
    }
    char ch;
    while ((ch = fgetc(fps)) != EOF) // reading each character in input file
    {
        if (isPresent(ch, argv[3])) // checking if character is present in string
            continue;
        fputc(ch, fpd); // if not present, write to output file
    }
    // closing input and output files
    fclose(fps); 
    fclose(fpd);
    return 0;
}
