INCLUDES=-I./SeqLib -I./SeqLib/htslib 
LIBS=./SeqLib/src/libseqlib.a ./SeqLib/htslib/libhts.a 
CXXFLAGS=-W -Wall -pedantic -std=c++14 

binaries=rgtools

all: rgtools.o
	g++ rgtools.o -O3 -g -o rgtools $(LIBS) -lpthread -lz -lm 

rgtools.o: rgtools.cpp
	g++ -g -c -O3 rgtools.cpp $(INCLUDES) $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(binaries) *.o
