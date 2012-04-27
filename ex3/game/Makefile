CC=avr32-linux-gcc
CFLAGS=-g -Wall -Iinclude 
LDFLAGS=-g -Wall -pedantic -Llib -lm -pthread
TARGET=game

####### RULES ##########################################################
.PHONY : all
all: $(TARGET)

game: screen.o image.o led.o button.o sound.o melody.o ui.o scorched_land.o main.o
	$(CC) $^ -o $@ $(LDFLAGS)

screen.o: screen.c
	$(CC) $(CFLAGS) -c $< -o $@

image.o: image.c
	$(CC) $(CFLAGS) -c $< -o $@

led.o: led.c
	$(CC) $(CFLAGS) -c $< -o $@

button.o: button.c
	$(CC) $(CFLAGS) -c $< -o $@

sound.o: sound.c
	$(CC) $(CFLAGS) -c $< -o $@

melody.o: melody.c
	$(CC) $(CFLAGS) -c $< -o $@

ui.o: ui.c
	$(CC) $(CFLAGS) -c $< -o $@

scorched_land.o: scorched_land.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -rf *.o *.*~
