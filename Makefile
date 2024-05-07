all: main run

main: main.o scanner.o
	g++ scanner.o main.o -o analisador_lexico
	

main.o:
	g++ -c main.cpp -o main.o

scanner.o:
	g++ -c scanner.cpp -o scanner.o

run:
	./analisador_lexico main.mj

clean:
	rm main.o
	rm scanner.o