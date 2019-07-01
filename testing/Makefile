CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \
	$(wildcard ../widgets/*.cpp) \
	$(wildcard ../dataSet/*.cpp) \
	$(wildcard ../visitors/*.cpp) \

OBJ = $(CCSRC:.cpp=.o)

CFLAGS=-I.

ifdef OS
	RM = del /Q
	FixPath = $(subst /,\,$(OBJ))
	exec = test.exe
else
	RM = rm -f
	FixPath = $(OBJ)
	exec = test
endif

lib:
	gcc -O -c ../lib/ezdib.c

test: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ $(CFLAGS)

run: lib test
	@./test

.PHONY: clean

clean:$
	$(RM) $(FixPath) $(exec) prova.bmp
