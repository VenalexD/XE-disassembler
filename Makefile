CC = g++
CFLAGS = -c
TARGET = dxe

all: $(TARGET)

$(TARGET): main.o dxe.o opcode.o
	$(CC) main.o dxe.o opcode.o -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

dxe.o: dxe.cpp
	$(CC) $(CFLAGS) dxe.cpp

opcode.o: opcode.cpp
	$(CC) $(CFLAGS) opcode.cpp

clean:
	rm -f core *.o $(TARGET)