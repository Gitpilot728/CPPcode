#include <iostream>
using namespace std;
struct bstnode
{
    int data;
    struct bstnode *left, *right;
};
struct bstnode *newNode(int key)
{
    struct bstnode *temp = new struct bstnode();
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct bstnode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}
struct bstnode *insert(struct bstnode *node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->data)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}
struct bstnode *minValueNode(struct bstnode *node)
{
    struct bstnode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
struct bstnode *deleteNode(struct bstnode *root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct bstnode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct bstnode *temp = root->left;
            free(root);
            return temp;
        }
        struct bstnode *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
int main()
{
    /* Let us create following BST
              40
             /  \
           30   60
                    \
                   65
                      \
                     70*/
    struct bstnode *root = NULL;
    root = insert(root, 47);
    root = insert(root, 32);
    root = insert(root, 68);
    root = insert(root, 52);
    root = insert(root, 40);
    root = insert(root, 38);
    cout << "Binary Search Tree created (Inorder traversal):" << endl;
    inorder(root);
    cout << "\nDelete node 40\n";
    root = deleteNode(root, 40);
    cout << "Inorder traversal for the modified Binary Search Tree:" << endl;
    inorder(root);
    return 0;
}
