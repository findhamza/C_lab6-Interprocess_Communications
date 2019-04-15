CC = gcc

CFLAGS = -L. -I. -lm

NOBJ = ent_nav.o libRandApi.a
LOBJ = ent_life.o libRandApi.a
EOBJ = ent_bridge.o libRandApi.a

all: navigation lifesupport bridge

navigation: $(NOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

lifesupport: $(LOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

bridge: $(EOBJ)
	$(CC) -o $@ $^ $(CFLAGS)
