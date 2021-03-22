#include <stdio.h>

int main()
{
    char str[50];
    // taking string input from user
    printf("Enter a string: ");
    scanf("%s", str);
    int i, count = 0;
    // for loop to access each character in string until null character is encountered
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') //if character is an uppercase alphabet
            count++;
        else if (str[i] >= 'a' && str[i] <= 'z') // if character is a lowercase alphabet
            count++;
    }
    // display
    printf("The number of English letters in the string \"%s\" is %d.\n", str, count);
    return 0;
}
