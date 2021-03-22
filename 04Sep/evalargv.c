#include <stdio.h>
#include <stdlib.h>

// function which evaluates the command line arguments and returns the value
int evaluate(char** arr, int n)
{
    int i, sum = 0, sign = 1;
    for (i = 0; i < n; i++)
    {
        if (arr[i][0] == '-') // if negative sign is encountered in the expression
            sign = -1;
        else if (arr[i][0] == '+') // if addition operator is encountered in the expression
            sign = 1;
        else // number encountered in the expression
            sum += sign * atoi(arr[i]);
    }
    return sum;
}

// if expression begins with sign
int checkOperator(char** arr, int n)
{
    int i;
    for (i = 0; i < n; i += 2)
    {
        if (arr[i][0] != '-' && arr[i][0] != '+')
            return 0;
    }
    for (i = 1; i < n; i += 2)
    {
        if (arr[i][0] == '-' || arr[i][0] == '+')
            return 0;
    }
    return 1;
}

// if expression begins with number
int checkOperand(char** arr, int n)
{
    int i;
    for (i = 0; i < n; i += 2)
    {
        if (arr[i][0] == '-' || arr[i][0] == '+')
            return 0;
    }
    for (i = 1; i < n; i += 2)
    {
        if (arr[i][0] != '-' && arr[i][0] != '+')
            return 0;
    }
    return 1;
}

// function to check for validity of expression
int validate(char** arr, int n)
{
    if (arr[0][0] == '-' || arr[0][0] == '+')
        return checkOperator(arr, n);
    else
        return checkOperand(arr, n);
}

int main(int argc, char* argv[])
{
    argv++; // excluding ./a.out from the command line arguments
    argc--; // number of operators + operands in the expression
    // validate
    if (!validate(argv, argc))
    {
        printf("Invalid input\n");
        return 0;
    }

    // display
    printf("%d\n", evaluate(argv, argc));
    return 0;
}
