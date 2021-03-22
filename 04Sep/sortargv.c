#include <stdio.h>
#include <string.h>

// selection sort algorithm to sort array of strings in ascending order
void sortStrings(int n, char** arr)
{
    int i, j, small_pos;
    for (i = 0; i < n - 1; i++)
    {
        small_pos = i;
        for (j = i + 1; j < n; j++)
            if (strcmp(arr[small_pos], arr[j]) > 0)
            {
                small_pos = j;
            }
        char temp[100];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[small_pos]);
        strcpy(arr[small_pos], temp);
    }
}

int main(int argc, char* argv[])
{
    argv++; // excluding ./a.out from the command line arguments
    // sorting argv[] in ascending order
    sortStrings(argc - 1, argv);
    // display sorted command line arguments
    for (int i = 0; i < argc - 1; i++)
        printf("%s ", argv[i]);
    printf("\n");
    return 0;
}
