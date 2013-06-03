
#include "common.h"
#include "fileNodes.h"
#include "connection.h"
#include <fstream>

FileNodeInterface *FileNodeInterface::instance()
{
	static FileNodeInterface instance;
	return &instance;
}

Node *FileNodeInterface::createNode()
{
	return new FileNode();
};

FileNode::FileNode()
{
}

void FileNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("FileNode::execute");
	boost::shared_ptr< Connection > filename(info->input_[0][0]);
	Value result;	
	if (filename->isConnected())
	{
		std::ifstream file(std::string(filename->getValue()).c_str());
		while (!file.eof ())
		{
			std::string line;
			std::getline (file, line);
			result = std::string(std::string(result) + line + "\n");
		}
		file.close();		
	}
	info->output_[0]->setValue(result);
}

StreamFileNodeInterface *StreamFileNodeInterface::instance()
{
	static StreamFileNodeInterface instance;
	return &instance;
}

Node *StreamFileNodeInterface::createNode()
{
	return new StreamFileNode();
};

StreamFileNode::StreamFileNode()
{
}

void StreamFileNode::execute(boost::shared_ptr< ConnectionInfo > info)
{ 
	OUTPUT("StreamFileNode::execute");
	boost::shared_ptr< Connection > filename_connection(info->input_[0][0]);
	if (filename_connection->isConnected())
	{
		std::string filename(filename_connection->getValue());
		std::ifstream file(filename.c_str());
		if (file.is_open())
		{
			while (!file.eof ())
			{
				std::string line;
				std::getline(file, line);
				info->output_[0]->setValue(line);
			}
			file.close();
		}
	}
}
