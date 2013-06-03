
#include "common.h"
#include "graph.h"
#include "NodeFactory.h"
#include <boost/threadpool.hpp>

namespace interfaces
{
	ExecuteNodeInterface executeNodeInterface_;
}

Graph::Graph()
{
	NodeFactory::instance().hook(&interfaces::executeNodeInterface_);	
	addNode(CID_EXECUTE_NODE);
}

Graph::~Graph()
{
	NodeFactory::instance().unhook(&interfaces::executeNodeInterface_);
}

void Graph::addNode(boost::shared_ptr<GraphNode> node)
{
	int todo_use_atomicint_for_node_ids;
	node->setId(int(listOfNodes_.size()));
	listOfNodes_.push_back(node);
}

boost::shared_ptr<Connection> Graph::make_connection(boost::shared_ptr<GraphNode> src_node, int src_id, int src_port, boost::shared_ptr<GraphNode> dest_node, int dest_id, int dest_port)
{
	//bool bSubExecuteDest = (dest_port >= dest_node->node()->getNbInputPort());
	//bool bSubExecuteSrc = (src_port >= src_node->node()->getNbOutputPort());
	// boost::function0<void> func_execute = boost::bind(&Graph::executeNode, this, src_id, bSubExecuteSrc);
	bool bIsStream = src_node->node()->getOutputPortStream(src_port);
	bool bNoneOutput = (src_node->node()->getOutputPortValueType(src_port) == VALUE_NONE);
	if (bIsStream)
	{
		setStream(dest_id);
		return boost::shared_ptr<Connection>(new StreamConnection(src_id, dest_id));
	}
	else if (bNoneOutput)
		return boost::shared_ptr<Connection>(new Connection(src_id, dest_id));
	else
		return boost::shared_ptr<Connection>(new CacheConnection(src_id, dest_id));
}

void Graph::connect(int src_id, int src_port, int dest_id, int dest_port)
{
	if (!canConnect(src_id, src_port, dest_id, dest_port))
		return;
	
	PortOnNode port_src(src_id, src_port);
	PortOnNode port_dest(dest_id, dest_port);
	std::map<PortOnNode, PortOnNode>::iterator it = mapConnections_.find(port_src);
	if (it != mapConnections_.end())
	{
		PortOnNode existing_dest((*it).second);

		if (existing_dest == port_dest)
			return; // connection already exists
		
		// disconnect existing connection
		// ...
	}

	boost::shared_ptr<GraphNode> src_node(listOfNodes_[src_id]);
	boost::shared_ptr<GraphNode> dest_node(listOfNodes_[dest_id]);
	boost::shared_ptr<Connection> connect = make_connection(src_node, src_id, src_port, dest_node, dest_id, dest_port);
	mapOutputConnections_[port_src] = connect;

	mapConnections_[port_src] = port_dest;
	if (dest_node->node()->getInputPortConnectionType(dest_id) == CONNECTION_SINGLE)
	{
		multiConnection connectList;
		connectList.push_back(connect);
		mapInputConnections_[port_dest] = connectList;
	}
	else
	{
		std::map<PortOnNode, multiConnection>::iterator it2 = mapInputConnections_.find(port_dest);
		if (it2 != mapInputConnections_.end())
		{
			(*it2).second.push_back(connect);
		}
		else
		{
			multiConnection connectList;
			connectList.push_back(connect);
			mapInputConnections_[port_dest] = connectList;
		}
	}

	bool bSubPort = dest_port >= dest_node->node()->getNbInputPort();
	if (!bSubPort)
		setDirty(dest_id);
}

void Graph::editNodeParameters(int id_node, const Value &setting)
{
	boost::shared_ptr<GraphNode> node(listOfNodes_[id_node]);
	node->node()->editParameters(setting);
	setDirty(id_node);
}

