#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct student {
    char name[20];
    int m;
    int* allot;
};

// defining gqueue data type using struct gqueue pointer

struct gqueue {
    int size;
    int dsize;
    int front;
    int rear;
    void* data;
};

typedef struct gqueue* gqueue;

int freeGQueue(gqueue q) // frees gqueue and returns 1 if successful, else 0
{
    if (q == NULL)
        return 0;
    free(q -> data);
    free(q);
    return 1;
}

int isGQueueFull(gqueue q) // returns if gqueue is full
{
    return q -> rear == (q -> size) - 1;
}

int isGQueueEmpty(gqueue q) // returns if gqueue is empty
{
    return q -> front == -1;
}

gqueue createGQueue(int queueSize, int dsize) // creates an instance of gqueue and returns it if successful, else returns NULL
{
    gqueue gq = (gqueue)malloc(sizeof(struct gqueue));
    if (gq == NULL) // memory could not be allocated to gqueue instance
        return NULL;
    gq -> size = queueSize;
    gq -> dsize = dsize;
    gq -> front = -1;
    gq -> rear = -1;
    gq -> data = malloc(queueSize * dsize);
    if (gq -> data == NULL) // memory could not be allocated to data of gqueue instance
        return NULL;
    return gq;
}

int enGQueue(gqueue q, void* dp) // enqueues data stored at address dp in gqueue q and returns 1 if successful, else 0
{
    if (isGQueueFull(q))
    {
        printf("Queue is full\n");
        return 0;
    }
    if (isGQueueEmpty(q)) // front needs to be updated as well
        q -> front = 0;
    (q -> rear)++;
    memcpy((void*)(q -> data + (q -> rear) * (q -> dsize)), dp, q -> dsize);
    return 1;
}

int deGQueue(gqueue q, void* dp) // dequeues gqueue q and returns 1 if successful, else 0
{
    if (isGQueueEmpty(q)) // cannot be dequeued if queue is empty
    {
        printf("Queue is empty\n");
        return 0;
    }
    memcpy(dp, (void*)(q -> data + (q -> front) * (q -> dsize)), q -> dsize);
    (q -> front)++;
    if (q -> front > q -> rear) // queue is empty after dequeue
    {
        q -> front = -1;
        q -> rear = -1;
    }
    return 1;
}

struct student inputStudent(int n) // function to input the details of the student
{
    getchar();
    struct student s;
    printf("Enter name of student: ");
    scanf("%[^\n]", s.name);
    int m, i;
    do
    {
        printf("Enter number of preferences: ");
        scanf("%d", &m);
        if (m > n || m < 1)
            printf("Invalid input\n");
    } while (m > n || m < 1);
    s.allot = (int *)malloc(m * sizeof(int));
    s.m = m;
    for (i = 0; i < m; i++)
    {
        printf("Enter preference (number from 1 to %d): ", m);
        scanf("%d", &s.allot[i]);
    }
    return s;
}

void displayStudent(struct student s) // function to display the details of the student
{
    printf("Name: %s\nPreferences:\n", s.name);
    int i;
    for (i = 0; i < s.m; i++)
    {
        printf("%d. %d\n", i + 1, s.allot[i]);
    }
    printf("\n");
}

int allotStudent(struct student s, int* group, int size) // function to allot students to their professors of choice
{
    int i, pref;
    for (i = 0; i < s.m; i++)
    {
        pref = s.allot[i];
        if (group[pref - 1] < size) // if the student's preference is available
        {
            group[pref - 1]++;
            return pref;
        }
    }
    return 0; // none of the preferences have slots left
}

int main() // main to demonstrate the functions are working
{
    int pref, i, ch, n, m, d = sizeof(struct student);
    int* groups;
    struct student s;
    // creating gqueue
    printf("Enter number of students: ");
    scanf("%d", &n);
    printf("Enter number of teachers: ");
    scanf("%d", &m);
    int size = (int)ceil((float)n / (float)m); // maximum size allowed in a group
    printf("Maximum size of group: %d\n", size);
    groups = (int*)calloc(m, sizeof(int)); 
    gqueue gq = createGQueue(n, d);
    for (i = 0; i < n; i++)
    {
        s = inputStudent(m);
        if (enGQueue(gq, &s) == 0)
            printf("Enqueue unsuccessful\n");
    }
    for (i = 0; i < n; i++) // alloting teacher to each student
    {
        if (deGQueue(gq, &s) == 0)
        {
            printf("Dequeue unsuccessful\n");
            break;
        }
        printf("\n");
        displayStudent(s);
        if ((pref = allotStudent(s, groups, size)) == 0)
            printf("%s: Unallotted\n", s.name);
        else
            printf("%s: Allotted %d\n", s.name, pref);
    }
    freeGQueue(gq); // free space allotted for gqueue
    return 0;
}
