OBJECTS=libraries/neander.o

all: neander

neander: $(OBJECTS)
	gcc main.c ${OBJECTS} -o main

%.o:%.c
	gcc -c -o $@ $^

clean:
	@rm -f out.mem $(OBJECTS) main main.exe
