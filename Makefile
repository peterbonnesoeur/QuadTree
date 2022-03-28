make:	src/Quadtree.cpp src/bpPoint.cpp src/bpReadWrite.cpp
	g++ -std=c++11 -I headers src/*.cpp -o quadtree

clean:
	rm quadtree
