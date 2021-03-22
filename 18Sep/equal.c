#include <stdio.h>

int equal(char* s)
{
    // function to check if string containing only 'a' and 'b' have the same number of 'a' and 'b'. Return 1 if yes, else 0
    char ch;
    int i, top = 0;

    for (i = 0; s[i] != '\0'; i++); // finding length of the string

    char stack[i]; // implementing stack using a char array
    for (i = 0; s[i] != '\0'; i++)
    {
        ch = s[i];
        if (top == 0) // stack is empty
        {
            stack[top++] = ch; // push to stack
            continue;
        }
        if (ch == stack[top - 1]) // current char does not nullify (a nullifies b and vice versa)
        {
            stack[top++] = ch; // push to stack
            continue;
        }
        top--; // pop from stack
    }
    return top == 0; // return if stack is empty
}

// main
int main()
{
    char s[20];
    // taking string user input
    printf("Enter string containing only a and b: ");
    scanf("%s", s);
    if (equal(s)) // if input has equal number of 'a' and 'b'
        printf("The string %s has equal number of 'a' and 'b'\n", s);
    else
        printf("The string %s has unequal number of 'a' and 'b'\n", s);
    return 0;
}
