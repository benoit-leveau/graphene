CC=g++
CFLAGS=-c -fPIC -Wall -I/milk/code/central/include/centos7/gcc-6.3.0/ -I../../src/ -std=c++11 -Wno-deprecated
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
