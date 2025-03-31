all: neander

neander: neander.o
	gcc main.c libraries/neander.o -o main -g

neander.o:
	gcc libraries/neander.c -c -o libraries/neander.o

clean:
	rm libraries/neander.o
	rm out.mem
	rm main
	rm main.exe
