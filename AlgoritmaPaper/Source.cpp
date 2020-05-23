#define PUBLIC

#include "Ramdan/Log.h"
#include "Ramdan/Timer.h"
#include "Graph.h"

enum GraphType { BFS, DFS, ALL };
GraphType GraphSelect;
int StartingNode;
int DestinationNode;

bool MainMenu()
{
	system( "Cls" );

	LOG_WARN( "Powered by Ramdan Engine" );
	LOG_TRACE( "Graph Algorithm Coding Implementation" );
	LOG_TRACE( "[1] Depth First Search" );
	LOG_TRACE( "[2] Breadth First Search" );
	LOG_TRACE( "[3] Experiment All" );
	LOG_INFO( "Please Select one of the Algorithm: ", false );

	std::string input;
	std::getline( std::cin, input );
	int val = stoi( input );
	switch ( val )
	{
	case 1: GraphSelect = DFS; break;
	case 2: GraphSelect = BFS; break;
	case 3: GraphSelect = ALL; break;
	default: return true;
	}
	return false;
}

void RandomizeGraph( Graph *graph, int vertices, int edges )
{
	Ramdan::Timer Log( "Graph", ADJUST, NONE );
	
	srand( time( 0 ) );
	int j, count; int i = 0;
	int **edge = new int *[edges];
	for ( int i = 0; i < edges; ++i )
		edge[i] = new int[2];

	//Assign random values to the number of vertex and edges of the graph, Using rand().
	LOG_WARN( "Generating Edges Connection..." );
	while ( i < edges )
	{	
		edge[i][0] = rand() % vertices;
		edge[i][1] = rand() % vertices;
		//Print the connections of each vertex, irrespective of the direction.
		if ( edge[i][0] == edge[i][1] )
			continue;
		else
		{
			for ( j = 0; j < i; j++ )
			{
				if ( ( edge[i][0] == edge[j][0] && edge[i][1] == edge[j][1] ) || 
					 ( edge[i][0] == edge[j][1] && edge[i][1] == edge[j][0] ) )
					i--;
			}
		}
		i++;
		float percentage = float( i ) / edges * 100.0f;
		LOG_TRACE( "Progress: ", false );
		LOG_NOHEAD( "%d out of %d, [%.1f]%%\r", i, edges, percentage );
	}

	LOG_WARN( "Assembling Graph...                                 " );

#ifdef PUBLIC

	for ( i = 0; i < vertices; i++ )
	{
		float percentage = float( i ) / vertices * 100.0f;
		LOG_TRACE( "Progress: ", false );
		LOG_NOHEAD( "%d out of %d, [%.1f]%%\r", i, vertices, percentage );

#else

	LOG_CORE_NOHEAD( "\nGraph Summary:" );
	for ( i = 0; i < vertices; i++ )
	{

#endif
		count = 0;
		int nextNode = -1;
		LOG_CORE_NOHEAD( "\n%d -> { ", i );
		if ( i != DestinationNode )
		{
			for ( j = 0; j < edges; j++ )
			{
				if ( edge[j][0] == i )						nextNode = edge[j][1];
				else if ( edge[j][1] == i )					nextNode = edge[j][0];
				else if ( j == edges - 1 && count == 0 )	continue;
				if ( nextNode != -1 )
				{
					LOG_CORE_NOHEAD( "%d ", nextNode );
					graph->addEdge( i, nextNode );
					count++;
					nextNode = -1;
				}
			}
		}
		else
		{
			LOG_CORE_NOHEAD( "Destination " );
			graph->addEdge( i, i );
		}
		LOG_CORE_NOHEAD( "}" );
	}
	LOG_CORE_NOHEAD( "\n\n" );

	Log.Toc();
	std::string duration = Log.GetDurStr();
	LOG_OK( duration.c_str(), false );
	LOG_NOHEAD( "               \n" );
}

int AskVertices()
{
	int size;
	while ( true )
	{
		LOG_INFO( "Insert Vertex Size: ", false );
		std::cin >> size;
		if ( size > 0 ) break;
	}
	return size;
}

int AskEdges( int vertices )
{
	int maxVertices = ( vertices * ( vertices - 1 ) ) / 2;
	LOG_TRACE( "Complete Graph / Maximum Edges: ", false );
	std::cout << maxVertices << std::endl;

	int size;
	while ( true )
	{
		LOG_INFO( "Insert Edge Size: ", false );
		std::cin >> size;
		if ( size > 0 && size <= maxVertices ) break;
	}
	return size;
}

void AskNode( int vertices )
{
	//print available node
	LOG_TRACE( "Available Node: ", false );
	LOG_NOHEAD( "0 - %d\n", vertices - 1 );

	while ( true )
	{
		LOG_INFO( "Insert Starting Node: ", false );
		std::cin >> StartingNode;
		if ( StartingNode >= 0 && StartingNode < vertices ) break;
	}
	while ( true )
	{
		LOG_INFO( "Insert Destination Node: ", false );
		std::cin >> DestinationNode;
		if ( DestinationNode < vertices ) break;
	}
}

int main()
{
	Ramdan::Log::init();

	while ( MainMenu() );
	
	int vertices = AskVertices();
	int edges = AskEdges( vertices );
	Graph *graph = new Graph( vertices );
	AskNode( vertices );

	RandomizeGraph( graph, vertices, edges );
	
	if ( GraphSelect == DFS || GraphSelect == ALL )
	{
		LOG_WARN( "Starting Depth First Search!" );
		Ramdan::Timer Log( "DFS", ADJUST, NONE );
		graph->DFS( StartingNode, DestinationNode );
		Log.Toc();
		LOG_TRACE( "Traversal Count: ", false );
		LOG_NOHEAD( "%d\n", Graph::DFS_Traversal_Count );
		LOG_OK( Log.GetDurStr().c_str() );
	}
	if ( GraphSelect == BFS || GraphSelect == ALL )
	{
		LOG_WARN( "Starting Breadth First Search!" );
		Ramdan::Timer Log( "BFS", ADJUST, NONE );
		graph->BFS( StartingNode, DestinationNode );
		Log.Toc();
		LOG_TRACE( "Traversal Count: ", false );
		LOG_NOHEAD( "%d\n", Graph::BFS_Traversal_Count );
		LOG_OK( Log.GetDurStr().c_str() );
	}

	system( "Pause" );
}