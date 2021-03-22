#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creating struct node for node of linked list
struct node
{
    void* data;
    struct node* next;
};

typedef struct node node;

struct student
{
    char fname[15];
    char lname[15];
    int roll;
};

struct student inputStudent()
{
    getchar();
    struct student s;
    printf("Enter name: ");
    scanf("%s%s", s.fname, s.lname);
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    return s;
}

int displayStudent(void* data)
{
    struct student s = *(struct student*)data;
    printf("\nName: %s %s\nRoll: %d\n", s.fname, s.lname, s.roll);
}

int displayInt(void* data)
{
    printf("%d\n", *(int*)data);
}

int displayFloat(void* data)
{
    printf("%f\n", *(float*)data);
}

// creating struct gqueue to implement generic queue using linked list
struct gqueue
{
    int dsize; // size of data in each node
    int (*printFn)(void*);
    node* front;
    node* rear;
};

typedef struct gqueue* gqueue;

// function to free memory allocated to generic queue
int freeGQueue(gqueue q)
{
    if (q -> front == NULL) // queue is empty
    {
        free(q);
        return 0;
    }
    node* temp = q -> front;
    node* del = q -> front;
    while (temp != NULL) // free each node and its data in the linked list
    {
        temp = temp -> next;
        free(del -> data);
        free(del);
        del = temp;
    }
    free(q);
    return 0;
}

int isGQueueEmpty(gqueue q) // function returns if the queue is empty
{
    return q -> front == NULL;
}

gqueue createGQueue(int dsize, int (*printFn)(void*)) // function to create and initialise a generic queue struct pointer
{
    gqueue q = (gqueue)malloc(sizeof(struct gqueue));
    q -> dsize = dsize;
    if (printFn)
        q -> printFn = *printFn;
    q -> front = NULL;
    q -> rear = NULL;
    
    return q;
}

void enGQueue(gqueue q, void* dp) // function to perform enqueue operation on generic queue
{
    // allocating memory for new node
    node* n = (node*)malloc(sizeof(node));
    n -> data = malloc(q -> dsize);
    n -> next = NULL;
    memcpy(n -> data, dp, q -> dsize);
    if (isGQueueEmpty(q)) // if queue is empty, front is equal to rear
    {
        q -> front = n;
        q -> rear = n;
    }
    else // enqueue operation is performed at the rear of the queue
    {
        q -> rear -> next = n;
        q -> rear = q -> rear -> next;
    }
}

int deGQueue(gqueue q, void* dp) // function to perform dequeue operation on generic queue -> returns 0 if dequeue could not be performed, else 1
{
    if (isGQueueEmpty(q)) // queue is empty
        return 0;
    memcpy(dp, q -> front -> data, q -> dsize); // copying dequeued data 
    if (q -> front == q -> rear) // queue becomes empty on performing dequeue
    {
        q -> front = NULL;
        q -> rear = NULL;
        return 1;
    }
    node* temp = q -> front;
    q -> front = q -> front -> next; // front is moved on dequeue
    // freeing dequeued node
    free(temp -> data);
    free(temp);
    return 1;
}

void exportGQ(gqueue g, FILE* fp)
{
    if (isGQueueEmpty(g))
    {
        printf("Queue is empty\n");
        fp = NULL;
        return;
    }
    if (!fp)
    {
        printf("File cannot be opened\n");
        return;
    }
    node* temp = g -> front;
    while (temp)
    {
        if (!(fprintf(fp, "%s %s %d%s", ((struct student*)(temp -> data)) -> fname, ((struct student*)(temp -> data)) -> lname, ((struct student*)(temp -> data)) -> roll, temp -> next ? "\n" : "")))
        {
            printf("Could not write to file\n");
            return;
        }
        temp = temp -> next;
    }
    printf("File export checkpoint reached\n");
}

gqueue importGQ(FILE* fp)
{
    if (!fp)
    {
        printf("File could not be opened\n");
        return NULL;
    }
    gqueue q = createGQueue(sizeof(struct student), displayStudent);
    struct student s;
    while(!feof(fp))
    {
        fscanf(fp, "%s %s %d", s.fname, s.lname, &s.roll);
        enGQueue(q, &s);
    }
    printf("File import checkpoint reached\n");
    return q;
}

void printGQ(gqueue g)
{
    if (isGQueueEmpty(g))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("\nDisplaying queue:\n");
    node* temp = g -> front;
    while (temp)
    {
        (g -> printFn)(temp -> data);
        temp = temp -> next;
    }
}

int main()
{
    int ch, d = sizeof(struct student);
    struct student s;
    gqueue gq = createGQueue(d, displayStudent);
    do
    {
        // menu
        printf("Enter choice:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Quit menu\n\n");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: // performing enqueue
                printf("\n");
                s = inputStudent();
                enGQueue(gq, &s);
                break;
            case 2: // performing dequeue
                if (!deGQueue(gq, &s)) // queue is empty
                    printf("Queue is empty\n");
                else
                {
                    printf("Dequeued element is:\n");
                    displayStudent((void*)&s);
                }
                break;
            case 3: // displaying queue
                printGQ(gq);
                break;
            case 4: // exiting menu
                printf("Quitting menu\n");
                break;
            default:
                printf("Invalid input\n");
        }
        printf("\n");
    } while (ch != 4);
    FILE *fex = fopen("queue.txt", "w");
    exportGQ(gq, fex);
    fclose(fex);
    freeGQueue(gq); // freeing queue
    FILE* fim = fopen("queue.txt", "r");
    gqueue q = importGQ(fim);
    fclose(fim);
    printGQ(q);
    freeGQueue(q);
    return 0;
}
