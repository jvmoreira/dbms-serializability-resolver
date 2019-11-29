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

bool Graph::findCycle()
{
	//Verifica nó por nó para encontrar algum ciclo
	for( const auto& node : nodes )
	{
		//Verifica os nós apontados
		for( const auto& targetNode : node->getNodes() )
		{
			//Se algum nó que é apontado, apontar para o nó que está verificando, significa que encontramos um ciclo
			//Logo podemos retornar true e sair do laço
			for( const auto& childNode : targetNode->getNodes() )
				if( childNode == node )
					return true;
		}
	}

	return false;
}

Node* Graph::createNode( unsigned int id )
{
	Node* node = new Node( id );
	nodes.push_back(node);

	return node;
}