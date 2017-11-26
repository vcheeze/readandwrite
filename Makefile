all: reader writer creator destroyer

reader: reader.o
	g++ reader.o -o reader

writer: writer.o
	g++ writer.o -o writer

creator: creator.o
	g++ creator.o -o creator

destroyer: destroyer.o
	g++ destroyer.o -o destroyer

reader.o: reader.cpp
	g++ -c reader.cpp

writer.o: writer.cpp
	g++ -c writer.cpp

creator.o: creator.cpp
	g++ -c creator.cpp

destroyer.o: destroyer.cpp
	g++ -c destroyer.cpp

clean:
	rm -f *.o reader writer creator destroyer
