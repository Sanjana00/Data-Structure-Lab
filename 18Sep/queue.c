#include <stdio.h>
#include <stdlib.h>

// defining queue data type
struct queue{
    int size; // size of queue
    int front; // index of first element of queue
    int rear; // index of last element of queue
    int *data; // elements in queue
};

typedef struct queue* queue;

int isIntegerQueueFull(queue q) // returns if queue is full
{
    return q -> size - 1 == q -> rear;
}

int isIntegerQueueEmpty(queue q) // returns if queue is empty
{
    return q -> front == -1;
}

queue createIntegerQueue(int queueSize) // creates an instance of a queue and returns its address if successful, else NULL
{
    queue q = (queue)malloc(sizeof(struct queue));
    if (q == NULL)
        return NULL;
    q -> size = queueSize;
    q -> front = -1;
    q -> rear = -1;
    q -> data = (int*)malloc(queueSize * sizeof(int));
    if (q -> data == NULL)
        return NULL;
    return q;
}

int enqueueInteger(queue q, int d) // enqueues data d in queue q and returns 1 if successful, else 0
{
    if (isIntegerQueueFull(q) || q -> size < 1)
        return 0;
    if (isIntegerQueueEmpty(q))
        q -> front++;
    q -> data[++(q -> rear)] = d;
    return 1;
}

int dequeueInteger(queue q, int* dp) // dequeues queue q and returns 1 if successful, else 0
{
    if (isIntegerQueueEmpty(q) || q -> size < 1)
        return 0;
    *dp = q -> data[(q -> front)++];
    if (q -> front > q -> rear)
    {
        q -> front = -1;
        q -> rear = -1;
    }
    return 1;
}

int freeQueueInteger(queue q) // frees queue and returns 1 if successful, else 0
{
    if (q -> size < 1)
        return 0;
    free(q -> data);
    return 1;
}

int main()
{
    int ch, n;
    // creating queue
    printf("Enter size of the desired queue: ");
    scanf("%d", &n);
    queue q = createIntegerQueue(n);
    do
    {
        // menu
        printf("Enter choice:\n1. Enqueue Integer\n2. Dequeue Integer\n3. Display\n4. Quit program\n\n");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1: // enqueue data
                printf("Enter integer: ");
                scanf("%d", &n);
                if (!enqueueInteger(q, n))
                    printf("Enqueue operation could not be performed\n");
                break;
            case 2: // dequeue element
                if (!dequeueInteger(q, &n))
                    printf("Dequeue operation could not be performed\n");
                else
                    printf("%d has been dequeued\n", n);
                break;
            case 3: // display queue
                if (isIntegerQueueEmpty(q)) // queue is empty
                {
                    printf("Queue is empty\n");
                    break;
                }
                printf("Displaying queue:\n\n");
                for (int i = q -> front; i <= q -> rear; i++)
                    printf("%d\t", q -> data[i]);
                printf("\n");
                break;
            case 4: // quitting program
                printf("Quitting program\n");
                break;
            default: // invalid input
                printf("Invalid input!\n");
        }
        printf("\n");
    } while (ch != 4); // condition for quitting program
    freeQueueInteger(q); // free space allotted for queue
    return 0;
}
