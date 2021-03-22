#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to store details of a student (first name, last name and roll number)
struct student
{
    char fname[20]; // stores first name of student
    char surname[20]; // stores surname of student
    int roll; // stores roll number of student
};

// comparing function for qsort on roll number
int intcompare(const void* a, const void* b)
{
    return (((struct student *)a) -> roll) - (((struct student *)b) -> roll);
}

// comparing function for qsort on fname
int fnamecompare(const void* a, const void* b)
{
    return strcmp(((struct student* )a) -> fname, ((struct student* )b) -> fname);
}

// comparing function for qsort on surname
int surnamecompare(const void* a, const void* b)
{
    return strcmp(((struct student* )a) -> surname, ((struct student* )b) -> surname);
}

// function to sort students in ascending order according to first name, surname or roll number according to choice of user
void sortStudent(struct student* d, int n, int f)
{
    if (f == 1) // sorting on basis of first name
        qsort(d, n, sizeof(struct student), fnamecompare);
    else if (f == 2) // sorting on basis of surname
        qsort(d, n, sizeof(struct student), surnamecompare);
    else // sorting on basis of roll number
        qsort(d, n, sizeof(struct student), intcompare);
}

int main()
{
    // taking user input
    printf("Enter the number of students: ");
    int n, i, f;
    scanf("%d", &n);
    struct student ss[n];
    printf("Enter details:\n");
    for (i = 0; i < n; i++)
    {
        getchar();
        printf("Enter first name: ");
        scanf("%[^\n]", ss[i].fname);
        getchar();
        printf("Enter surname: ");
        scanf("%[^\n]", ss[i].surname);
        getchar();
        printf("Enter roll number: ");
        scanf("%d", &ss[i].roll);
    }
    printf("Enter sorting critera [1 for fname, 2 for surname or 3 for roll]: ");
    scanf("%d", &f);
    if (f < 1 || f > 3)
    {
        printf("Invalid input, must be either 1, 2 or 3\n");
        return 0;
    }
    // sorting students in ascending order on the basis of criteria mentioned
    sortStudent(ss, n, f);
    // display
    printf("Name\t\tRoll\n");
    for (i = 0; i < n; i++)
    {
        printf("%s %s\t%d\n", ss[i].fname, ss[i].surname, ss[i].roll);
    }
    return 0;
}
