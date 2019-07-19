#include <list>
#include <vector>
#include <iostream>

using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::to_string;

class graph
{
    int vertices_num;
    vector<list<int>> *adj_list;
    public:
        graph(int v);
        void add_edge(int src, int dest);
        int get_vertices_num();
        const vector<list<int>>* get_adj_list();
};

graph::graph(int v)
{
    adj_list = new vector<list<int>>;
    for(int i = 0; i < v; i++)
    {
        list<int> temp;
        temp.push_back(i);
        adj_list->push_back(temp);
    }
    vertices_num = v;
}

void graph::add_edge(int src, int dest)
{
    if(src == dest)
        throw "It's a Directed Acyclic Graph";
    if(src >= this->vertices_num)
        throw "vertex" + to_string(src) + " does not exist!";
    if(dest >= this->vertices_num)
        throw "vertex" + to_string(dest) + " does not exist!";

    adj_list->at(src).push_back(dest);
}

int graph::get_vertices_num()
{
    return this->vertices_num;
}

const vector<list<int>>*  graph::get_adj_list()
{
    return this->adj_list;
}

/**
 * @brief Implements a depth-first search traversal of a given graph 
 * @param g a gragh in adjacent list format
 * @param visited check if a node is visited
 * @param the vertex we want to visit
 */
void dfs(graph &g, vector<bool> &visited, int v)
{
    if(visited[v])
        return;

    cout << v << endl;
    visited[v] = true;

    auto adj_list = g.get_adj_list();
    list<int> temp = adj_list->at(v);
    for(auto it = temp.begin(); it != temp.end(); it++)
        if(!visited[*it])
            dfs(g, visited, *it);
}


int main()
{
    graph g(7); //DAG, also a disconnected graph
    g.add_edge(0, 2);
    g.add_edge(0, 5);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(2, 5);
    g.add_edge(3, 4);
    g.add_edge(5, 6);
    g.add_edge(5, 4);
    g.add_edge(4, 6);

    vector<bool> visited(g.get_vertices_num());
    for(int i = 0; i < g.get_vertices_num(); i++)
        visited[i] = false;
    
    for(int i = 0; i < 7; i++)
        dfs(g, visited, i); //since g is a disconnected graph, we need to call dfs for every vertex
}