
#include "common.h"
#include "boost_time_util.h"
#include "connection_advanced.h"
#include <boost/thread/condition_variable.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

StreamConnection::StreamConnection(int src_node, int dest_node) : 
	Connection(src_node, dest_node), 
	value_in_(false),
	isAlive_(false)
{}

void StreamConnection::close()
{
	cond_empty_.notify_one();
	cond_full_.notify_one();
	isAlive_ = false;
}

void StreamConnection::open()
{
	isAlive_ = true;
	value_in_ = false;
	stream_value_ = Value();
}

void StreamConnection::setValue(const Value &v)
{
	boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
	if (value_in_)
	{
		while (isAlive_ && value_in_)
		{
			cond_full_.timed_wait(lock, delay(0,100));
		}
		if (!isAlive_)
			throw CloseStreamException();
	}

	// write value to cache
	stream_value_ = v;

	// unlock readers
	cond_empty_.notify_one();
	value_in_ = true;
}

Value StreamConnection::getValue()
{
	boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
	if (!value_in_)
	{
		while(isAlive_ && !value_in_)
		{
			cond_empty_.timed_wait(lock, delay(0,100));
		}
		if (!value_in_)
			throw CloseStreamException();
	}
	
	// read cached value
	Value tmp;
	std::swap(tmp, stream_value_);

	// unlock writers
	value_in_ = false;
	cond_full_.notify_one();
	return tmp;
}

// ---

CacheConnection::CacheConnection(int src_node, int dest_node) : Connection(src_node, dest_node), bIsDirty_(true)
{}

void CacheConnection::setDirty()
{
	if (!bIsDirty_)
	{
		bIsDirty_ = true;
		cache_ = Value();
	}
}

void CacheConnection::setValue(const Value &v)
{
	boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);

	// write value to cache
	cache_ = v;

	// unlock readers
	cond_cache_.notify_one();
	bIsDirty_ = false;
}

Value CacheConnection::getValue()
{
	boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
	if (bIsDirty_)
		cond_cache_.wait(lock);
	
	return cache_;
}
	
