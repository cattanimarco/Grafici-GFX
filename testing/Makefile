CSRC = $(wildcard *.c) \
	$(wildcard ../*.c) \
	$(wildcard ../decorators/*.c) \
	$(wildcard ../visitors/*.c) \

CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \
	$(wildcard ../decorators/*.cpp) \
	$(wildcard ../visitors/*.cpp) \

OBJ = $(CSRC:.c=.o) $(CCSRC:.cpp=.o)

CFLAGS=-I.

ifdef OS
	RM = del /Q
	FixPath = $(subst /,\,$(OBJ))
else
	ifeq ($(shell uname), Linux)
		RM = rm -f
		FixPath = $(OBJ)
	endif
endif

lib:
	gcc -O -c ../lib/ezdib.c

test: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ $(CFLAGS)

run: lib test
	@./test

.PHONY: clean

clean:$
	$(RM) $(FixPath) test
