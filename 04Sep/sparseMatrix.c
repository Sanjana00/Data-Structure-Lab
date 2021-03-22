#include <stdio.h>
#include <stdlib.h>

struct element
{
    int data;
    int row;
    int col;
};

int addMatrix(struct element m1[], struct element m2[], struct element m3[])
{
    int row = m1[0].row, col = m1[0].col, s1 = m1[0].data, s2 = m2[0].data, i, j, k = 1;
    if (row != m2[0].row || col != m2[0].col) // sizes of the two matrices to be added are not the same
        return 0;
    // the dimensions of the added matrix are the same as the dimensions of the two matrices to be added
    m3[0].row = row;
    m3[0].col = col;
    // adding non zero elements whose positions are in first matrix and common to both matrices
    for (i = 1; i < s1; i++) // loop running through each non zero element in first matrix
    {
        m3[k].row = m1[i].row;
        m3[k].col = m1[i].col;
        m3[k].data = m1[i].data;
        for (j = 1; j < s2; j++) // loop running through each non zero element in second matrix
        {
            if (m1[i].row == m2[j].row && m1[i].col == m2[j].col) // check if non zero elements exist at the same position in both matrices
            {
                m3[k].data += m2[j].data;
                m2[j].data = 0;
            }
        }
        k++;
    }
    // adding non zero elements present in positions only in second matrix
    for (i = 1; i < s2; i++) // loop running through non zero elements of second matrix
    {
        if (m2[i].data == 0) // element has already been added
            continue;
        m3[k].data = m2[i].data;
        m3[k].row = m2[i].row;
        m3[k].col = m2[i].col;
        k++;
    }
    m3[0].data = k; // number of non zero elements in added matrix
    return 1;
}

int main()
{
    int m, n, x, i, j, ele, k = 1;
    // taking user input for first matrix
    printf("Enter number of rows: ");
    scanf("%d", &m);
    printf("Enter number of columns: ");
    scanf("%d", &n);
    x = (m * n) / 2 + 1;
    struct element m1[x], m3[m * n];
    int arr[m][n];

    m1[0].row = m;
    m1[0].col = n;

    printf("Enter elements of first matrix, m1 of size %d x %d (total number of elements: %d): ", m, n, m * n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &ele);
            if (ele == 0)
                continue;
            m1[k].data = ele;
            m1[k].row = i;
            m1[k].col = j;
            k++;
        }
    }
    m1[0].data = k;
    k = 1;
    // taking user input for second matrix
    printf("Enter number of rows: ");
    scanf("%d", &m);
    printf("Enter number of columns: ");
    scanf("%d", &n);
    x = (m * n) / 2 + 1;
    struct element m2[x];
    m2[0].row = m;
    m2[0].col = n;

    printf("Enter elements of second matrix, m2 of size %d x %d (total number of elements: %d): ", m, n, m * n);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &ele);
            if (ele == 0)
                continue;
            m2[k].data = ele;
            m2[k].row = i;
            m2[k].col = j;
            k++;
        }
    }
    m2[0].data = k;

    if (!addMatrix(m1, m2, m3)) // dimensions of both matrices are not the same
    {
        printf("Matrices could not be added\n");
        return 0;
    }

    // initialising default values of added matrix to 0
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            arr[i][j] = 0;

    // storing values of non zero elements in matrix
    for (i = 0; i < m3[0].data; i++)
        arr[m3[i].row][m3[i].col] = m3[i].data;

    // displaying added matrix
    printf("\nResult:\n\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d\t", arr[i][j]);
        printf("\n");
    }
    return 0;
}
