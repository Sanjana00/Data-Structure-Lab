#include <stdio.h>

int main()
{
    int freq[26] = {};
    char s1[100], s2[100];
    // taking user input for two strings
    printf("Enter the 1st string: ");
    scanf("%s", s1);
    printf("Enter the 2nd string: ");
    scanf("%s", s2);
    int i, frequency, max = 0;
    char common;
    // for loop to read each character s1 and store the frequency of their occurrence in s1
    for (i = 0; s1[i] != '\0'; i++)
    {
        if (s1[i] >= 'A' && s1[i] <= 'Z') // if character is an uppercase English letter
            freq[s1[i] - 'A']++;
        else if (s1[i] >= 'a' && s1[i] <= 'z') // if character is a lowercase English letter
            freq[s1[i] - 'a']++;
    }
    // for loop to access each character of s2 and find their maximum frequency of occurrence in s1
    for (i = 0; s2[i] != '\0'; i++)
    {
        if (s2[i] >= 'A' && s2[i] <= 'Z') // converting uppercase English letters to lowercase
            s2[i] = s2[i] - 'A' + 'a';
        if (s2[i] >= 'a' && s2[i] <= 'z') // if character is an alphabet
        {
            frequency = freq[s2[i] - 'a'];
            if (frequency > max) // if current alphabet occurs more times in s1 than any other alphabet so far
            {
                common = s2[i];
                max = frequency;
            }
        }
    }
    // display
    printf("\'%c\' of \"%s\" is occurring %d times in \"%s\"\n", common, s2, max, s1);
    return 0;
}
