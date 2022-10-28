CC=g++
CFLAGS=-I. -g
DEPS = assembler.h
OBJ = ./build/assembler.o ./build/main.o 

./build/%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@  $(CFLAGS)

assembler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

all: assembler

.PHONY: clean

clean:
	rm assembler
	rm ./build/*.o