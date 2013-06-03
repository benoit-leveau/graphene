BOOST_DIR=/code/tpl/el6/gcc-4.4.6/boost/1.44.0/
BOOST_THREAPOOL_DIR=/code/work/benoit/thirdparty/build

CC=g++
CFLAGS=-c -Wall -I$(BOOST_DIR)/include -I$(BOOST_THREAPOOL_DIR)/include
LDFLAGS=-L$(BOOST_DIR)/lib -lboost_thread -lboost_filesystem -lboost_system -ldl -Wl,-rpath=$(BOOST_DIR)/lib
SOURCES=src/application.cpp src/connection_advanced.cpp src/connection.cpp src/executeNode.cpp src/graph.cpp src/main.cpp src/NodeFactory.cpp src/PluginManager.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graphene
EXECUTABLE_PATH=bin

# add Debug Options
debug: CXX += -DDEBUG -g
debug: CC += -DDEBUG -g
debug: all

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
