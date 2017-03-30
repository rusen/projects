# Define the symbols we might want to change:
CXX	:= c++

OBJECTS	:=  hw2.o

hw2: $(OBJECTS)
	$(CXX) -lGL -lGLU -lglut -lm $(OBJECTS) -o hw2	
	
hw1.o: hw2.cpp
	$(CXX) -c hw2.cpp -o hw2.o
	
clean:
	rm -rf *.o hw2