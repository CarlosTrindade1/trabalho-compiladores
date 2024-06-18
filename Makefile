all: main run

main: main.o scanner.o parser.o
	g++ scanner.o main.o parser.o -o minijava_compiler
	

main.o:
	g++ -c main.cpp -o main.o

scanner.o:
	g++ -c scanner.cpp -o scanner.o

parser.o:
	g++ -c parser.cpp -o parser.o

run:
	./minijava_compiler main.mj

clear:
	rm main.o
	rm scanner.o
	rm parser.o
	rm minijava_compiler