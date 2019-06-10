CC = gcc

EXEC=main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC)   -o main  main.c -L /usr/lib64 -lcjson

clean:
	rm -rf $(EXEC)