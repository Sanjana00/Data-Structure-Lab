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

// creating struct gqueue to implement generic queue using linked list
struct gqueue
{
    int dsize; // size of data in each node
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

gqueue createGQueue(int dsize) // function to create and initialise a generic queue struct pointer
{
    gqueue q = (gqueue)malloc(sizeof(struct gqueue));
    q -> dsize = dsize;
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

int main()
{
    // main function assumes data in the generic queue is of integer type to demonstrate the working of the functions
    int ch, n, d = sizeof(int);
    gqueue gq = createGQueue(d);
    do
    {
        // menu
        printf("Enter choice:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Quit program\n\n");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: // performing enqueue
                printf("Enter integer: ");
                scanf("%d", &n);
                enGQueue(gq, &n);
                break;
            case 2: // performing dequeue
                if (!deGQueue(gq, &n)) // queue is empty
                    printf("Queue is empty\n");
                else
                    printf("Dequeued element is: %d\n", n);
                break;
            case 3: // displaying queue
                if (isGQueueEmpty(gq)) // queue is empty, nothing to display
                    printf("Queue is empty\n");
                else
                {
                    printf("Displaying queue: ");
                    node* temp = gq -> front;
                    while (temp != NULL)
                    {
                        printf("%d\t", *(int*)temp -> data);
                        temp = temp -> next;
                    }
                    printf("\n");
                }
                break;
            case 4: // exiting menu
                printf("Quitting program\n");
                break;
            default:
                printf("Invalid input\n");
        }
        printf("\n");
    } while (ch != 4);
    freeGQueue(gq); // freeing queue
    return 0;
}
