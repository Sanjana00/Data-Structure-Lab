#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to define node of tree
struct bstnode
{
    void* data;
    struct bstnode* lchild;
    struct bstnode* rchild;
    int height;
};

// struct to define generic BST 
typedef struct gbst
{
    int dsize;
    void (*printNode)(void *);
    int (*compareFn)(void*, void*);
    struct bstnode* root;
}* genericBST;

// setting print function to generic BST
int setPrintNodeFnGBST(genericBST gt, void (*pn)(void*))
{
    if (!pn)
        return 0;
    gt -> printNode = pn;
    return 1;
}

// setting compare function to generic BST
int setCompareFnGBST(genericBST gt, int (*cf)(void*, void*))
{
    if (!cf)
        return 0;
    gt -> compareFn = cf;
    return 1;
}

// function to return the larger of two integer values
int max(int a, int b){
    return a > b? a : b;
}

// function to initialise a generic BST with given information
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

// function to compare the integer key values of two nodes in a generic BST
int intcmp(void* d1, void* d2)
{
    int diff = *(int*) d1 - *(int*) d2;
    if (diff < 0)
        return -1;
    if (diff > 0)
        return 1;
    return 0;
}

// function to display the integer key value of a node in a generic BST
void intprint(void* d)
{
    printf("%d\t", *((int*)d));
}

// function to return height of given node
int heightNode(struct bstnode* currNode){
    if (!currNode)
        return 0;
    return currNode -> height;
}

// function to calculate balance factor of given node
int balanceFactor(struct bstnode* currNode){
    if (!currNode)
        return 0;
    return heightNode(currNode -> lchild) - heightNode(currNode -> rchild);
}

// function to perform a single right rotation
struct bstnode* rightRotate(struct bstnode* ynode){
    struct bstnode* xnode = ynode -> lchild;
    struct bstnode* t = xnode -> rchild;
    xnode -> rchild = ynode;
    ynode -> lchild = t;
    ynode -> height = 1 + max(heightNode(ynode -> lchild), heightNode(ynode -> rchild));
    xnode -> height = 1 + max(heightNode(xnode -> lchild), heightNode(xnode -> rchild));
    return xnode;
}

// function to perform a single left rotation
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
    if (!currNode){ // new node to be inserted here
        struct bstnode* newNode = (struct bstnode*)malloc(sizeof(struct bstnode));
        newNode -> data = malloc(gt -> dsize);
        newNode -> lchild = NULL;
        newNode -> rchild = NULL;
        memcpy(newNode -> data, d, gt -> dsize);
        newNode -> height = 1; // height of leaf node is assumed to be 1 in this code
        return newNode;
    }
    int cmpval = (gt -> compareFn)(currNode -> data, d);
    if (cmpval < 0)
        currNode -> rchild = insertNodeAVL(gt, currNode -> rchild, d);
    else
        currNode -> lchild = insertNodeAVL(gt, currNode -> lchild, d);
    currNode -> height = 1 + max(heightNode(currNode -> lchild), heightNode(currNode -> rchild));
    int bf = balanceFactor(currNode); // calculating balance factor of current node
    int cmpleft = 0, cmpright = 0;
    if (currNode -> lchild) // tree may be unbalanced
        cmpleft = (gt -> compareFn)(currNode -> lchild -> data, d);
    if (currNode -> rchild) // tree may be unbalanced
        cmpright = (gt -> compareFn)(currNode -> rchild -> data, d);
    if (bf > 1 && cmpleft > 0) // single right rotation
        return rightRotate(currNode);
    if (bf < -1 && cmpright < 0) // single left rotation
        return leftRotate(currNode);
    if (bf > 1 && cmpleft < 0){ // double left right rotation
        currNode -> lchild = leftRotate(currNode -> lchild);
        return rightRotate(currNode);
    }
    if (bf < -1 && cmpright > 0){ // double right left rotation
        currNode -> rchild = rightRotate(currNode -> rchild);
        return leftRotate(currNode);
    }
    return currNode;
}

// function to insert a node in an AVL tree and return the tree
genericBST insAVL(genericBST gt, void* d)
{
    gt -> root = insertNodeAVL(gt, gt -> root, d);
    return gt;
}

