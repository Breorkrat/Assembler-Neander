OBJECTS=libraries/neander.o
CFLAGS=-Wall

all: neander

neander: $(OBJECTS)
	gcc main.c ${CFLAGS} ${OBJECTS} -o main

%.o:%.c
	gcc -c -o $@ $^

clean:
	@rm -f out.mem $(OBJECTS) main main.exe
