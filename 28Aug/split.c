#include <stdio.h>

int main()
{
    printf("Enter the line: ");
    char s[100];
    scanf("%[^\n]", s);
    getchar();
    char c;
    printf("Enter splitting character: ");
    c = getchar();
    int i, j, start = 0, count = 1, pos = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != c)
            pos++;
        else if (s[i] == '\0')
            pos = i;
        else
        {
            printf("Part %d: ", count);
            count++;
            for (j = start; j < pos; j++)
                printf("%c", s[j]);
            printf("\n");
            start = i + 1;
            pos = start;
        }
    }
    pos = i;
    printf("Part %d: ", count);
    for (j = start; j < pos; j++)
        printf("%c", s[j]);
    printf("\n");
    return 0;
}
