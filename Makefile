CC=g++

memsim: main.cpp LRUCache.cpp FIFOCache.cpp
	$(CC) -o memsim main.cpp LRUCache.cpp FIFOCache.cpp
