#pragma once
#include <iostream> 
#include <list> 
#include <iterator>
#include "AllocationMetrics.h"
#include "Ramdan/Log.h"

class Graph
{
    int V;    // No. of vertices 
    bool found = false;
    // Pointer to an array containing 
    // adjacency lists 
    std::list<int> *adj;
    // A recursive function used by DFS 
    void DFSUtil( int v, bool visited[], int target );
public:
    Graph( int V );
    void addEdge( int v, int w );
    void DFS( int v, int target );
    void BFS( int s, int target );

    static unsigned int DFS_Traversal_Count;
    static unsigned int BFS_Traversal_Count;
};

unsigned int Graph::DFS_Traversal_Count = 0;
unsigned int Graph::BFS_Traversal_Count = 0;

Graph::Graph( int V )
{
    this->V = V;
    adj = new std::list<int>[V];
}

void Graph::addEdge( int v, int w )
{
    adj[v].push_back( w ); // Add w to v’s list. 
}

void Graph::DFSUtil( int v, bool visited[], int target )
{
    if ( found ) return;
    else
    {
        DFS_Traversal_Count++;
        visited[v] = true;
        LOG_CORE_NOHEAD( "%d ", v );
        if ( v == target ) found = true;

        std::list<int>::iterator i;
        for ( i = adj[v].begin(); i != adj[v].end(); ++i )
            if ( !visited[*i] )
                DFSUtil( *i, visited, target );
    }
}

// DFS traversal of the vertices reachable from v. 
// It uses recursive DFSUtil() 
void Graph::DFS( int v, int target )
{
    LOG_MEM();
    LOG_CORE_TRACE( "Traversal: ", false );
    // Mark all the vertices as not visited 
    bool *visited = new bool[V];
    for ( int i = 0; i < V; i++ )
        visited[i] = false;

    // Call the recursive helper function 
    // to print DFS traversal 
    DFSUtil( v, visited, target );
    LOG_CORE_NEWLINE();
    LOG_MEM();
}

void Graph::BFS( int s, int target )
{
    LOG_MEM();
    LOG_CORE_TRACE( "Traversal: ", false );
    // Mark all the vertices as not visited 
    bool *visited = new bool[V];
    for ( int i = 0; i < V; i++ )
        visited[i] = false;

    // Create a queue for BFS 
    std::list<int> queue;
    // Mark the current node as visited and enqueue it 
    visited[s] = true;
    queue.push_back( s );

    // 'i' will be used to get all adjacent 
    // vertices of a vertex 
    std::list<int>::iterator i;
    while ( !queue.empty() )
    {
        // Dequeue a vertex from queue and print it
        BFS_Traversal_Count++;
        s = queue.front();
        LOG_CORE_NOHEAD( "%d ", s );
        queue.pop_front();
        if ( s == target ) break;

        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        for ( i = adj[s].begin(); i != adj[s].end(); ++i )
        {
            if ( !visited[*i] )
            {
                visited[*i] = true;
                queue.push_back( *i );
            }
        }
    }
    LOG_CORE_NEWLINE();
    LOG_MEM();
}