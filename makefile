CC=g++
CFLAGS=-c -Wall --std=c++11
LDFLAGS=
SOURCES=Main.cpp Line.cpp TestArea.cpp RayTracer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ra

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE) *~
