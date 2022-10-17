CC=g++

memsim: main.cpp LRUCache.cpp FIFOCache.cpp 
	$(CC) -std=c++11 -o memsim main.cpp LRUCache.cpp FIFOCache.cpp
