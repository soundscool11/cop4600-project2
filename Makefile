CC=g++

memsim: main.cpp LRUCache.cpp FIFOCache.cpp SegmentedFIFOCache.cpp
	$(CC) -o memsim main.cpp LRUCache.cpp FIFOCache.cpp SegmentedFIFOCache.cpp
