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

void inorderExport(genericBST gt, struct bstnode* root, FILE* fp)
{
    if (!root)
        return;
    inorderExport(gt, root -> lchild, fp);

    fprintf(fp, "%d\n", *(int*)(root -> data));

    inorderExport(gt, root -> rchild, fp);
}

int exportGBST(genericBST gt, const char* fname)
{
    FILE* fp = fopen(fname, "w");
    if (!fp)
    {
        printf("File could not be opened\n");
        return 0;
    }
    inorderExport(gt, gt -> root, fp);
    fclose(fp);
    return 1;
}

genericBST importGBST(const char* fname, int (*cf)(void*, void*), void (*pn)(void*))
{
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        printf("File could not be opened\n");
        return NULL;
    }
    int x;
    genericBST gt = createGBST(sizeof(int), cf, pn);
    while (!feof(fp))
    {
        fscanf(fp, "%d", &x);
        insertNodeGBST(gt, &x);
    }
    fclose(fp);
    return gt;
}

/*
void deleteNode(genericBST gt, struct bstnode* node)
{
    if (!(node -> lchild) && !(node -> rchild))
    {
        free(node);
        node = NULL;
        return;
    }
    struct bstnode* temp;
    if (node -> lchild)
        temp = node -> lchild;
    else
        temp = node -> rchild;
    memcpy(node -> data, temp -> data, gt -> dsize);
    node -> rchild = temp -> rchild;
    node -> lchild = temp -> lchild;
    temp -> rchild = NULL;
    temp -> lchild = NULL;
    free(temp);
}

int deleteNodeGBST(genericBST gt, void* d)
{
    struct bstnode* node = searchGBST(gt, d);
    if (!node)
    {
        printf("Tree is empty\n");
        return 0;
    }
    if ((gt -> compareFn)(node -> data, d) != 0)
    {
        printf("Node could not be found\n");
        return 0;
    }
    if (!(node -> lchild) || !(node -> rchild))
    {
        deleteNode(gt, node);
        return 1;
    }
    struct bstnode* suc = node -> rchild;
    while (suc -> lchild)
        suc = suc -> lchild;
    memcpy(node -> data, suc -> data, gt -> dsize);
    deleteNode(gt, suc);
    return 1;
}
*/

struct bstnode* deleteNode(genericBST gt, struct bstnode* root, void *d){
    if (!root) 
        return root;

    if ((gt -> compareFn)(root -> data, d) == -1)
        root -> rchild = deleteNode(gt, root -> rchild, d);
    else if ((gt -> compareFn)(root -> data, d) == 1)
        root -> lchild = deleteNode(gt, root->lchild, d);
    else
    {
        if (!(root -> lchild))
        {
            struct bstnode* temp = root -> rchild;
            free(root);
            return temp;
        }
        else if (!(root -> rchild))
        {
            struct bstnode* temp = root -> lchild;
            free(root);
            return temp;
        }

        struct bstnode* suc = root -> rchild;
        while (suc -> lchild)
            suc = suc -> lchild;
        memcpy(root -> data, suc -> data, gt -> dsize);
        root -> rchild = deleteNode(gt, root -> rchild, suc -> data);
    }
    return root;
}

int deleteNodeGBST(genericBST gt, void *d)
{
    struct bstnode* node = searchGBST(gt, d);
    if (!node)
    {
        printf("Tree is empty\n");
        return 0;
    }
    if ((gt -> compareFn)(node -> data, d) != 0)
    {
        printf("Node could not be found\n");
        return 0;
    }

    gt -> root = deleteNode(gt, gt -> root, d);
    return 1;
}

int main()
{
    genericBST gt = createGBST(sizeof(int), &intcmp, &intprint);
    int arr[11] = {15, 7, 20, 23, 0, 19, 21, 45, 1, 4, 5};
    for (int i = 0; i < 11; i++)
        insertNodeGBST(gt, &(arr[i]));
    traverseGBST(gt, 0);
    int a[3] = {21, 4, 7};
    for (int i = 0; i < 3; i++)
        deleteNodeGBST(gt, &(a[i]));
    traverseGBST(gt, 0);
    exportGBST(gt, "exported.txt");
    genericBST t = importGBST("exported.txt", &intcmp, &intprint);
    traverseGBST(t, 0);
    return 0;
}
