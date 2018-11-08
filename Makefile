CXX=g++
CXXFLAGS=-std=c++11 -Wall -Werror -pthread

.PHONY:
all: demo

.PHONY:
clean:
	-rm -f demo *.o

demo: main.o
	$(CXX) $(CXXFLAGS) -o demo $^

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

