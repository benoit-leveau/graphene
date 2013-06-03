
#include "common.h"
#include "connection.h"
#include "NodeInterface.h"

Connection::Connection() : isConnected_(false), src_node_(-1), dest_node_(-1)
{
}

Connection::Connection(int src_node, int dest_node): 
    isConnected_(true),
    src_node_(src_node),
    dest_node_(dest_node)
{
}

