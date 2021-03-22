#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstnode // struct defining the node of the tree
{
    void* data;
    struct bstnode* lchild;
    struct bstnode* rchild;
    int lthread;
    int rthread;
};

typedef struct gbst // struct defining the tree
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void*, void*);
    struct bstnode* head;
}* genericBST;

// setting print function of the tree
int setPrintNodeFnGBST(genericBST gt, void (*pn)(void*))
{
    if (!pn)
        return 0;
    gt -> printNode = pn;
    return 1;
}

// setting compare function of the tree
int setCompareFnGBST(genericBST gt, int (*cf)(void*, void*))
{
    if (!cf)
        return 0;
    gt -> compareFn = cf;
    return 1;
}

// function to create a generic inorder threaded binary search tree
genericBST createTGBST(int dsize, int (*cfunction)(void*, void*), void (*printNode)(void*))
{
    genericBST gt = (genericBST)malloc(sizeof(struct gbst));
    gt -> dsize = dsize;
    if (!setPrintNodeFnGBST(gt, printNode))
    {
        printf("Error while setting print node function\n");
        return NULL;
    }
    if (!setCompareFnGBST(gt, cfunction))
    {
        printf("Error while setting compare function\n");
        return NULL;
    }
    struct bstnode* header = (struct bstnode*)malloc(sizeof(struct bstnode));
    header -> data = NULL;
    header -> lthread = 1;
    header -> lchild = header;
    header -> rthread = 0;
    header -> rchild = header;
    gt -> head = header;
    return gt;
}

// compare function to compare data of int type
int intcmp(void* d1, void* d2)
{
    int diff = *(int*) d1 - *(int*) d2;
    if (diff < 0)
        return -1;
    if (diff > 0)
        return 1;
    return 0;
}

// print function to display data of int type
void intprint(void* d)
{
    printf("%d\t", *((int*)d));
}

// function to search the tree for a node containing given data. Returns NULL if tree is empty. If node found, returns the node, else returns n parent of the given node for insertion
struct bstnode* searchTGBST(genericBST gt, void* d)
{
    if (gt -> head -> lthread) // tree is empty
        return NULL;
    struct bstnode* ptr = gt -> head -> lchild;
    while (1)
    {
        int cmpval = (gt -> compareFn)((ptr -> data), d);
        if (cmpval == 0) // node found
            return ptr;
        else if (cmpval == 1)
        {
            if (ptr -> lthread) // ptr is a leaf node
                return ptr;
            ptr = ptr -> lchild;
        }
        else
        {
            if (ptr -> rthread) // ptr is a leaf node
                return ptr;
            ptr = ptr -> rchild;
        }
    }
    return ptr;
}

// function to insert node in generic inorder threaded binary search tree
void insertNodeTGBST(genericBST gt, void* d)
{
    struct bstnode* node = (struct bstnode*)malloc(sizeof(struct bstnode));
    node -> data = malloc(gt -> dsize);
    node -> lchild = NULL;
    node -> rchild = NULL;
    node -> lthread = 1;
    node -> rthread = 1;
    memcpy(node -> data, d, gt -> dsize);
    if (gt -> head -> lthread) // if tree is empty, initialise root as left child of head
    {
        gt -> head -> lthread = 0;
        gt -> head -> lchild = node;
        node -> lchild = gt -> head;
        node -> rchild = gt -> head;
        return;
    }
    struct bstnode* ptr = searchTGBST(gt, d); // finds parent of the node to be inserted
    if ((gt -> compareFn)(ptr -> data, d) == -1) // node to be inserted to the right of the parent
    {
        node -> rchild = ptr -> rchild;
        ptr -> rchild = node;
        ptr -> rthread = 0;
        node -> lchild = ptr;
    }
    else // node to be inserted to the left of the parent
    {
        node -> lchild = ptr -> lchild;
        ptr -> lthread = 0;
        ptr -> lchild = node;
        node -> rchild = ptr;
    }
}

// function to find the inorder successor of a particular node
struct bstnode* inorderSuccessor(struct bstnode* node)
{
    if (node -> rthread)
        return node -> rchild;
    node = node -> rchild;
    while (!(node -> lthread))
        node = node -> lchild;
    return node;
}

