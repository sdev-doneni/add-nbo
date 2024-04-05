all : add-nbo

add-nbo : main.cpp
	g++ -o add-nbo main.cpp

clean :
	rm -f add-nbo
	rm -f *.o
