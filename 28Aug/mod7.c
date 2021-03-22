#include <stdio.h>

int main()
{
    printf("How many integers? ");
    int n, i, k = 0, d;
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter an integer: ");
        scanf("%d", &d);
        if (d % 7 == 0)
        {
            arr[k++] = d;
        }
    }
    for (k = k - 1; k >= 0; k --)
        printf("%d  ", arr[k]);
    printf("\n");
    return 0;
}
