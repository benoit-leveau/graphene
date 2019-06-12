#BOOST_DIR=/code/tpl/el6/gcc-4.4.6/boost/1.44.0/
#BOOST_THREAPOOL_DIR=/code/work/benoit/thirdparty/build

CC=g++
CFLAGS=-c -Wall -I/milk/code/central/include/centos7/gcc-6.3.0/ -I/milk/users/benoit/pwork/ubik/thirdparty/ctpl/
LDFLAGS=-L/milk/code/central/lib/centos7/gcc-6.3.0/ -lboost_thread -lboost_filesystem -lboost_system -ldl -Wl,-rpath=/milk/code/central/lib/centos7/gcc-6.3.0/ -lpthread
SOURCES=src/application.cpp src/connection_advanced.cpp src/connection.cpp src/executeNode.cpp src/graph.cpp src/main.cpp src/NodeFactory.cpp src/PluginManager.cpp
#SOURCES=src/application.cpp src/connection_advanced.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graphene
EXECUTABLE_PATH=bin

# add Debug Options
debug: CXX += -DDEBUG -g
debug: CC += -DDEBUG -g
debug: all

CXX += -std=c++11 -Wno-deprecated
CC  += -std=c++11 -Wno-deprecated

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
