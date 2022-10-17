CC=g++

memsim: memsim.cpp LRUCache.cpp FIFOCache.cpp 
	$(CC) -std=c++11 -o memsim memsim.cpp LRUCache.cpp FIFOCache.cpp
