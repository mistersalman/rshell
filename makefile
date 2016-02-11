CC = g++
CC_FLAGS = -Wall -ansi -Werror -pedantic 
EXEC = rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	mkdir bin
	$(CC) $(OBJECTS) -o $(EXEC)
	mv ./rshell bin
	mv src/main.o bin

all: $(OBJECTS)
	mkdir bin
	$(CC) $(OBJECTS) -o $(EXEC)
	mv ./rshell bin
	mv src/main.o bin

rshell: $(OBJECTS)
	mkdir bin
	$(CC) $(OBJECTS) -o $(EXEC)
	mv ./rshell bin
	mv src/main.o bin

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -r bin
