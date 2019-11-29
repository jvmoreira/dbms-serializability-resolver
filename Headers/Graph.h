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
	Node(unsigned int id_) : id(id_),nodes{}{}
	~Node(){}

	unsigned int getID() const{ return id; }
	const vector<Node*>& getNodes() const{ return nodes; }
	void addNode( Node* node );
private:
	unsigned int id;
	vector<Node*> nodes;
};

class Graph
{
public:
	Graph();
	~Graph();

	bool findCycle();

	Node* createNode( unsigned int id );
private:
	vector<Node*> nodes;
};