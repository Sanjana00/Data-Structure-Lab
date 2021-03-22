#include <stdio.h>
#include <stdlib.h>

// function to insert new element to the max heap
void heapInsert(int arr[], int ele, int ptr){
    int par;
    while (ptr > 1){ // while parent of the pointer exists (pointer is not root)
        par = ptr / 2; // finding parent of the current element
        if (ele <= arr[par]){ // if element to be inserted is in order
            arr[ptr] = ele;
            return;
        }
        arr[ptr] = arr[par]; // element is greated than its parent -> parent is lowered
        ptr = par;
    }
    arr[ptr] = ele;
}

// function to delete largest element from max heap
int heapDelete(int arr[], int n){
    if (n < 1) // heap is empty
        return -1;
    int item = arr[1], last = arr[n], ptr = 1, left = 2, right = 3;
    n = n - 1;
    arr[ptr] = last; // last element is brought to root
    while (right <= n){
        if (last >= arr[left] && last >= arr[right]){ // element is now in place
            arr[ptr] = last;
            return item;
        }
        if (arr[left] >= arr[right]){ // element is smaller than child and left child is greater than right child
            arr[ptr] = arr[left];
            ptr = left;
        }
        else{ // right child is greater than left child
            arr[ptr] = arr[right];
            ptr = right;
        }
        // finding left and right children of pointer
        left = ptr * 2;
        right = ptr * 2 + 1;
    }
    if (left == n){ // if right child does not exist
        if (last < arr[left]){ // if left child is greater than parent, swap
            arr[ptr] = arr[left];
            ptr = left;
        }
        arr[ptr] = last;
    }
    return item; // return deleted item
}

// function to display priority queue
void display(int arr[], int ptr){
    printf("Displaying queue:\n");
    for (int i = 1; i < ptr; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

// main function
int main(){
    int n, ch, out, x, ptr = 1;
    printf("Enter the size of the queue: "); // input size of priority queue
    scanf("%d", &n);
    int arr[n + 1];
    arr[0] = n;
    while (1){
        printf("Toss coin? (1 = yes, 0 = no): "); // toss coin
        scanf("%d", &ch);
        if (!ch){ // quit program
            printf("Quitting program\n");
            break;
        }
        out = rand() % 2; // outcome of coin toss
        printf("Outcome (1 = head, 0 = tail) : %d\n", out);
        if (out){ // coin tossed to heads - insert random element
            if (ptr > n){ // queue is full
                printf("Queue is full\n");
                continue;
            }
            x = rand() % 10;
            printf("Item to be inserted: %d\n", x);
            heapInsert(arr, x, ptr);
            ptr++;
        }
        else{ // coin tossed to tail - delete element with highest priority (maximum value)
            if (ptr == 1){ // queue is empty
                printf("Queue is empty\n");
                continue;
            }
            x = heapDelete(arr, ptr - 1);
            printf("Evicted item: %d\n", x);
            ptr--;
        }
        display(arr, ptr); // display queue after each toss
    }
    return 0;
}
