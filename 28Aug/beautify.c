#include <stdio.h>

int main()
{
    // taking user input for line and width of output
    printf("Enter the line: ");
    char s[100];
    scanf("%[^\n]", s);
    printf("Length of the output line: ");
    int width;
    scanf("%d", &width);
    int i, j, k = 0, l = 0, x = 0, end, nowords = 0;
    int wlen[50], lines[50]; 
    // loop to find length of each word and number of words in each line of output
    for (i = 0; s[i] != '\0'; i++)
    {
        l = 0;
        for(j = i; j < i + width + 1; j++)
        {
            if (s[j] == ' ' || s[j] == '\0') // end of a word reached
            {
                nowords++;
                end = j;
                wlen[k++] = l;
                l = 0;
                if (s[j] == '\0')
                {
                    end = j - 1;
                    break;
                }
            }
            else
            {
                l++;
            }
        }
        if (nowords == 0) // if length of a word exceeds the width of the output, the word is printed anyway in one line
        {
            nowords = 1;
            for (j = i; s[j] != ' ' && s[j] != '\0'; j++);
            end = j;
            wlen[k++] = end - i;
        }
        lines[x++] = nowords;
        nowords = 0;
        i = end; // reinitialising the value of i to denote start of the next line
    }

    int begin = 0, space, rem, f = 0;
    end = 0;
    // displaying output
    for(i = 0; i < x; i++)
    {
        l = 0;
        nowords = lines[i];
        for(j = end; j < end + nowords; j++)
            l += wlen[j]; // length of line excluding spaces
        end = j;
        if (nowords != 1) // no need to print spaces if line has only one word, else spaces are evenly distributed
        {
            space = (width - nowords + 1 - l) / (nowords - 1);
            rem = (width - nowords + 1 - l) % (nowords - 1);
        }
        k = begin;
        begin += l + nowords;
        f = 0;
        while (nowords > 0)
        {
            if (nowords == 1) // no need to print spaces if only one word is to be printed
            {
                space = 0;
                rem = 0;
            }
            if (s[k] == ' ' || s[k] == '\0') // printing each word
            {
                if (nowords == 1)
                    break;
                printf(" ");
                if (f == 0) // printing extra spaces required after first word
                {
                    for (int m = 0; m < (space + rem); m++)
                        printf(" ");
                    f = 1;
                }
                else // printing spaces between words
                {
                    for (int m = 0; m < space; m++)
                        printf(" ");
                }
                nowords--;
                if (s[k] == '\0') // end of line reached
                    break;
            }
            else // printing current character of word
            {
                printf("%c", s[k]);
            }
            k++;
        }
        printf("\n");
    }
    return 0;
}
