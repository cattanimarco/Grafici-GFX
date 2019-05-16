CSRC = $(wildcard *.c) \
	$(wildcard ../*.c) \
	$(wildcard ../widgets/*.c) \
	$(wildcard ../visitors/*.c) \

CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \
	$(wildcard ../widgets/*.cpp) \
	$(wildcard ../drivers/*File.cpp) \
	$(wildcard ../visitors/*.cpp) \

OBJ = $(CSRC:.c=.o) $(CCSRC:.cpp=.o)

CFLAGS=-I.

lib:
	gcc -g -O -c ../lib/ezdib.c

test: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ $(CFLAGS)

run: lib test
	@./test

.PHONY: clean
clean:
	rm -f $(OBJ) test
