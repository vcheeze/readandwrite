all: reader writer manager

reader: reader.o
	g++ reader.o -o reader

writer: writer.o
	g++ writer.o -o writer

manager: main.o
	g++ main.o -o manager

reader.o: reader.cpp
	g++ -c reader.cpp

writer.o: writer.cpp
	g++ -c writer.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o reader writer
