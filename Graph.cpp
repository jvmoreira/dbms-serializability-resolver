// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "Graph.h"

void Node::addNode( Node* node )
{
	nodes.push_back(node);
}

Graph::Graph()
{
}

Graph::~Graph()
{
}

Node* Graph::findNode( unsigned int id ) {
	for( auto& node : nodes )
		if( node->getID() == id )
			return node;
	return nullptr;
}

bool Graph::findCycle()
{
	//Verifica nó por nó para encontrar algum ciclo
	for( auto& node : nodes )
	{
		vector<Node*> visitedNodes;
		visitedNodes.push_back(node);

		if( isCyclic( visitedNodes, node ) )
			return true;
	}

	return false;
}

Node* Graph::createNode( unsigned int id )
{
	Node* node = new Node( id );
	nodes.push_back(node);

	return node;
}

void Graph::clear()
{
	for( auto& node : nodes )
		delete node;

	nodes.clear();
}

bool Graph::isCyclic( vector<Node*>&visitedNodes, Node* node )
{
	for(auto& p : node->getNodes() )
	{
		visitedNodes.push_back(p);

		if( p == visitedNodes[0] )
			return true;

		return isCyclic(visitedNodes,p);
	}

	return false;
}
