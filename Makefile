CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic
#CFLAGS+=-g
CFLAGS+=-O2
LDLIBS=-lpcap
#DEFINES=-DDEBUG

TARGET=ipk-sniffer
OBJS= main.o packet_handler.o argumets.o header_display.o

LOGIN=xdohun00

############################################

.PHONY: all clean run pack valgrind debug

############################################

all: $(TARGET)

run: $(TARGET)
	./$< -i wlp3s0 --icmp

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(DEFINES)

clean:
	rm -f *.o $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$<

debug: $(TARGET)
	gdb -tui ./$<

pack:
	rm -f $(LOGIN).tar
	tar -cvf $(LOGIN).tar Makefile *.c *.h README.md manual.pdf
