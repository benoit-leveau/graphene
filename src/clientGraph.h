
#ifndef CLIENTGRAPH_H
#define CLIENTGRAPH_H

class LINKTYPE ClientGraph
{
public:
	virtual int addNode(ClassID id) = 0;

	virtual void editNodeParameters(int id_node, const Value &setting) = 0;

	virtual bool canConnect(int id_node1, int id_port1, int id_node2, int id_port2) = 0;
	virtual void connect(int id_node1, int id_port1, int id_node2, int id_port2) = 0;

	virtual void execute(int nb_threads) = 0;
};

#endif //!CLIENTGRAPH_H
