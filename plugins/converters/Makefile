CC=g++
CFLAGS=-c -fPIC -Wall -I/Users/benoit/Documents/Prog/libs/include -I../../src
LDFLAGS=-shared -L/Users/benoit/Documents/Prog/libs/lib -lboost_system
SOURCES=src/dllMain.cpp src/converters.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=converters.so
LIBRARY_PATH=../../bin/plugins

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(LIBRARY_PATH)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o
	rm -rf $(LIBRARY_PATH)/$(LIBRARY)
