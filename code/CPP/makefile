CC=mpic++
CFLAGS=-I /usr/bin/
DEPS=
LIBS=
OBJ=hello.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test1: main
	mpirun -np 4 --allow-run-as-root ./main

test2: 
	mpirun -np 8 --allow-run-as-root ./main

test3: 
	mpirun -np 16 --allow-run-as-root  --oversubscribe ./main

clean:
	rm -f *.o *~ core main
