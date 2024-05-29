TARGET = houghlines

CFLAGS = -Ofast -Wall -std=c++11 `pkg-config --cflags opencv`
LDFLAGS = -Ofast -Wall -std=c++11 `pkg-config --libs opencv`
CC = g++

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) *.a *.o *~

