CSRC = $(wildcard *.c) \
	$(wildcard ../*.c) \

CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \

OBJ = $(CSRC:.c=.o) $(CCSRC:.cpp=.o)

CFLAGS=-I.

test: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

run: test
	@./test

.PHONY: clean
clean:
	rm -f $(obj) test
