CC=g++
CFLAGS=-c -fPIC -Wall -I/code/tpl/el6/gcc-4.4.6/boost/1.44.0/include -I../../src/
LDFLAGS=-shared
SOURCES=src/dllMain.cpp src/fileNodes.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=fileNodes.so
LIBRARY_PATH=../../bin/plugins

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(LIBRARY_PATH)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o
	rm -rf $(LIBRARY_PATH)/$(LIBRARY)
