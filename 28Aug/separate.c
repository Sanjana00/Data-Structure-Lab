#include <stdio.h>

int main()
{
    printf("Enter string: ");
    char s[100], vowel[100], cons[100], spec[100];
    scanf("%[^\n]", s);
    int i, vow = 0, con = 0, sp = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
            spec[sp++] = c;
        else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            vowel[vow++] = c;
        else
            cons[con++] = c;
    }
    printf("Vowels: ");
    for (i = 0; i < vow; i++)
        printf("%c", vowel[i]);
    printf("\nConsonants: ");
    for (i = 0; i < con; i++)
        printf("%c", cons[i]);
    printf("\nSpecial characters: ");
    for (i = 0; i < sp; i++)
        printf("%c", spec[i]);
    printf("\n");
    return 0;
}
