#include <list>
#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;
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
 * @brief Implements a breadth-first search traversal of a given graph 
 * @param g a gragh in adjacent list format
 * @param visited check if a node is visited
 * @param the vertex we want to visit
 */
void bfs(graph &g, vector<bool> &visited, int v)
{
    if(visited[v])
        return;
    
    if(!g.get_vertices_num())
        return;

    queue<int> q;
    q.push(v);
    visited[v] = true;
    cout << q.front() << endl;

    while(!q.empty())
    {
        auto adj_list = g.get_adj_list();
        auto cur_vertex = adj_list->at(q.front());

        //iterate through the vertices that are one step away from the current vertex
        for(auto it = cur_vertex.begin(); it != cur_vertex.end(); it++)
        {
            if(!visited[*it])
            {
                visited[*it] = true;
                q.push(*it);
                cout << *it << endl;
            }
        }

        q.pop();
    }
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
        bfs(g, visited, i); //since g is a disconnected graph, we need to call dfs for every vertex

}