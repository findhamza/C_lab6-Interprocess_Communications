CC = gcc
LIB = ar rcs

CFLAGS = -L. -I. -lm

LIBHDR = randapi seedRandGenerator
LIBOBJ = randapi.o seedRandGenerator.o
OBJ = enterprise.o libRandApi.a

all: libRandApi.a entsys

%.o: %.c $(LIBHDR)
	$(CC) -c -Wall $@ $< $(CFLAGS)

libRandApi.a: $(LIBOBJ)
	$(LIB) $@ $^

entsys: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
