tube : main.o tube.o
	g++ -Wall -g main.o tube.o -o tube

main.o: main.cpp tube.h
	g++ -Wall -g main.cpp -c

tube.o : tube.cpp tube.h
	g++ -Wall -g tube.cpp -c

clean:
	rm -r *.o main

