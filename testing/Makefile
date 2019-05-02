CC=g++
CFLAGS=-I.
DEPS = DriverCout.h
OBJ = test.o DriverCout.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: test
	@./test

.PHONY: clean

clean: 
	rm *.o
