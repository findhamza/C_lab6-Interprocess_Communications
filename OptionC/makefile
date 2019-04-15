CC = gcc
LIB = ar rcs

CFLAGS = -L. -I. -lm

LIBHDR = randapi seedRandGenerator
LIBOBJ = randapi.o seedRandGenerator.o
OBJ = enterprise.o libRandApi.a

all: libRandApi.a enterprise

%.o: %.c $(LIBHDR)
	$(CC) -c -Wall $@ $< $(CFLAGS)

libRandApi.a: $(LIBOBJ)
	$(LIB) $@ $^

enterprise: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
