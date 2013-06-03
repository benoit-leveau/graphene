
#ifndef CONNECTION_H
#define CONNECTION_H

#include "value.h"
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

class Graph;
class Node;
class Value;

class Connection
{
private:
	bool isConnected_;
public:
	int src_node_;
	int dest_node_;

	Connection();
	Connection(int src_node, int dest_node);
	virtual ~Connection(){}
	
	bool isConnected() const {return isConnected_;}

	virtual void setDirty(){}
	virtual bool isDirty() const { return true;}
	virtual bool isStream() const { return false;}
	virtual Value getValue(){ return Value();}
	virtual void setValue(const Value &v){}
};

typedef std::vector< boost::shared_ptr< Connection > > multiConnection;

class ConnectionInfo
{
public:
      std::vector<multiConnection> &input_;
      multiConnection &output_;

      ConnectionInfo(std::vector< multiConnection > &input, multiConnection &output) : input_(input), output_(output){}
	  virtual ~ConnectionInfo(){}
};

#endif //!CONNECTION_H
