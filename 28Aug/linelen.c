#include <stdio.h>

int main()
{
    char line[100];
    int len = 0, i;
    // taking user input for line
    printf("Enter the line: ");
    scanf("%[^\n]", line);
    // for loop to read each character in the line
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] >= 'A' && line[i] <= 'Z') // if character is uppercase English letter
            len++;
        else if (line[i] >= 'a' && line[i] <= 'z') // if character is lowercase English letter
            len++;
    }
    // output
    printf("Length of the line is %d!\n", len);
    return 0;
}
