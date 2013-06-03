CC=g++
CFLAGS=-c -Wall -I/code/tpl/el6/gcc-4.4.6/boost/1.44.0/include -I/code/work/benoit/thirdparty/build/include
LDFLAGS=-L/code/tpl/el6/gcc-4.4.6/boost/1.44.0/lib -lboost_thread -lboost_filesystem -lboost_system -ldl
SOURCES=src/application.cpp src/connection_advanced.cpp src/connection.cpp src/executeNode.cpp src/graph.cpp src/main.cpp src/NodeFactory.cpp src/PluginManager.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graphene
EXECUTABLE_PATH=bin

all: $(SOURCES) $(EXECUTABLE) nodes
	mkdir -p bin/plugins

nodes:
	cd plugins && $(MAKE) all

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE_PATH)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o
	rm -rf $(EXECUTABLE_PATH)/$(EXECUTABLE)
	cd plugins && $(MAKE) $(MAKEFLAGS) $@
