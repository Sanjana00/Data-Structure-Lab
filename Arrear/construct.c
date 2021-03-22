#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int preIndex = 0;
int postIndex = 0;

struct treenode
{
    int data;
    struct treenode* lchild;
    struct treenode* rchild;
    struct treenode* parent;
};

typedef struct treenode treenode;

void inorderTraverse(treenode* root)
{
    if (!root)
        return;
    inorderTraverse(root -> lchild);
    printf("%d\t", (root -> data));
    inorderTraverse(root -> rchild);
}

void preorderTraverse(treenode* root)
{
    if (!root)
        return;
    printf("%d\t", (root -> data));
    preorderTraverse(root -> lchild);
    preorderTraverse(root -> rchild);
}

void postorderTraverse(treenode* root)
{
    if (!root)
        return;
    postorderTraverse(root -> lchild);
    postorderTraverse(root -> rchild);
    printf("%d\t", (root -> data));
}

int traverseBST(treenode* root, int order)
{
    if (!root){
        printf("Tree is empty\n");
        return 0;
    }
    if (order == 0)
        inorderTraverse(root);
    else if (order == 1)
        preorderTraverse(root);
    else if (order == 2)
        postorderTraverse(root);
    else
        return 0;
    printf("\n");
    return 1;
}

int search(int arr[], int start, int end, int value){
    for (int i = start; i <= end; i++){
        if (arr[i] == value)
            return i;
    }
    return -1;
}

treenode* buildTreeInPost(int in[], int post[], int start, int end, treenode* par){
    if (start > end)
        return NULL;
    treenode* newNode = (treenode*)malloc(sizeof(treenode));
    newNode -> data = post[postIndex--];
    newNode -> lchild = NULL;
    newNode -> rchild = NULL;
    newNode -> parent = par;
    if (start == end)
        return newNode;
    int rootPos = search(in, start, end, newNode -> data);
    if (rootPos == -1)
        return NULL;
    newNode -> rchild = buildTreeInPost(in, post, rootPos + 1, end, newNode);
    newNode -> lchild = buildTreeInPost(in, post, start, rootPos - 1, newNode);
    return newNode;
}

treenode* getTreeInPost(int a[], int asize, int b[], int bsize){
    if (asize != bsize)
        return NULL;
    if (asize == 0)
        return NULL;
    postIndex = bsize - 1;
    return buildTreeInPost(a, b, 0, asize - 1, NULL);
}

treenode* buildTreeInPre(int in[], int pre[], int start, int end, treenode* par){
    if (start > end)
        return NULL;
    treenode* newNode = (treenode*)malloc(sizeof(treenode));
    newNode -> data = pre[preIndex++];
    newNode -> lchild = NULL;
    newNode -> rchild = NULL;
    newNode -> parent = par;
    if (start == end)
        return newNode;
    int rootPos = search(in, start, end, newNode -> data);
    if (rootPos == -1)
        return NULL;
    newNode -> lchild = buildTreeInPre(in, pre, start, rootPos - 1, newNode);
    newNode -> rchild = buildTreeInPre(in, pre, rootPos + 1, end, newNode);
    return newNode;
}

treenode* getTreeInPre(int a[], int asize, int b[], int bsize){
    if (asize != bsize)
        return NULL;
    if (asize == 0)
        return NULL;
    preIndex = 0;
    return buildTreeInPre(a, b, 0, asize - 1, NULL);
}

int main()
{
    int inorder[11] = {0, 1, 4, 5, 7, 15, 19, 20, 21, 23, 45};
    int preorder[11] = {15, 7, 0, 1, 4, 5, 20, 19, 23, 21, 45};
    int postorder[11] = {5, 4, 1, 0, 7, 19, 21, 45, 23, 20, 15};
    treenode* root = getTreeInPre(inorder, 11, preorder, 11);
    traverseBST(root, 0);
    traverseBST(root, 1);
    traverseBST(root, 2);
    root = getTreeInPost(inorder, 11, postorder, 11);
    traverseBST(root, 0);
    traverseBST(root, 1);
    traverseBST(root, 2);
    return 0;
}
