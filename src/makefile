CC=gcc
CFLAGS=-c -Wall
LIB_SOURCES=library.c
LIB_OBJECTS=$(LIB_SOURCES:.c=.o)
LIB_NAME=libstring.a
EXEC=program

all: $(LIB_SOURCES) $(EXEC)

$(EXEC): main.o $(LIB_NAME)
	$(CC) -o $@ $< -L. $(LIB_NAME)

%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

$(LIB_NAME): $(LIB_OBJECTS)
	ar cr $@ $<

.PHONY: clean valgrind

clean:
	rm -f *.o $(LIB_NAME) $(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXEC)
