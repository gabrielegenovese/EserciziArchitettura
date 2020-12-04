assembler: assembler.o funz.o
	gcc -o assembler assembler.o funz.o

assembler.o: assembler.c funz.h
	gcc -c assembler.c

funz.o: funz.c funz.h
	gcc -c funz.c
	
clean:
	rm *.o