void insertHeap(int heap[], int ptr, int data){
    int par;
    while (ptr > 1){
        par = ptr / 2;
        if (data <= heap[par]){
            heap[ptr] = data;
            return;
        }
        heap[ptr] = heap[par];
        ptr = par;
    }
    heap[ptr] = data;
}

int deleteHeap(int heap[], int size){
    if (size < 1)
        return -1;
    int ele = heap[1], last = heap[n], ptr = 1, left = 2, right = 3;
    n--;
    while (right <= n){
        if (last >= heap[left] && last >= heap[right]){
            heap[ptr] = last;
            return ele;
        }
        if (heap[left] > heap[right]){
            heap[ptr] = heap[left];
            ptr = left;
        }
        else{
            heap[ptr] = heap[right];
            ptr = right;
        }
        left = ptr * 2;
        right = ptr * 2 + 1;
    }
    if (left == n){
        if (heap[left] > heap[ptr]){
            heap[ptr] = heap[left];
            ptr = left;
        }
        heap[ptr] = last;
    }
    return ele;
}
