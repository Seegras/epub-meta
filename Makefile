CC=gcc
DEBUG = -g
EXEC=epub-meta
LDFLAGS = -Wall $(DEBUG) -lpopt -lepub
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

epub-meta: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm *.o

mrproper: clean
	@rm $(EXEC)
