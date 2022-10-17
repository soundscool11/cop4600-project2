#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <deque>

#include "FIFOCache.cpp"
#include "LRUCache.cpp"

using namespace std;

int totalEvents = 0;
int totalRead = 0;
int totalWrite = 0;
int pageFault = 0;
int pageHit = 0;


void fifo(FILE *tFile, int nframes, bool debugMode) {
    FIFOCache cache(nframes, debugMode);

    // track each line of the file and do page replacement process if necessary
    unsigned addr;
    char rw;

    while(!feof(tFile)) {

        fscanf(tFile, "%x %c\n", &addr, &rw);

        addr = addr >> 12; // since page size is 4KB == 2^12 bits == 4096 bits

        int pageNum = int(addr); // convert hex into int 

        int dirtyBit = 0; // unmodified(or read) = 0, modified = 1

        cache.update(addr, rw, dirtyBit);
    }

    fclose(tFile);

    totalEvents = cache.getEvents();
	totalRead = cache.getReads();
	totalWrite = cache.getWrites();
	pageFault = cache.getFaults();
	pageHit = cache.getHits();

    if(debugMode) {
        printf("\ntotal page hit: %d\n", pageHit);
        printf("total page fault: %d\n\n", pageFault);
    }
}


void lru(FILE *tFile, int nframes, bool debugMode) {

	LRUCache cache(nframes, debugMode);

	unsigned int address;
	char rw;

	while(!feof(tFile)) {

		fscanf(tFile, "%x %c\n", &address, &rw);

        address = address >> 12;

		int writeBit = (rw == 'W');

		if (debugMode) printf("Page: %d, bit: %d\n", address, writeBit);

		cache.update(address, writeBit);
		
	}

	fclose(tFile);

	totalEvents = cache.getEvents();
	totalRead = cache.getReads();
	totalWrite = cache.getWrites();
	pageFault = cache.getFaults();
	pageHit = cache.getHits();

	if(debugMode) {
        printf("\ntotal page hit: %d\n", pageHit);
        printf("total page fault: %d\n\n", pageFault);
    }   
}

void segmentedFifo(FILE *tFile, int nframes, int p, bool debugMode) {
    // SegmentedFIFOCache cache(nframes, p, debugMode);

	// unsigned int address;
	// char rw;

	// while(!feof(tFile)) {

	// 	fscanf(tFile, "%x %c\n", &address, &rw);

    //     address = address >> 12;

	// 	int writeBit = (rw == 'W');

	// 	if (debugMode) printf("Page: %d, bit: %d\n", address, writeBit);

	// 	cache.update(address, writeBit);
		
	// }

	// fclose(tFile);

	// totalEvents = cache.getEvents();
	// totalRead = cache.getReads();
	// totalWrite = cache.getWrites();
	// pageFault = cache.getFaults();
	// pageHit = cache.getHits();

	// if(debugMode) {
    //     printf("\ntotal page hit: %d\n", pageHit);
    //     printf("total page fault: %d\n\n", pageFault);
    // }   
}


int main(int argc, char** argv) {
    if(argc != 5 && argc != 6) {
        perror("Please enter the following arguments.\n");
        perror("memsim <tracefile> <nframes> <lru|fifo|vms> (<p> if vms) <debug|quite>");
        exit(0);
    }

    string tracefile = argv[1];
    int nframes = stof(argv[2]);
    string selectedAlgo = argv[3];
    string outputFormat = argv[argc-1];

    const char* traceFile = tracefile.c_str();
    FILE *tFile = fopen(traceFile, "r");

    if(tFile == NULL) {
        perror("File is empty. Please try again.\n");
        exit(0);
    }

    bool debugMode;
    if(outputFormat == "debug") {
        debugMode = true;
    } else if(outputFormat == "quiet") {
        debugMode = false;
    } else {
        perror("Please enter <debug|quiet> correctly.\n");
        exit(0);
    }

    if(selectedAlgo == "lru") {
        lru(tFile, nframes, debugMode);
    } else if(selectedAlgo == "fifo") {
        fifo(tFile, nframes, debugMode);
    } else if(selectedAlgo == "vms") {
        int p = stoi(argv[4]);
        segmentedFifo(tFile, nframes, p, debugMode);
    } else {
        perror("Please enter <lru|fifo|vms> correctly.\n");
        exit(0);
    }
    
    printf("total memory frames: %d\n", nframes);
    printf("events in trace: %d\n", totalEvents);
    printf("total disk reads: %d\n", totalRead);
    printf("total disk writes: %d\n", totalWrite);

    return 0;
}
