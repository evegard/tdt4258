CC=avr32-linux-gcc
CFLAGS=-g -Wall -Iinclude 
LDFLAGS=-g -Wall -pedantic -Llib -lm
TARGET=game

####### RULES ##########################################################
.PHONY : all
all: $(TARGET)

game: screen.o main.o
	$(CC) $^ -o $@ $(LDFLAGS)

screen.o: screen.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -rf *.o *.*~
