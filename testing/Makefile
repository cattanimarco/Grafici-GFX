ARDUINO_DIR = ~/Documents/Arduino/libraries/Grafici
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
	rm -f -r $(ARDUINO_DIR)
	mkdir $(ARDUINO_DIR)
	cp ../Data.cpp $(ARDUINO_DIR)
	cp ../Data.h $(ARDUINO_DIR)
	cp ../Display.cpp $(ARDUINO_DIR)
	cp ../Display.h $(ARDUINO_DIR)
	cp ../Grafici.cpp $(ARDUINO_DIR)
	cp ../Grafici.h $(ARDUINO_DIR)
	cp -r ../color_schemes $(ARDUINO_DIR)
	cp -r ../plotters $(ARDUINO_DIR)
	cp -r ../decorators $(ARDUINO_DIR)
	cp -r ../datasets $(ARDUINO_DIR)
	cp -r ../examples $(ARDUINO_DIR)

.PHONY: clean

clean:$
	$(RM) $(FixPath) $(exec) prova.bmp
