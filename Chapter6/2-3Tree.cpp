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

class node
{
    vector<int>  data;
    node_ptr left_child;
    node_ptr right_child;
    node_ptr middle_child;
    node_ptr parent;
    void split();
    void promote();
public:
    node(int val);
    node_ptr get_left_child();
    void set_left_child(node_ptr node);

    node_ptr get_right_child();
    void set_right_child(node_ptr node);

    node_ptr get_mid_child();
    void set_mid_child(node_ptr node);

    node_ptr get_parent();
    void set_parent(node_ptr node);

    size_t size();

    int get_left_data();
    int get_mid_data();
    int get_right_data();

    bool is_leaf();
    bool is_overflow();
    void insert(int data);
};

node::node(int val)
{
    data.push_back(val);
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

node_ptr node::get_mid_child()
{
    return middle_child;
}

void node::set_mid_child(node_ptr node)
{
    middle_child = node;
}

void node::set_right_child(node_ptr node)
{
    right_child = node;
}

void node::set_left_child(node_ptr node)
{
    left_child = node;
}

node_ptr node::get_parent()
{
    return parent;
}

void node::set_parent(node_ptr node)
{
    parent = node;
}

int node::get_left_data()
{
    assert(data.size() < 4);
    return data.front();
}

int node::get_right_data()
{
    assert(data.size() > 1 && data.size() < 4);
    return data.back();
}

int node::get_mid_data()
{
    assert(data.size() == 3);
    return data[1];
}

//return node's elements number
size_t node::size()
{
    return data.size();
}

bool node::is_overflow()
{
    return data.size() > 2;
}

bool node::is_leaf()
{
    return !(left_child || right_child || middle_child);
}

void node::insert(int data)
{
    //can not insert when data size is larger than 3
    assert(this->data.size() > 3);
    this->data.push_back(data);
    sort(this->data.begin(), this->data.end());
}

//2-3 tree
class tree
{
    node_ptr root;
    void insert_core(node_ptr node, int key);
public:
    void insert(int data);
};

void tree::insert(int data)
{
    if(!root)
    {
        root = make_shared<node>(data);
        return;
    }

}

void tree::insert_core(node_ptr node, int key)
{
    if(node->is_leaf())
}

int main()
{
    node n;
}




