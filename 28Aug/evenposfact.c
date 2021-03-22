#include <stdio.h>

void factors(int n)
{
    int count = 1, i, k = 1;
    int f[n];
    f[0] = 2;
    for (i = 3; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            count++;
            f[k++] = i;
        }
    }
    if (n == 2)
        return;
    printf("%d has %d factors: ", n, count);
    for (i = 0; i < k - 1; i++)
        printf("%d, ", f[i]);
    printf("%d\n", f[i]);
}

int main()
{
    printf("How many integers? ");
    int n, i, k = 0, d;
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &d);
        if (d % 2 == 0 && d > 0)
        {
            arr[k++] = d;
        }
    }
    for (k = k - 1; k >= 0; k --)
        factors(arr[k]);
    printf("\n");
    return 0;
}
