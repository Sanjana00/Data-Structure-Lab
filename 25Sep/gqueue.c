#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
    char name[20];
    long int roll;
    char email[50];
    char telephone[11];
    char address[4][20];
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

struct student inputStudent()
{
    struct student s;
    printf("Enter name of student: ");
    scanf("%[^\n]", s.name);
    printf("Enter roll number: ");
    scanf("%ld", &s.roll);
    printf("Enter email: ");
    scanf("%s", s.email);
    printf("Enter phone number: ");
    scanf("%s", s.telephone);
    return s;
}

void displayStudent(struct student s)
{
    printf("Name: %s\nRoll: %ld\nEmail: %s\nTelephone: %s\n", s.name, s.roll, s.email, s.telephone);
}

int main() // main to demonstrate the functions are working
{
    int ch, n, d = sizeof(struct student);
    struct student s;
    // creating gqueue
    printf("Enter size of the desired queue: ");
    scanf("%d", &n);
    gqueue gq = createGQueue(n, d);
    do
    {
        // menu
        printf("Enter choice:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Quit program\n\n");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1: // enqueue data in the form of struct student
                getchar();
                printf("Enter struct details:\n");
                s = inputStudent();
                if (!enGQueue(gq, &s))
                    printf("Enqeue operation could not be performed\n");
                break;
            case 2: // dequeue data
                if (!deGQueue(gq, &s))
                    printf("Dequeue operation could not be performed\n");
                else
                {
                    printf("Dequeue details:\n");
                    displayStudent(s);
                }
                break;
            case 3: // display gqueue
                if (isGQueueEmpty(gq)) // gqueue is empty
                {
                    printf("Queue is empty\n");
                    break;
                }
                printf("Displaying queue:\n\n");
                for (int i = gq -> front; i <= gq -> rear; i++)
                {
                    printf("\n");
                    displayStudent(*(struct student*)((gq -> data) + (i * d)));
                    printf("\n");
                }
                break;
            case 4: // exit program
                printf("Quitting program\n");
                break;
            default: // invalid input
                printf("Invalid input\n");
        }
        printf("\n");
    } while (ch != 4); // exiting program
    freeGQueue(gq); // free space allotted for gqueue
    return 0;
}
