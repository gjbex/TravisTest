override CXXFLAGS += -std=c++14 -O2 -g -Wall
CPPFLAGS = $(shell pkg-config --cflags gsl)
LDFLAGS = $(shell pkg-config --libs gsl)

all: cannon.exe

test: trajectory.txt
	diff -q $< trajectory_target.txt 

trajectory.txt: cannon.exe
	./$^ > $@

%.exe: %.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $^

clean:
	$(RM) *.exe *.o
	$(RM) core core.*
	$(RM)  trajectory.txt
