#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstnode
{
    void* data;
    struct bstnode* lchild;
    struct bstnode* rchild;
    int height;
};

typedef struct gbst
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void*, void*);
    struct bstnode* root;
}* genericBST;

int setPrintNodeFnGBST(genericBST gt, void (*pn)(void*))
{
    if (!pn)
        return 0;
    gt -> printNode = pn;
    return 1;
}

int setCompareFnGBST(genericBST gt, int (*cf)(void*, void*))
{
    if (!cf)
        return 0;
    gt -> compareFn = cf;
    return 1;
}

int max(int a, int b){
    return a > b? a : b;
}

genericBST createGBST(int dsize, int (*cfunction)(void*, void*), void (*printNode)(void*))
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

int heightNode(struct bstnode* currNode){
    if (!currNode)
        return 0;
    return currNode -> height;
}

int balanceFactor(struct bstnode* currNode){
    if (!currNode)
        return 0;
    return heightNode(currNode -> lchild) - heightNode(currNode -> rchild);
}

struct bstnode* rightRotate(struct bstnode* ynode){
    struct bstnode* xnode = ynode -> lchild;
    struct bstnode* t = xnode -> rchild;
    xnode -> rchild = ynode;
    ynode -> lchild = t;
    ynode -> height = 1 + max(heightNode(ynode -> lchild), heightNode(ynode -> rchild));
    xnode -> height = 1 + max(heightNode(xnode -> lchild), heightNode(xnode -> rchild));
    return xnode;
}

struct bstnode* leftRotate(struct bstnode* xnode){
    struct bstnode* ynode = xnode -> rchild;
    struct bstnode* t = ynode -> lchild;
    ynode -> lchild = xnode;
    xnode -> rchild = t;
    xnode -> height = 1 + max(heightNode(xnode -> lchild), heightNode(xnode -> rchild));
    ynode -> height = 1 + max(heightNode(ynode -> lchild), heightNode(ynode -> rchild));
    return ynode;
}

struct bstnode* insertNodeAVL(genericBST gt, struct bstnode* currNode, void* d){
    if (!currNode){
        struct bstnode* newNode = (struct bstnode*)malloc(sizeof(struct bstnode));
        newNode -> data = malloc(gt -> dsize);
        newNode -> lchild = NULL;
        newNode -> rchild = NULL;
        memcpy(newNode -> data, d, gt -> dsize);
        newNode -> height = 1;
        return newNode;
    }
    int cmpval = (gt -> compareFn)(currNode -> data, d);
    if (cmpval < 0)
        currNode -> rchild = insertNodeAVL(gt, currNode -> rchild, d);
    else
        currNode -> lchild = insertNodeAVL(gt, currNode -> lchild, d);
    currNode -> height = 1 + max(heightNode(currNode -> lchild), heightNode(currNode -> rchild));
    int bf = balanceFactor(currNode);
    int cmpleft = 0, cmpright = 0;
    if (currNode -> lchild)
        cmpleft = (gt -> compareFn)(currNode -> lchild -> data, d);
    if (currNode -> rchild)
        cmpright = (gt -> compareFn)(currNode -> rchild -> data, d);
    if (bf > 1 && cmpleft > 0)
        return rightRotate(currNode);
    if (bf < -1 && cmpright < 0)
        return leftRotate(currNode);
    if (bf > 1 && cmpleft < 0){
        currNode -> lchild = leftRotate(currNode -> lchild);
        return rightRotate(currNode);
    }
    if (bf < -1 && cmpright > 0){
        currNode -> rchild = rightRotate(currNode -> rchild);
        return leftRotate(currNode);
    }
    return currNode;
}

genericBST insAVL(genericBST gt, void* d)
{
    gt -> root = insertNodeAVL(gt, gt -> root, d);
    return gt;
}

int height(genericBST gt){
    return heightNode(gt -> root);
}

void printNodeBF(genericBST gt, struct bstnode* currRoot){
    if (!currRoot)
        return;
    (gt -> printNode)(currRoot -> data);
    printf("\nBalance factor = %d\n\n", balanceFactor(currRoot));
    printNodeBF(gt, currRoot -> lchild);
    printNodeBF(gt, currRoot -> rchild);
}

int printBF(genericBST gt){
    if (!gt -> root){
        return 0;
    }
    printNodeBF(gt, gt -> root);
    return 1;
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

int main()
{
    genericBST gt = createGBST(sizeof(int), &intcmp, &intprint);
    int arr[11] = {15, 7, 20, 23, 0, 19, 21, 45, 1, 4, 5};
    for (int i = 0; i < 11; i++)
        gt = insAVL(gt, &(arr[i]));
    traverseGBST(gt, 0);
    traverseGBST(gt, 1);
    printf("Height of tree = %d\n", height(gt));
    printBF(gt);
    return 0;
}
