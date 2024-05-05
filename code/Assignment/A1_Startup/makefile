CC=mpic++
CFLAGS=-I

LIBS=
OBJ=hello.o

%.o: %.cpp $(DEPS)
$(CC) -c -o $@ $< $(CFLAGS)

main : $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)

test1: $(OBJ)
    mpirun -np 4 ./hello

clean
    rm -f *.o*~core
    