// recursive function to delete a node in an AVL tree and balance the tree afterwards
struct bstnode* deleteNodeAVL(genericBST gt, struct bstnode* currNode, void* d){
    if (!currNode) // node does not exist, nothing to delete
        return currNode;
    int cmpval = (gt -> compareFn)(currNode -> data, d);
    if (cmpval == 1) // node to be deleted is present in the left subtree
        currNode -> lchild = deleteNodeAVL(gt, currNode -> lchild, d);
    else if (cmpval == -1) // node to be deleted is present in the right subtree
        currNode -> rchild = deleteNodeAVL(gt, currNode -> rchild, d);
    else { // need to delete current node
        if (!(currNode -> lchild)) { // current node is either a leaf or only has right subtree (no balancing required as tree was already balanced before deletion)
            struct bstnode* temp = currNode -> rchild;
            free(currNode);
            return temp; // replacing current node with its right subtree
        }
        else if (!(currNode -> rchild)) { // current node only has left subtree (no balancing required as tree was already balanced before deletion)
            struct bstnode* temp = currNode -> rchild;
            free(currNode);
            return temp; // replacing current node with its left subtree
        }
        // node to be deleted has both subtrees present
        // need to find inorder successor, copy data to current node and then delete inorder successor
        struct bstnode* temp = currNode -> rchild;
        while (temp -> lchild) // locating inorder successor
            temp = temp -> lchild;
        memcpy(currNode -> data, temp -> data, gt -> dsize); // copy data to current node
        currNode -> rchild = deleteNodeAVL(gt, currNode -> rchild, temp -> data); // deleting inorder successor
    }
    // balancing the tree after deletion
    currNode -> height = 1 + max(heightNode(currNode -> lchild), heightNode(currNode -> rchild)); // updating height of current node
    int bf = balanceFactor(currNode); // balance factor of current node
    int bfleft = balanceFactor(currNode -> lchild); // balance factor of left child
    int bfright = balanceFactor(currNode -> rchild); // balance factor of right child
    if (bf > 1 && bfleft >= 0) // single right rotation for left-left unbalanced condition
        return rightRotate(currNode);
    if (bf < -1 && bfright <= 0) // single left rotation for right-right unbalanced condition
        return leftRotate(currNode);
    if (bf > 1 && bfleft < 0){ // double left right rotation for left-right unbalanced condition
        currNode -> lchild = leftRotate(currNode -> lchild);
        return rightRotate(currNode);
    }
    if (bf < -1 && bfright > 0){ // double right left rotation for right-left unbalanced condition
        currNode -> rchild = rightRotate(currNode -> rchild);
        return leftRotate(currNode);
    }
    return currNode;
}

// function to delete a node from an AVL tree and return the tree
genericBST delAVL(genericBST gt, void* d){
    gt -> root = deleteNodeAVL(gt, gt -> root, d);
    return gt;
}

// function returns the height of the root of the AVL tree
int height(genericBST gt){
    return heightNode(gt -> root);
}

// recursive function to print the balance factor of each node in an AVL tree in inorder traversal
void printNodeBF(genericBST gt, struct bstnode* currRoot){
    if (!currRoot) // recursive base case
        return;
    printf("Key = ");
    (gt -> printNode)(currRoot -> data);
    printf("\nBalance factor = %d\n\n", balanceFactor(currRoot));
    printNodeBF(gt, currRoot -> lchild); // left subtree
    printNodeBF(gt, currRoot -> rchild); // right subtree
}

// function to print the balance factor of every node in AVL tree -> returns 0 if tree is empty, else 1
int printBF(genericBST gt){
    if (!gt -> root){ // tree is empty
        return 0;
    }
    printNodeBF(gt, gt -> root);
    return 1;
}

// recursive function to traverse BST in inorder (gives sorted output)
void inorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root) // base case
        return;
    inorderTraverse(gt, root -> lchild);
    (gt -> printNode)((root -> data));
    inorderTraverse(gt, root -> rchild);
}

// recursive function to traverse BSt in preorder
void preorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root) // base case
        return;
    (gt -> printNode)((root -> data));
    preorderTraverse(gt, root -> lchild);
    preorderTraverse(gt, root -> rchild);
}

// recursive function to traverse BST in postorder
void postorderTraverse(genericBST gt, struct bstnode* root)
{
    if (!root) // base case
        return;
    postorderTraverse(gt, root -> lchild);
    postorderTraverse(gt, root -> rchild);
    (gt -> printNode)((root -> data));
}

// function to traverse BST in mentioned order (0 = inorder, 1 = preorder, 2 = postorder)
int traverseGBST(genericBST gt, int order)
{
    if (!gt -> root) // tree is empty
        return 0;
    if (order == 0) // inorder traversal
        inorderTraverse(gt, gt -> root);
    else if (order == 1) // preorder traversal
        preorderTraverse(gt, gt -> root);
    else if (order == 2) // postorder traversal
        postorderTraverse(gt, gt -> root);
    else
        return 0;
    printf("\n");
    return 1;
}

// main function to demonstrate the working of the AVL tree and its implemented functions
int main()
{
    genericBST gt = createGBST(sizeof(int), &intcmp, &intprint);
    int arr[11] = {15, 7, 20, 23, 0, 19, 21, 45, 1, 4, 5};
    for (int i = 0; i < 11; i++)
        gt = insAVL(gt, &(arr[i]));
    printf("Inorder Traversal:\n");
    traverseGBST(gt, 0);
    printf("Preorder Traversal:\n");
    traverseGBST(gt, 1);
    int del[5] = {15, 20, 45, 1, 7};
    for (int i = 0; i < 5; i++) {
        printf("Deleting element: %d\n", del[i]);
        gt = delAVL(gt, &(del[i]));
        traverseGBST(gt, 1);
    }
    printf("\nHeight of tree = %d\n\n", height(gt));
    printBF(gt);
    return 0;
}
