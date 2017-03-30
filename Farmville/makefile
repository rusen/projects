CC = g++
CFLAGS = -g
LIBS = -lGL -lGLU -lglut -lm BMPLoader.cpp -Wall

hw3: hw3.o
	$(CC) $(CFLAGS) $(LIBS) -o hw3 hw3.o

hw3.o: hw3.cpp
	$(CC) $(CFLAGS) -c hw3.cpp

clean:
	rm -rf *o hw3


