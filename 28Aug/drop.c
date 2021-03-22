#include <stdio.h>

int main()
{
    char line[100], drop[25];
    // taking user input for line and string to be dropped
    printf("Enter the line: ");
    scanf("%[^\n]", line);
    printf("Enter the string to be dropped: ");
    scanf("%s", drop);
    int i, j, flag = 0, l = 0;

    // loop to find the length of the string to be dropped
    for (i = 0; drop[i] != '\0'; i++)
        l++;

    // output
    printf("The resulting line: ");
    // loop through each character of line
    for (i = 0; line[i] != '\0'; i++)
    {
        // if current character is same as beginning of string to be dropped
        if (line[i] == drop[0])
        {
            flag = 1; // raising flag to skip characters
            // loop through each character of string to be dropped
            for (j = 1; drop[j] != '\0'; j++)
            {
                if (line[i + j] != drop[j])
                {
                    flag = 0; // no characters to be skipped, flag lowered
                    break;
                }
            }
        }
        if (flag == 0) // character is to be printed
            printf("%c", line[i]);
        else // characters to be dropped
        {
            i += l - 1;
            flag = 0;
        }
    }
    printf("\n");
    return 0;
}