void Graph::setStream(int id_node)
{
	multiConnection connections = getOutputConnections(id_node, false);
	for (multiConnection::iterator it = connections.begin(); it != connections.end(); ++it)
	{
		boost::shared_ptr<Connection> connection(*it);
		int todo_make_iterative;
		if (connection->isConnected())
		{
			if (!connection->isStream())
			{
				int src_node = connection->src_node_;
				int dest_node = connection->dest_node_;
				boost::shared_ptr<Connection> stream = boost::shared_ptr<Connection>(new StreamConnection(src_node, dest_node));
				bool bFound = false;
				PortOnNode p;
				for (std::map<PortOnNode, boost::shared_ptr<Connection> >::iterator it2 = mapOutputConnections_.begin(); it2 != mapOutputConnections_.end(); ++it2)
				{
					boost::shared_ptr<Connection> &c((*it2).second);
					if (c.get() == connection.get())
					{
						bFound = true;
						p = (*it2).first;
						break;
					}
				}
				if (bFound)
					mapOutputConnections_[p]= stream;
				bFound = false;
				for (std::map<PortOnNode, multiConnection>::iterator it2 = mapInputConnections_.begin(); it2 != mapInputConnections_.end(); ++it2)
				{
					multiConnection &mC((*it2).second);
					for (std::vector< boost::shared_ptr< Connection > >::iterator it3 = mC.begin(); it3 != mC.end(); ++it3)
					{
						boost::shared_ptr< Connection > &c(*it3);
						if (c.get() == connection.get())
						{
							bFound = true;
							p = (*it2).first;
							mC.erase(it3);
							break;
						}
					}
					if (bFound)
						break;
				}
				if (bFound)
					mapInputConnections_[p].push_back(stream);
			}
			int todo_check_if_destination_port_is_subexecute_port;
			bool bSubExecuteDest = false; // (dest_port >= dest_node->node()->getNbInputPort());
			if (!bSubExecuteDest)
				setStream(connection->dest_node_);
		}
	}
}

void Graph::setDirty(int id_node)
{
	multiConnection connections = getOutputConnections(id_node, false);
	for (multiConnection::iterator it = connections.begin(); it != connections.end(); ++it)
	{
		boost::shared_ptr<Connection> connection(*it);
		connection->setDirty();
		int todo_make_iterative;
		
		if (connection->isConnected())
		{
			int todo_check_if_destination_port_is_subexecute_port;
			bool bSubExecuteDest = false; // (dest_port >= dest_node->node()->getNbInputPort());
			if (!bSubExecuteDest)
				setDirty(connection->dest_node_);
		}
	}
}

std::vector< multiConnection > Graph::getInputConnections(int id)
{
	boost::shared_ptr<GraphNode> node(listOfNodes_[id]);
	std::vector< multiConnection > connections;
	int nb_ports = node->node()->getNbInputPort();
	for (int i=0; i<nb_ports; ++i)
	{
		PortOnNode port(id, i);
		std::map<PortOnNode, multiConnection>::iterator it = mapInputConnections_.find(port);
		if (it!=mapInputConnections_.end())
		{
			connections.push_back((*it).second);
		}
		else
		{
			boost::shared_ptr<Connection> connect(new Connection());
			multiConnection connectList;
			connectList.push_back(connect);
			connections.push_back(connectList);
		}
	}
	int nb_sub_ports = node->node()->getNbSubInputPort();
	for (int i=0; i<nb_sub_ports; ++i)
	{
		PortOnNode port(id, nb_ports + i);
		std::map<PortOnNode, multiConnection>::iterator it = mapInputConnections_.find(port);
		if (it!=mapInputConnections_.end())
		{
			connections.push_back((*it).second);
		}
		else
		{
			boost::shared_ptr<Connection> connect(new Connection());
			multiConnection connectList;
			connections.push_back(connectList);
		}
	}
	return connections;
}

multiConnection Graph::getOutputConnections(int id, bool bOnlySubOutputPorts)
{
	boost::shared_ptr<GraphNode> node(listOfNodes_[id]);
	multiConnection connections;
	int nb_ports = node->node()->getNbOutputPort();
	int nb_sub_ports = node->node()->getNbSubOutputPort();
	int nb_ports_to_fill = bOnlySubOutputPorts ? nb_sub_ports : nb_ports + nb_sub_ports;
	for (int i=0; i<nb_ports_to_fill; ++i)
	{
		PortOnNode port(id, i);
		std::map<PortOnNode, boost::shared_ptr<Connection> >::iterator it = mapOutputConnections_.find(port);
		if (it!=mapOutputConnections_.end())
		{
			connections.push_back((*it).second);
		}
		else
		{
			boost::shared_ptr<Connection> connect(new Connection());
			connections.push_back(connect);
		}
	}
	return connections;
}

