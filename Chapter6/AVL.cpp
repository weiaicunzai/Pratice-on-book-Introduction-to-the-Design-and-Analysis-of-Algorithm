#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

class node
{
    int balance_factor;
    shared_ptr<node> left;
    shared_ptr<node> right;
    int val;

public:
    node(int v):val(v){};

    int get_balance_factor();
    void set_balance_factor(const int bf);

    shared_ptr<node> get_left_child();
    shared_ptr<node> get_right_child();
    void set_left_child(shared_ptr<node> left);
    void set_right_child(shared_ptr<node> right);

    int set_val(int val);
};

int node::get_balance_factor()
{
    return balance_factor;
}

void node::set_balance_factor(const int bf)
{
    balance_factor = bf;
}

shared_ptr<node> node::get_left_child()
{
    return left;
}

shared_ptr<node> node::get_right_child()
{
    return right;
}

int main()
{
    shared_ptr<node> a = new node(1);

}
