
#ifndef CONNECTION_ADVANCED_H
#define CONNECTION_ADVANCED_H

#include "connection.h"

class CloseStreamException : public std::exception
{};

class StreamConnection : public Connection
{
private:
	//Mutex to protect access to the queue
	boost::interprocess::interprocess_mutex mutex_;

	//Condition to wait when the queue is empty
	boost::interprocess::interprocess_condition cond_empty_;

	//Condition to wait when the queue is full
	boost::interprocess::interprocess_condition cond_full_;

	volatile bool value_in_;

	Value stream_value_;
	volatile bool isAlive_;
public:

	StreamConnection(int src_node, int dest_node);
	
	virtual bool isStream() const { return true;}
	virtual bool isAlive() const { return isAlive_ || value_in_;}
	void close();
	void open();
	virtual Value getValue();
	virtual void setValue(const Value &v);
};

class CacheConnection : public Connection
{
private:
	//Mutex to protect access to the cache
	boost::interprocess::interprocess_mutex mutex_;

	//Condition to wait when the cache is not yet filled empty
	boost::interprocess::interprocess_condition cond_cache_;

	bool bIsDirty_;
	Value cache_;
public:
	CacheConnection(int src_node, int dest_node);
	
	void setDirty();

	virtual Value getValue();
	virtual void setValue(const Value &v);
};

#endif //!CONNECTION_ADVANCED_H
