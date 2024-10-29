CC=gcc

simulator: rr.o cfs.o
	$(CC) -o $@ $^ simul.c

rr.o:
	$(CC) -c -o $@ rr.c

cfs.o:
	$(CC) -c -o $@ cfs.c

clean:
	rm -rf simulator *.o