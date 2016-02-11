CC = g++
CC_FLAGS = -Wall -ansi -Werror -pedantic 
EXEC = rshell.out
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	mkdir bin
	$(CC) $(OBJECTS) -o $(EXEC)
	mv rshell.out bin
	mv src/main.o bin

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -r bin