// function to find the inorder predecessor of a particular node
struct bstnode* inorderPredecessor(struct bstnode* node)
{
    if (node -> lthread)
        return node -> lchild;
    node = node -> lchild;
    while (!(node -> rthread))
        node = node -> rchild;
    return node;
}


// function to traverse inorder threaded binary search tree
void inorderTraverse(genericBST gt)
{
    struct bstnode* temp = gt -> head;
    while (1)
    {
        temp = inorderSuccessor(temp);
        if (temp == gt -> head)
            break;
        (gt -> printNode)(temp -> data);
    }
}

// function that returns 0 if tree is empty, else returns 1 and traverses tree in inorder
int traverseTGBST(genericBST gt)
{
    if (gt -> head -> lthread)
        return 0;
    inorderTraverse(gt);
    printf("\n");
    return 1;
}

// function to delete node which has no children
struct bstnode* delNoChild(struct bstnode* root, struct bstnode* par, struct bstnode* ptr){
    if (ptr == root)
        root = NULL;
    else if (ptr == par -> lchild){
        par -> lthread = 1;
        par -> lchild = ptr -> lchild;
    }
    else {
        par -> rthread = 1;
        par -> rchild = ptr -> rchild;
    }
    free(ptr);
    return root;
}

// function to delete node which has exactly one child
struct bstnode* delOneChild(struct bstnode* root, struct bstnode* par, struct bstnode* ptr){
    struct bstnode* child;
    if (ptr -> rthread)
        child = ptr -> lchild;
    else
        child = ptr -> rchild;
    if (root == ptr)
        root = child;
    else if (ptr == par -> lchild)
        par -> lchild = child;
    else
        par -> rchild = child;
    struct bstnode* succ = inorderSuccessor(ptr);
    struct bstnode* pred = inorderPredecessor(ptr);
    if (ptr -> rthread)
        pred -> rchild = succ;
    else if (ptr -> lthread)
        succ -> lchild = pred;
    free(ptr);
    return root;
}

// function to delete node in a threaded binary search tree
struct bstnode* delNodeTGBST(genericBST gt, void* d){
    struct bstnode* root = gt -> head -> lchild;
    struct bstnode* par = gt -> head;
    struct bstnode* ptr = gt -> head -> lchild;
    int search = 0;
    while (ptr){
        if ((gt -> compareFn)(ptr -> data, d) == 0){
            search = 1;
            break;
        }
        par = ptr;
        if ((gt -> compareFn)(ptr -> data, d) == 1){
            if (!(ptr -> lthread))
                ptr = ptr -> lchild;
            else
                break;
        }
        else{
            if (!(ptr -> rthread))
                ptr = ptr -> rchild;
            else
                break;
        }
    }

    if (!search)
        return gt -> head -> lchild;
    if (ptr -> lthread && ptr -> rthread){
        return delNoChild(root, par, ptr);
    }
    if (ptr -> rthread || ptr -> lthread){
        return delOneChild(root, par, ptr);
    }
    struct bstnode* parsucc = ptr;
    struct bstnode* succ = ptr -> rchild;
    while (!(succ -> lthread)){
        parsucc = succ;
        succ = succ -> lchild;
    }
    memcpy(ptr -> data, succ -> data, gt -> dsize);
    if (succ -> lthread && succ -> rthread)
        return delNoChild(root, parsucc, succ);
    else
        return delOneChild(root, parsucc, succ);
    return root;
}

void deleteNodeTGBST(genericBST gt, void* d){
    if (gt -> head -> lthread)
        return;
    gt -> head -> lchild = delNodeTGBST(gt, d);
}

// main function to check if implemented functions are working
int main()
{
    genericBST gt = createTGBST(sizeof(int), &intcmp, &intprint);
    int arr[11] = {15, 7, 20, 23, 0, 19, 21, 45, 1, 4, 5};
    for (int i = 0; i < 11; i++)
        insertNodeTGBST(gt, &(arr[i]));
    traverseTGBST(gt);
    int a[4] = {21, 4, 7, 15};
    for (int i = 0; i < 4; i++)
        deleteNodeTGBST(gt, &(a[i]));
    traverseTGBST(gt);
    return 0;
}
