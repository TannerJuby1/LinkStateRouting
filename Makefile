
CXXFLAGS = -g -std=c++11 
OBJS = LinkStateRouting.o LinkStateRouting

all:
	g++ LinkStateRouting.cpp -o LinkStateRouting

LinkStateRouting: LinkStateRouting.cpp
	g++ LinkStateRouting.cpp -o LinkStateRouting -c $(CXXFLAGS)

clean:
	rm -f $(OBJS)
