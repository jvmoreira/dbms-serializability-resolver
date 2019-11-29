// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "Graph.h"

Node* Graph::findNode( unsigned int id ) {
	// Busca um nó pela sua ID
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

		// Se for ciclico, retornar verdadeiro
		if( isCyclic( visitedNodes, node ) )
			return true;
	}

	return false;
}

Node* Graph::createNode( unsigned int id )
{
	// Cria nó para o grafo
	Node* node = new Node( id );
	nodes.push_back(node);

	return node;
}

void Graph::clear()
{
	// Limpa o grafo
	for( auto& node : nodes )
		delete node;

	nodes.clear();
}

bool Graph::isCyclic( vector<Node*>&visitedNodes, Node* node )
{
	for(auto& p : node->getNodes() )
	{
		// Adiciona o nó atual para os nós visitados
		visitedNodes.push_back(p);

		// Se o nó que está verificado, foi o nó de origem, quer dizer que é ciclico
		if( p == visitedNodes[0] )
			return true;

		return isCyclic(visitedNodes,p);
	}

	return false;
}
