
#ifndef GRAPH_H
#define GRAPH_H

#include "graphNode.h"
#include "connection_advanced.h"
#include "executeNode.h"
#include "clientGraph.h"

class PortOnNode
{
private:
	int id_node_;
	int id_port_;
public:
	PortOnNode() : id_node_(-1), id_port_(-1){}
	explicit PortOnNode(int id_node, int id_port) : id_node_(id_node), id_port_(id_port){}
	bool operator==(const PortOnNode &other) const
	{
		return (id_node_==other.id_node_ && id_port_==other.id_port_);
	}
	bool operator<(const PortOnNode &other) const
	{
		if (id_node_  < other.id_node_ || (id_node_ == other.id_node_ && id_port_ < other.id_port_))
			return true;
		return false;
	}
};

#define ROOT_NODE 0

class Graph : public ClientGraph
{
private:
	// data
	std::vector<boost::shared_ptr<GraphNode> > listOfNodes_;
	std::map<PortOnNode, PortOnNode> mapConnections_;
	std::map<PortOnNode, multiConnection> mapInputConnections_;
	std::map<PortOnNode, boost::shared_ptr<Connection> > mapOutputConnections_;

	// methods
	std::vector< multiConnection > getInputConnections(int id);
	multiConnection getOutputConnections(int id, bool bOnlySubOutputPorts);
	boost::shared_ptr<Connection> make_connection(boost::shared_ptr<GraphNode> src_node, int src_id, int src_port, boost::shared_ptr<GraphNode> dest_node, int dest_id, int dest_port);
	void addNode(boost::shared_ptr<GraphNode> node);

	// for streaming connections
	void closeInputOutputs(std::vector< multiConnection > &input, multiConnection &output);
	void closeMultiConnection(multiConnection &mC);
	bool checkStreamAlive(const std::vector< multiConnection > &input, multiConnection &output) const;
	void executeStreamingNode(int id, bool bSubExecute);

	// for normal connections
	void executeNode(int id, bool bSubExecute);

	// edit connections
	void setStream(int id_node);
	void setDirty(int id);

    friend void executeNode_threaded(size_t threadid, Graph *graph, int id, bool bSubExecute);
public:
	Graph();
	virtual ~Graph();

	virtual int addNode(ClassID id);

	virtual bool canConnect(int id_node1, int id_port1, int id_node2, int id_port2);
	virtual void connect(int id_node1, int id_port1, int id_node2, int id_port2);
	
	virtual void editNodeParameters(int id_node, const Value &setting);
	
	virtual void execute(int nb_threads);
};

#endif //!GRAPH_H
