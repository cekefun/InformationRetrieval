all: bsbi printer

bsbi: bsbi.o
	g++ bsbi.o -o bsbi

bsbi.o:
	g++ -c bsbi.cpp -o bsbi.o


printer: printer.o
	g++ printer.o -o printer

printer.o:
	g++ -c printer.cpp -o printer.o

clean:
	rm -rf bsbi *.o printer
