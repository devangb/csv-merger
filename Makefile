all: mergecsv.cpp
	g++ -o mergecsv mergecsv.cpp

clean:
	rm mergecsv