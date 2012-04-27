CC=avr32-linux-gcc
CFLAGS=-g -Wall -Iinclude 
LDFLAGS=-g -Wall -pedantic -Llib -lm -pthread
TARGET=game
OBJS=screen.o image.o led.o button.o sound.o ui.o scorched_land.o main.o

####### RULES ##########################################################
.PHONY : all
all: $(TARGET)

game: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : test
test:
	cd test; make

.PHONY : clean
clean :
	rm -rf *.o *.*~
