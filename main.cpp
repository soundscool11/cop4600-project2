#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <deque>

using namespace std;

int totalEvents = 0;
int totalRead = 0;
int totalWrite = 0;
int pageFault = 0;
int pageHit = 0;

void fifo(FILE *tFile, int nframes, bool debugMode) {
    deque<pair<int, int>> pageTable; // <page number, dirty bit>

    // track each line of the file and do page replacement process if necessary
    unsigned addr;
    char rw;

    while(!feof(tFile)) {
        fscanf(tFile, "%x %c\n", &addr, &rw);
        totalEvents++;

        int dirtyBit = 0; // unmodified(or read) = 0, modified = 1
        addr = addr >> 12; // since page size is 4KB == 2^12 bits == 4096 bits
        int pageNum = int(addr); // convert hex into int 

        // case 1: page is in the FIFO page table (when page hit occurs)
        // solution: update write (dirty bit = 1) if "W" encountered
        int pageExist = 0;
        for(int i = 0; i <= pageTable.size(); i++) {
            if(pageTable[i].first == pageNum) {
                pageExist = 1;
                pageHit++;

                if(debugMode) printf("Case 1) Event time: %d, Page Number: %d, Page hit time: %d - ", totalEvents, pageNum, pageHit);

                if(rw == 'W') { 
                    pageTable[i].second = 1; // replace the "R" with "W"
                    if(debugMode) printf("The dirty bit of page number %d has been changed to 1. / ", pageNum);
                }

                if(debugMode) printf("The page number %d already in the page table.\n", pageNum);
            
                break;
            }
        }

        // case 2: page is not in page table and page table is not full
        // solution: push a new page at the end of page table
        if(pageExist == 0 && pageTable.size() != nframes) {
            pageTable.push_back(make_pair(pageNum, dirtyBit));

            if(debugMode) {
                printf("Case 2) Event time: %d, Page Number: %d - ", totalEvents, pageNum);
                printf("Page table is not full. A new page has been pushed.\n");
            }
        }

        // case 3: page is not in page table and page table is full (when page fault occurs) 
        // solution: pop from the front and push the new page at the end of the page table
        else if(pageExist == 0 && pageTable.size() == nframes) {
            pageFault++;
            totalRead++;

            if(debugMode) printf("Case 3) Event time: %d, Page Number: %d, Page fault time: %d - ", totalEvents, pageNum, pageFault);

            if(pageTable.front().second == 1) {
                // if "W", then increase write count
                totalWrite++;
                if(debugMode) printf("Frame with Write saved to disk. / ");
            }

            pageTable.pop_front();
            pageTable.push_back(make_pair(pageNum, dirtyBit));

            if(debugMode) printf("The first page is popped and the page number %d is pushed.\n", pageNum);
        }
        
    }

    fclose(tFile);

    if(debugMode) {
        printf("\ntotal page hit: %d\n", pageHit);
        printf("total page fault: %d\n\n", pageFault);
    }    
}

void lru(FILE *tFile, int nframes, bool debugMode) {

}


void segmentedFifo(FILE *tFile, int nframes, float p, bool debugMode) {
  
}


int main(int argc, char** argv) {
    if(argc != 5 && argc != 6) {
        perror("Please enter the following arguments.\n");
        perror("./memsim <tracefile> <nframes> <lru|fifo|vms> (<p> if vms) <debug|quite>");
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