bool Graph::checkStreamAlive(const std::vector< multiConnection > &input, multiConnection &output) const
{
	for (std::vector< multiConnection >::const_iterator it = input.begin(); it != input.end(); ++it)
	{
		const multiConnection &multi(*it);
		for (multiConnection::const_iterator it2 = multi.begin(); it2 != multi.end(); ++it2)
		{
			boost::shared_ptr< Connection > connection(*it2);
			if (connection->isConnected() && connection->isStream())
			{
				StreamConnection *stream = dynamic_cast<StreamConnection *>(connection.get());
				if (stream && stream->isAlive())
				{
					// one stream is still alive
					return true;
				}
			}
		}
	}
	// no more alive streams, close output stream
	for (multiConnection::iterator it = output.begin(); it != output.end(); ++it)
	{
		boost::shared_ptr< Connection > connection(*it);
		if (connection->isConnected() && connection->isStream())
		{
			StreamConnection *stream = dynamic_cast<StreamConnection *>(connection.get());
			if (stream && stream->isAlive())
			{
				stream->close();
			}
		}
	}	
	return false;
}


void Graph::closeMultiConnection(multiConnection &mC)
{
	for (multiConnection::iterator it = mC.begin(); it != mC.end(); ++it)
	{
		boost::shared_ptr< Connection > connection(*it);
		if (connection->isConnected() && connection->isStream())
		{
			StreamConnection *stream = dynamic_cast<StreamConnection *>(connection.get());
			stream->close();
		}
	}
}

void Graph::closeInputOutputs(std::vector< multiConnection > &input, multiConnection &output)
{
	closeMultiConnection(output);
	for (std::vector< multiConnection >::iterator it = input.begin(); it != input.end(); ++it)
	{
		closeMultiConnection(*it);
	}
}

void Graph::executeStreamingNode(int id, bool bSubExecute)
{
	std::vector< multiConnection > input(getInputConnections(id));
	multiConnection output(getOutputConnections(id, bSubExecute));
	boost::shared_ptr< ConnectionInfo > connectionInfo(new ConnectionInfo(input, output));
	try
	{
		while(checkStreamAlive(input, output))
		{
			if (bSubExecute)
				listOfNodes_[id]->node()->subExecute(connectionInfo);
			else
				listOfNodes_[id]->node()->execute(connectionInfo);
		}
	}
	catch(CloseStreamException &e)
	{
	}
	catch(...)
	{
		std::cout << "Catched exception!" << std::endl;
	}
	closeInputOutputs(input, output);
}

void Graph::executeNode(int id, bool bSubExecute)
{
	std::vector< multiConnection > input(getInputConnections(id));
	multiConnection output(getOutputConnections(id, bSubExecute));
	boost::shared_ptr< ConnectionInfo > connectionInfo(new ConnectionInfo(input, output));
	try
	{
		if (bSubExecute)
			listOfNodes_[id]->node()->subExecute(connectionInfo);
		else
			listOfNodes_[id]->node()->execute(connectionInfo);
	}
	catch(...)
	{
		std::cout << "Catched exception!" << std::endl;
	}
	closeInputOutputs(input, output);
}

