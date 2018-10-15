INCLUDES = interface.o AuxInterface.o parser.o BaseBTree.o Colaborator.o 
CC = gcc
CFLAGS = -Wall -std=c11 -g 
XMLCFLAGS = `xml2-config --cflags`  
LIBS2 = `xml2-config --libs`


all: includes program

includes: interface.o AuxInterface.o parser.o BaseBTree.o Colaborator.o

interface.o:
	$(CC) $(XMLCFLAGS) $(CFLAGS) -c  interface.c

AuxInterface.o:
	$(CC) $(XMLCFLAGS) -c $(CFLAGS) AuxInterface.c

parser.o:
	$(CC) $(XMLCFLAGS) -c $(CFLAGS) parser.c

BaseBTree.o:
	$(CC) -c $(CFLAGS) BaseBTree.c 

Colaborator.o:
	$(CC) -c $(CFLAGS) Colaborator.c

program: $(INCLUDES)
	$(CC)  $(XMLCFLAGS) $(CFLAGS) $(INCLUDES) program.c -o program $(LIBS2)


run: program
	./program

clean:
	rm *.o
	rm program

