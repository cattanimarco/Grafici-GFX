CCSRC = $(wildcard *.cpp) \
	$(wildcard ../*.cpp) \
	$(wildcard ../dataSet/*.cpp) \

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

arduino: lib test
	rm -f -r arduino
	mkdir arduino
	cp ../Data.cpp arduino/
	cp ../Data.h arduino/
	cp ../Display.cpp arduino/
	cp ../Display.h arduino/
	cp ../Grafici.cpp arduino/
	cp ../Grafici.h arduino/
	cp -r ../colorSchemes arduino/
	cp -r ../drawVisitors arduino/
	cp -r ../dataset arduino/
	cp -r ../examples arduino/

.PHONY: clean

clean:$
	$(RM) $(FixPath) $(exec) prova.bmp
