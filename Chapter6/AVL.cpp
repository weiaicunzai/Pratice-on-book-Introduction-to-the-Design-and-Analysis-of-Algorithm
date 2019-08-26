#include <iostream>
#include <memory>
#include <set>
#include "../utils/utils.hpp"

class node;
using std::cout;
using std::endl;
using std::make_shared;
using std::max;
using std::set;
using std::shared_ptr;
using node_ptr = shared_ptr<node>;

class node
{
    int balance_factor;
    node_ptr left;
    node_ptr right;
    int val;

public:
    node(int v) : val(v), left(nullptr), right(nullptr), balance_factor(0){};

    int get_balance_factor();
    void set_balance_factor(const int bf);

    node_ptr get_left_child();
    node_ptr get_right_child();
    void set_left_child(node_ptr left);
    void set_right_child(node_ptr right);

    void set_val(int val);
    int get_val();
};

void node::set_val(int val)
{
    val = val;
}

int node::get_val()
{
    return val;
}

int node::get_balance_factor()
{
    return balance_factor;
}

void node::set_balance_factor(const int bf)
{
    balance_factor = bf;
}

node_ptr node::get_left_child()
{
    return left;
}

node_ptr node::get_right_child()
{
    return right;
}

void node::set_left_child(node_ptr left)
{
    this->left = left;
}

void node::set_right_child(node_ptr right)
{
    this->right = right;
}

class AVL
{
    node_ptr rl_rotation(node_ptr node);
    node_ptr lr_rotation(node_ptr node);
    node_ptr l_rotation(node_ptr node);
    node_ptr r_rotation(node_ptr node);
    void update_balance(node_ptr node);
    void insert_core(node_ptr node);
    int height(node_ptr);
    node_ptr root;
    node_ptr new_node;
    node_ptr sub_root;
    bool update_child;
    void inorder(node_ptr root);

public:
    node_ptr get_root();
    void insert_node(node_ptr node);
    void inorder_print();
    AVL(node_ptr n) : root(n), update_child(false){};
};

/**
 * @brief perform single right rotation on given node
 * @node node whose bf is -2 
 * @output new root after rotated
 */
node_ptr AVL::r_rotation(node_ptr node)
{
    node_ptr left_child = node->get_left_child();
    node_ptr T2 = left_child->get_right_child();
    left_child->set_right_child(node);
    node->set_left_child(T2);

    //update root
    if (node == root)
        root = left_child;

    update_balance(left_child);
    update_balance(node);

    return left_child;
}

/**
 * @brief perform left rotation on given node
 * @param node the node which perform left rotation on
 * @param output return new root of the subtree
 */
node_ptr AVL::l_rotation(node_ptr node)
{
    node_ptr right_child = node->get_right_child();
    node_ptr T2 = right_child->get_left_child();
    right_child->set_left_child(node);
    node->set_right_child(T2);

    //update root
    if (node == root)
        root = right_child;

    update_balance(node);
    update_balance(right_child);

    return right_child;
}

/**
 * @brief perform left rotation on given node's left child, then
 *        right rotation on given node
 * @param given node
 * @output new root of rotated subtree
 */
node_ptr AVL::lr_rotation(node_ptr node)
{
    node_ptr r = node;
    node_ptr c = r->get_left_child();
    node_ptr g = c->get_right_child();
    r->set_left_child(l_rotation(c));
    node_ptr res = r_rotation(r);

    return res;
}

/**
 * @brief perform right rotation on given node's right child, then
 *        left rotation on given node
 * @param given node
 * @output new root of rotated subtree
 */
node_ptr AVL::rl_rotation(node_ptr node)
{
    node_ptr r = node;
    node_ptr c = r->get_right_child();
    node_ptr g = c->get_left_child();

    r->set_right_child(r_rotation(c));
    node_ptr res = l_rotation(r);

    return res;
}

void AVL::insert_core(node_ptr node)
{
    if (node == nullptr)
        return;

    int key = new_node->get_val();

    if (node->get_val() < key)
    {
        if (!node->get_right_child())
            node->set_right_child(new_node);
        else
            insert_core(node->get_right_child());
    }
    else if (node->get_val() > key)
    {
        if (!node->get_left_child())
            node->set_left_child(new_node);
        else
            insert_core(node->get_left_child());
    }
    else
        throw "equal keys not allowed";

    //set new child to the new rotated subroot
    if (update_child)
    {
        if (key > node->get_val())
            node->set_right_child(sub_root);
        if (key < node->get_val())
            node->set_left_child(sub_root);
        update_child == false;
    }

    //update balance factor for current node
    update_balance(node);
    int bf = node->get_balance_factor();

    //left left case
    if (bf > 1 && key < node->get_left_child()->get_val())
    {
        update_child = true;
        sub_root = r_rotation(node);
    }

    //right right case
    else if (bf < -1 && key > node->get_right_child()->get_val())
    {
        update_child = true;
        sub_root = l_rotation(node);
    }

    //left right case
    else if (bf > 1 && key > node->get_left_child()->get_val())
    {
        update_child = true;
        sub_root = lr_rotation(node);
    }

    //right left case
    else if (bf < -1 && key < node->get_right_child()->get_val())
    {
        update_child = true;
        sub_root = rl_rotation(node);
    }
}

void AVL::insert_node(node_ptr node)
{
    if (node == nullptr)
        return;

    new_node = node;
    update_child = false;
    insert_core(root);
}

node_ptr AVL::get_root()
{
    return root;
}

int AVL::height(node_ptr node)
{
    //height of an empty tree is -1
    if (!node)
        return -1;

    return max(height(node->get_left_child()),
               height(node->get_right_child())) +
           1;
}

void AVL::update_balance(node_ptr node)
{
    node_ptr left = node->get_left_child();
    node_ptr right = node->get_right_child();
    node->set_balance_factor(height(left) - height(right));
}

void AVL::inorder(node_ptr node)
{
    if (node == nullptr)
        return;

    if (node->get_left_child())
        inorder(node->get_left_child());

    cout << "val: " << node->get_val()
         << " bf: " << node->get_balance_factor() << endl;
    ;

    if (node->get_left_child())
        cout << "left: " << node->get_left_child()->get_val() << endl;
    else
        cout << "left: empty" << endl;

    if (node->get_right_child())
        cout << "right: " << node->get_right_child()->get_val() << endl;
    else
        cout << "right: empty" << endl;

    cout << endl;

    if (node->get_right_child())
        inorder(node->get_right_child());
}

void AVL::inorder_print()
{
    inorder(root);
}

int main()
{
    int size = randint(1, 30);

    //no duplicates numbers are allowed
    set<int> data;
    while (data.size() != size)
        data.insert(randint(-100, 100));

    //init root
    //only test for insert implementation
    AVL test(make_shared<node>(100000));
    for (auto it = data.begin(); it != data.end(); it++)
        test.insert_node(make_shared<node>(*it));

    test.inorder_print();

    data.clear();
}