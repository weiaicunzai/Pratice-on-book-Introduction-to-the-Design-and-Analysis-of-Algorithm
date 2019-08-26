#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>

class node;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;
using std::sort;
using node_ptr = shared_ptr<node>;

enum color {RED, BLACK};

class node
{
    int  data;
    node_ptr left_child;
    node_ptr right_child;
    color c;
    size_t size;
public:
    node(int val):data(val), c(RED), size(1){};
    node_ptr get_left_child();
    void set_left_child(node_ptr node);

    node_ptr get_right_child();
    void set_right_child(node_ptr node);

    color get_color();
    void set_color(color c);
    int get_data();

    size_t get_size();

    bool is_leaf();
};

void node::set_color(color c)
{
    this->c = c;
}

color node::get_color()
{
    return c;
}

//getter and setter
node_ptr node::get_left_child()
{
    return left_child;
}

node_ptr node::get_right_child()
{
    return right_child;
}

void node::set_right_child(node_ptr node)
{
    right_child = node;
}

void node::set_left_child(node_ptr node)
{
    left_child = node;
}

//return node's all subtree elements number
size_t node::get_size()
{
    return size;
}

bool node::is_leaf()
{
    return !(left_child || right_child);
}

int node::get_data()
{
    return data;
}


//2-3 tree
//use red black tree to implement the 2 3 tree
class tree
{
    node_ptr root;
    void insert_core(node_ptr node, int key);
    bool is_red(node_ptr node);
    node_ptr l_rotate(node_ptr node);
    node_ptr r_rotate(node_ptr node);
    node_ptr insert(node_ptr node, int data);
public:
    void insert(int data);
};

bool tree::is_red(node_ptr node)
{
    if(!node)
        return false;
    return node->get_color() == RED;
}

node_ptr tree::insert(node_ptr h, int key)
{
    if(!h)
        return make_shared<node>(key);
    
    if(h->get_data() > key)
        h->set_left_child(insert(h->get_left_child(), key));
    if(h->get_data() < key)
        h->set_right_child(insert(h->get_right_child(), key));
    //do nothing when key == data

    if(!is_red(h->get_left_child) && is_red(h->get_right_child()))
        h = l_rotate(h);
    return h;
}

void tree::insert(int data)
{
    if(!root)
    {
        root = make_shared<node>(data);
        return;
    }

    root = insert(root, data);
    root->set_color(BLACK);

}

int main()
{
    vector<int> v(1, 33);
    cout << v.size() << endl;
    node_ptr a = make_shared<node>(10);
}




