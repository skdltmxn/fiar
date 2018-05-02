CC = g++
CFLAGS = -Wall -O3 -std=c++14
OUTPUT = fiar
OBJS = fiar.o main.o
HDRS = fiar.h gameboard.h

all: prepare build

clean:
	rm -rf obj; rm -rf bin

prepare:
	mkdir -p obj
	mkdir -p bin

build: $(OBJS)
	$(CC) -o bin/$(OUTPUT) $(addprefix obj/, $^)

$(OBJS): %.o: %.cpp $(HDRS)
	$(CC) -c $(CFLAGS) -o obj/$@ $<
