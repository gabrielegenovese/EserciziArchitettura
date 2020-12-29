VMtranslator: VMtranslator.o funz.o
	gcc -o VMtranslator VMtranslator.o funz.o

VMtranslator.o: VMtranslator.c funz.h
	gcc -c VMtranslator.c

funz.o: funz.c funz.h
	gcc -c funz.c
	
clean:
	rm *.o