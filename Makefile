INCLUDES=-I./SeqLib -I./SeqLib/htslib
CPPFLAGS=$(INCLUDES) -MMD -MP

LIBS+=-lz -lbz2 ./SeqLib/src/libseqlib.a ./SeqLib/htslib/libhts.a ./SeqLib/bwa/libbwa.a
CXXFLAGS+=-W -Wall -Wno-nested-anon-types -Wno-sign-compare -pedantic -std=c++14 -O3 

SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:.cpp=.o)
DEP=$(OBJECTS:.o=.d)  # one dependency file for each source

TARGET=seqtools

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS) $(LDLIBS)

# c++ source
src/%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(binaries) $(OBJS) *~ $(DEPS) $(TARGET)

-include $(DEPS)
