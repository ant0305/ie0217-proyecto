CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = main1

all: $(TARGET)

$(TARGET): main1.cpp info.cpp funciones.cpp banco.cpp 
	$(CC) $(CFLAGS) -o $(TARGET) main1.cpp info.cpp funciones.cpp banco.cpp 

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.txt
