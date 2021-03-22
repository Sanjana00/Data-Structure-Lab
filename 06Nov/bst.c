#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstnode
{
    void* data;
    struct bstnode* lchild;
    struct bstnode* rchild;
};

typedef struct gbst
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void*, void*);
    struct bstnode* root;
}* genericBST;

genericBST createGBST(int dsize, int (*cfunction)(void*, void*), void (*printNode)(void*))
{
    genericBST gt = (genericBST)malloc(sizeof(struct gbst));
    gt -> dsize = dsize;
    gt -> printNode = printNode;
    gt -> compareFn = cfunction;
    gt -> root = NULL;
    return gt;
}

int intcmp(void* d1, void* d2)
{
    int diff = *(int*) d1 - *(int*) d2;
    if (diff < 0)
        return -1;
    if (diff > 0)
        return 1;
    return 0;
}

void intprint(void* d)
{
    printf("%d\t", *((int*)d));
}

struct bstnode* searchGBST(genericBST gt, void* d)
{
    struct bstnode* ptr = gt -> root;
    struct bstnode* prev = NULL;
    if (!(gt -> root))
        return NULL;
    while (ptr)
    {
        int cmpval = (gt -> compareFn)((ptr -> data), d);
        prev = ptr;
        if (cmpval == 0)
            return ptr;
        else if (cmpval == 1)
            ptr = ptr -> lchild;
        else
            ptr = ptr -> rchild;
    }
    return prev;
}

void insertNodeGBST(genericBST gt, void* d)
{
    struct bstnode* node = (struct bstnode*)malloc(sizeof(struct bstnode));
    node -> data = malloc(gt -> dsize);
    node -> lchild = NULL;
    node -> rchild = NULL;
    memcpy(node -> data, d, gt -> dsize);
    if (!(gt -> root))
    {
        gt -> root = node;
        return;
    }
    struct bstnode* ptr = searchGBST(gt, d);
    if ((gt -> compareFn)(ptr -> data, d) == -1)
        ptr -> rchild = node;
    else
        ptr -> lchild = node;
}

void inorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root)
        return;
    inorderTraverse(gt, root -> lchild);
    (gt -> printNode)((root -> data));
    inorderTraverse(gt, root -> rchild);
}

void preorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root)
        return;
    (gt -> printNode)((root -> data));
    preorderTraverse(gt, root -> lchild);
    preorderTraverse(gt, root -> rchild);
}

void postorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root)
        return;
    postorderTraverse(gt, root -> lchild);
    postorderTraverse(gt, root -> rchild);
    (gt -> printNode)((root -> data));
}

int traverseGBST(genericBST gt, int order)
{
    if (!gt -> root)
        return 0;
    if (order == 0)
        inorderTraverse(gt, gt -> root);
    else if (order == 1)
        preorderTraverse(gt, gt -> root);
    else if (order == 2)
        postorderTraverse(gt, gt -> root);
    else
        return 0;
    printf("\n");
    return 1;
}

int exportGBST(genericBST gt, const char* fname)
{
    FILE* fp = fopen(fname, "w");
    
}

genericBST importGBST(const char* fname, int (*cf)(void*, void*), void (*pn)(void*))
{
    FILE* fp = fopen(fname, "r");
    int x;
    genericBST gt = createGBST(sizeof(int), cf, pn);
    while (!feof(fp))
    {
        fscanf(fp, "%d", &x);
        insertNodeGBST(gt, &x);
    }
    return gt;
}

int main()
{
    genericBST gt = createGBST(sizeof(int), &intcmp, &intprint);
    int arr[11] = {15, 7, 20, 23, 0, 19, 21, 45, 1, 4, 5};
    for (int i = 0; i < 11; i++)
        insertNodeGBST(gt, &(arr[i]));
    traverseGBST(gt, 0);
    return 0;
}
