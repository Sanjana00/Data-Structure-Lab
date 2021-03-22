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
struct gstack
{
    int dsize; // size of data in each node
    int (*printFn)(void*);
    node* top;
};

typedef struct gstack* gstack;

int displayInt(void* x)
{
    printf("%d\t", *(int*)x);
    return 0;
}

// function to free memory allocated to generic queue
int freeGStack(gstack s)
{
    if (s -> top == NULL) // queue is empty
    {
        free(s);
        return 0;
    }
    node* temp = s -> top;
    node* del = s -> top;
    while (temp != NULL) // free each node and its data in the linked list
    {
        temp = temp -> next;
        free(del -> data);
        free(del);
        del = temp;
    }
    free(s);
    return 0;
}

int isGStackEmpty(gstack s) // function returns if the queue is empty
{
    return s -> top == NULL;
}

gstack createGStack(int dsize, int (*printFn)(void*)) // function to create and initialise a generic queue struct pointer
{
    gstack s = (gstack)malloc(sizeof(struct gstack));
    s -> dsize = dsize;
    if (printFn)
        s -> printFn = printFn;
    s -> top = NULL;
    
    return s;
}

void push(gstack s, void* dp) // function to perform enqueue operation on generic queue
{
    // allocating memory for new node
    node* n = (node*)malloc(sizeof(node));
    n -> data = malloc(s -> dsize);
    n -> next = NULL;
    memcpy(n -> data, dp, s -> dsize);
    if (isGStackEmpty(s)) // if queue is empty, front is equal to rear
    {
        s -> top = n;
    }
    else // enqueue operation is performed at the rear of the queue
    {
        n -> next = s -> top;
        s -> top = n;
    }
}

int pop(gstack s, void* dp) // function to perform dequeue operation on generic queue -> returns 0 if dequeue could not be performed, else 1
{
    if (isGStackEmpty(s)) // queue is empty
        return 0;
    memcpy(dp, s -> top -> data, s -> dsize); // copying dequeued data 
    node* temp = s -> top;
    s -> top = s -> top -> next; // front is moved on dequeue
    // freeing dequeued node
    free(temp -> data);
    free(temp);
    return 1;
}

void printGS(gstack s)
{
    if (isGStackEmpty(s))
    {
        printf("Stack is empty\n");
        return;
    }
    printf("\nDisplaying stack:\n");
    node* temp = s -> top;
    while (temp)
    {
        (s -> printFn)(temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}

int main()
{
    int ch, d = sizeof(int), n;
    gstack gs = createGStack(d, &displayInt);
    do
    {
        // menu
        printf("Enter choice:\n1. Push\n2. Pop\n3. Display\n4. Quit menu\n\n");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("Enter a number: ");
                scanf("%d", &n);
                push(gs, &n);
                break;
            case 2: 
                if (!pop(gs, &n))
                    printf("Stack is empty\n");
                else
                    printf("Popped element is: %d\n", n);
                break;
            case 3: // displaying stack
                printGS(gs);
                break;
            case 4: // exiting menu
                printf("Quitting menu\n");
                break;
            default:
                printf("Invalid input\n");
        }
        printf("\n");
    } while (ch != 4);
    freeGStack(gs);
    return 0;
}
