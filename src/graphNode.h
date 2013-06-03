
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "NodeInterface.h"

class GraphNode
{
private:
	int id_;
	boost::shared_ptr<Node> node_;
public:
	GraphNode(boost::shared_ptr<Node> node) : id_(-1), node_(node){}

	boost::shared_ptr<Node> node(){return node_;};

	void setId(int id){id_ = id;}
	int getId(){return id_;}
};

#endif //!GRAPHNODE_H
