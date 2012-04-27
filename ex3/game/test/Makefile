CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-g -Wall -lm 
TARGET=sc_land
OBJS=sc_land.o scorched_land.o

####### RULES ##########################################################
.PHONY : all
all: $(TARGET) clean

sc_land: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

scorched_land.o: ../scorched_land.c
	$(CC) $(CFLAGS) -c $< -o $@

sc_land.o: sc_land.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o

.PHONY: purge
purge: clean
	rm -f $(TARGET)
