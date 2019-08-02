#include <iostream>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::max;

struct node
{
    int val;
    node *left;
    node *right;
    node(int x) : val(x){};
};

int height(node *root)
{
    if (root == nullptr)
        return -1;
    return max(height(root->right), height(root->left)) + 1;
}

int main()
{
    node *root = new node(randint(1, 20));

    root->right = new node(randint(1, 20));
    root->left = new node(randint(1, 20));

    root->right->left = new node(randint(1, 20));
    root->left->left = new node(randint(1, 20));

    root->left->left->left = new node(randint(1, 20));

    cout << height(root) << endl;
}