void Graph::execute(int nb_threads)
{
	OUTPUT("executing graph...");
	std::vector<int> tasks, streaming_tasks;
	std::vector<int> nodes_to_visit;
	nodes_to_visit.push_back(ROOT_NODE);
	while(nodes_to_visit.size())
	{
		int id_current_node = nodes_to_visit.front();
		std::swap(nodes_to_visit.front(), nodes_to_visit.back());
		nodes_to_visit.pop_back();
		std::vector< multiConnection > inputs = getInputConnections(id_current_node);
		multiConnection outputs = getOutputConnections(id_current_node, false);
		bool bStreamOutput = false;
		for (std::vector< multiConnection >::iterator it = inputs.begin(); it != inputs.end(); ++it)
		{
			multiConnection &input(*it);
			for (multiConnection::iterator it2 = input.begin(); it2 != input.end(); ++it2)
			{
				boost::shared_ptr< Connection > connection(*it2);
				if (connection->isConnected() && connection->isStream())
				{
					StreamConnection *stream = dynamic_cast<StreamConnection *>(connection.get());
					stream->open();
					bStreamOutput = true;
				}
			}
		}
		if (bStreamOutput)
			streaming_tasks.push_back(id_current_node);
		else
			tasks.push_back(id_current_node);
		for (std::vector< multiConnection >::iterator it = inputs.begin(); it != inputs.end(); ++it)
		{
			multiConnection &input(*it);
			for (multiConnection::iterator it2 = input.begin(); it2 != input.end(); ++it2)
			{
				boost::shared_ptr< Connection > connection(*it2);
				if (connection->isConnected() && connection->isDirty())
				{
					nodes_to_visit.push_back(connection->src_node_);
				}
			}
		}
	}

	std::cout << "Executing " << tasks.size() << " nodes..." << std::endl;
	std::cout << "Executing " << streaming_tasks.size() << " nodes in streaming mode..." << std::endl;

	std::vector< boost::shared_ptr< boost::thread > > streaming_threads;
	for (std::vector<int>::const_iterator it = streaming_tasks.begin(); it != streaming_tasks.end(); ++it)
	{
		boost::shared_ptr< boost::thread > thread(new boost::thread(boost::bind(&Graph::executeStreamingNode, this, *it, false)));
		streaming_threads.push_back(thread);
	}

	{
		boost::threadpool::pool pool(nb_threads);
		for (std::vector<int>::const_reverse_iterator it = tasks.rbegin(); it != tasks.rend(); ++it)
		{
			pool.schedule(boost::bind(&Graph::executeNode, this, *it, false));
		}
		pool.wait();
	}

	// wait for end of all threaded tasks
	for (std::vector< boost::shared_ptr< boost::thread > >::iterator it = streaming_threads.begin(); it != streaming_threads.end(); ++it)
	{
		boost::shared_ptr< boost::thread > thread(*it);
		thread->join();
	}

	std::cout << "finished executing nodes!" << std::endl;

	OUTPUT("done executing graph!");
}

int Graph::addNode(ClassID id)
{
	boost::shared_ptr<Node> node(NodeFactory::instance().createNode(id));
	if (node)
	{
		boost::shared_ptr<GraphNode> graphNode(new GraphNode(node));
		addNode(graphNode);
		return graphNode->getId();
	}
	return -1;
}

bool Graph::canConnect(int id_node1, int id_port1, int id_node2, int id_port2)
{
	int size = int(listOfNodes_.size());
	if (id_node1 < 0 || id_node1 >= size || id_node2 < 0 || id_node2 >= size)
		return false;

	boost::shared_ptr<GraphNode> src(listOfNodes_[id_node1]);
	if (id_port1 >= (src->node()->getNbOutputPort() + src->node()->getNbSubOutputPort()))
		return false;

	boost::shared_ptr<GraphNode> dest(listOfNodes_[id_node2]);
	if (id_port2 >= (dest->node()->getNbInputPort() + dest->node()->getNbInputPort()))
		return false;

	ValueType src_type = src->node()->getOutputPortValueType(id_port1);
	ValueType dest_type = dest->node()->getInputPortValueType(id_port2);
	
	int allowedOutput = src->node()->allowedOutputTypes(id_port1);
	int allowedInput = dest->node()->allowedInputTypes(id_port2);
	if (src_type == VALUE_DYNAMIC && allowedOutput == 0)
	{
		// all kind of types are handled
		return true;
	}
	else if (dest_type == VALUE_DYNAMIC && allowedInput == 0)
	{
		// all kind of types are handled
		return true;
	}
	else if (src_type == VALUE_DYNAMIC)
	{
		if (dest_type == VALUE_DYNAMIC)
		{
			return ((allowedOutput & allowedInput) != 0);
		}
		else
		{
			return ((allowedOutput & 1<<dest_type) != 0);
		}
	}
	else if (dest_type == VALUE_DYNAMIC)
	{
		return ((allowedInput & 1<<src_type) != 0);
	}
	else
		return (src_type == dest_type);
}
