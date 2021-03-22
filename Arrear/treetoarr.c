void treeToArray(int* arr, bstnode* root, int pos){
    if (!root)
        return;
    arr[pos] = root -> data;
    if (root -> lchild)
        treeToArray(arr, root -> lchild, 2 * pos);
    if (root -> rchild)
        treeToArray(arr, root -> rchild, 2 * pos + 1);
}
