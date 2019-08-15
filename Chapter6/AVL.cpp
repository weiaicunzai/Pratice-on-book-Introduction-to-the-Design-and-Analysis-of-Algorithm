#include <iostream>
#include <memory>

class node;
using std::cout;
using std::endl;
using std::make_shared;
using std::max;
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
    void update_balance(node_ptr node);
    void insert_core(node_ptr node);
    int height(node_ptr);
    node_ptr root;
    node_ptr new_node;
    void inorder(node_ptr root);

public:
    node_ptr r_rotation(node_ptr node);
    node_ptr get_root();
    void insert_node(node_ptr node);
    void delete_node(node_ptr node);
    void inorder_print();
    AVL(node_ptr n) : root(n){};
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

    update_balance(left_child);
    update_balance(node);

    return left_child;
}

/**
 * @brief 
 */
node_ptr AVL::l_rotation(node_ptr node)
{
    node_ptr right_child = node->get_right_child();
    node_ptr T2 = right_child->get_left_child();
    right_child->set_left_child(node);
    node->set_right_child(T2);

    update_balance(node);
    update_balance(right_child);

    return right_child;
}

node_ptr AVL::lr_rotation(node_ptr node)
{
    node_ptr r = node;
    node_ptr c = r->get_left_child();
    node_ptr g = c->get_right_child();
    r->set_left_child(l_rotation(c));
    node_ptr res = r_rotation(r);

    return res;
}

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

    //update balance factor for current node
    update_balance(node);
    int bf = node->get_balance_factor();

    //left left case
    if (bf > 1 && key < node->get_left_child()->get_val())
        node = r_rotation(node);

    //right right case
    if (bf < -1 && key > node->get_right_child()->get_val())
        node = l_rotation(node);

    //left right case
    if (bf > 1 && key > node->get_left_child()->get_val())
        node = lr_rotation(node);

    //right left case
    if (bf < -1 && key < node->get_right_child()->get_val())
        node = rl_rotation(node);
}

void AVL::insert_node(node_ptr node)
{
    if (node == nullptr)
        return;

    new_node = node;
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

    if (node->get_right_child())
        inorder(node->get_right_child());
}

void AVL::inorder_print()
{
    inorder(root);
}

int main()
{
    node_ptr root = make_shared<node>(10);
    AVL a(root);

    a.insert_node(make_shared<node>(11));
    a.insert_node(make_shared<node>(12));
    a.inorder_print();

    node_ptr c = make_shared<node>(111);
    c->set_left_child(make_shared<node>(222));
    c->get_left_child()->set_left_child(make_shared<node>(333));

    a.r_rotation(c);


}
