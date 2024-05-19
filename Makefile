all: main run

main: main.o scanner.o parser.o
	g++ scanner.o main.o parser.o -o analisador_lexico
	

main.o:
	g++ -c main.cpp -o main.o

scanner.o:
	g++ -c scanner.cpp -o scanner.o

parser.o:
	g++ -c parser.cpp -o parser.o

run:
	./analisador_lexico main.mj

clean:
	rm main.o
	rm scanner.o