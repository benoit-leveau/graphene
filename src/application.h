
#ifndef APPLICATION_H
#define APPLICATION_H

class ClientGraph;

class LINKTYPE Application
{
public:
	Application();
	~Application();

	boost::shared_ptr<ClientGraph> createGraph();
};

#endif //!APPLICATION_H
