CXX = g++
override CXXFLAGS += -std=c++11 -O2 -g -Wall
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = -larmadillo $(shell pkg-config --libs gsl)

all: circuit.exe

data: resistance.txt

resistance.txt: circuit_01.exe
	./$^ > $@

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
	$(RM)  resistance.txt
