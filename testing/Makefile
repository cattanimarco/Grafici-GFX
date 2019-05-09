CSRC = $(wildcard *.c) \
	$(wildcard ../*.c) \
	$(wildcard ../widgets/*.c) \

CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \
	$(wildcard ../widgets/*.cpp) \
	$(wildcard ../drivers/*File.cpp) \
	$(wildcard ../visitors/*Cout.cpp) \

OBJ = $(CSRC:.c=.o) $(CCSRC:.cpp=.o)

CFLAGS=-I.

test: $(OBJ) ../lib/ezdib.o
	$(CXX) -o $@ $^ $(CFLAGS)

run: test
	@./test

.PHONY: clean
clean:
	rm -f $(OBJ) test
