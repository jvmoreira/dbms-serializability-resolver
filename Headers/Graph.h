// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

#include <vector>
#include <string>

using namespace std;

class Node
{
public:
	//Construtor
	Node(unsigned int id_) : id(id_),nodes{}{}

	unsigned int getID() const{ return id; }
	const vector<Node*>& getNodes() const{ return nodes; }
	void addNode( Node* node ) { nodes.push_back(node); }
private:
	unsigned int id;
	vector<Node*> nodes;
};

class Graph
{
public:
	//Construtor
	Graph(){}

	bool findCycle();
	Node* findNode( unsigned int id );

	Node* createNode( unsigned int id );
	void clear();
private:
	bool isCyclic( vector<Node*>&visitedNodes, Node* node );
private:
	vector<Node*> nodes;
};
