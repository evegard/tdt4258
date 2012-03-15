CC=avr32-gcc
CFLAGS=-g -Wall -Iinclude 
LDFLAGS=-g -Wall -pedantic -Llib -lavr32b-interrupts -lm
TARGET=ex2.elf


# Command to upload program to flash 
AVR32PROGRAM = avr32program

####### RULES ##########################################################
.PHONY : all
all: $(TARGET)

ex2.elf: ex2.o sound.o melody.o
	$(CC) $^ -o $@ $(LDFLAGS)

ex2.o: ex2.c 
	$(CC) $(CFLAGS) -c $< -o $@

sound.o: sound.c 
	$(CC) $(CFLAGS) -c $< -o $@

melody.o: melody.c 
	$(CC) $(CFLAGS) -c $< -o $@

# upload to STK1000 (program flash)
.PHONY : upload
upload : $(TARGET)
	$(AVR32PROGRAM) halt
	sleep 1
	$(AVR32PROGRAM) program -e -f0,8Mb $<

.PHONY : clean
clean :
	rm -rf *.o *.elf *.*~
