CXX = g++
CXXFLAGS = -pedantic -Wall -W -ansi -g
CXXOBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(CXXOBJS)
	$(CXX) $(CXXFLAGS) $(CXXOBJS) -o astar

clean:
	rm -fR *.o

%.o: %.cpp %.h
	$(CXX) -c -o $@ $<
%.o: %.cpp
	$(CXX) -c -o $@ $<

