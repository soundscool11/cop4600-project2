#include <deque>
#include <stdio.h>

using namespace std;

class FIFOCache {
    private:
        int events = 0;
        int reads = 0;
        int writes = 0;
        int faults = 0;
        int hits = 0;

    public:
        deque<pair<int, int>> pageTable; // <page number, dirty bit>

        int capacity;
        bool debug;

        FIFOCache(int n, bool debugMode) {
            capacity = n;
            debug = debugMode;
        }

        int getEvents() {return events;}
        int getReads() {return reads;}
        int getWrites() {return writes;}
        int getFaults() {return faults;}
        int getHits() {return hits;}

        void update(unsigned int targetPage, char rw, int dirtyBit) {
            events++;
            int pageExists = 0;
            for(int i = 0; i < pageTable.size(); i++) {
                // case 1: page is in the FIFO page table (when page hit occurs)
                // solution: update write (dirty bit 0 -> 1) if "W" encountered
                if(pageTable[i].first == targetPage) {
                    pageExists = 1;
                    hits++;

                    if(debug) printf("Event time: %d, Page Number: %d - ", events, targetPage);

                    if(rw == 'W') { 
                        pageTable[i].second = 1; // replace the "R" with "W"
                        if(debug) printf("Dirty bit: 0 -> 1 / ", targetPage);
                    }

                    if(debug) printf("Page hit time: %d", hits);
                
                    break;
                }
            }

            // case 2: page is not in page table and page table is not full
            // solution: push a new page at the end of page table
            if(pageExists == 0 && pageTable.size() != capacity) {
                reads++;
                faults++;

                if(debug) printf("Event time: %d, Page Number: %d - ", events, targetPage);

                if(rw == 'W') { 
                    dirtyBit = 1; // replace the "R" with "W"
                    //if(debug) printf("Dirty bit: 0 -> 1 / ", targetPage);
                }

                pageTable.push_back(make_pair(targetPage, dirtyBit));

                if(debug) printf("Push\n");
            }

            // case 3: page is not in page table and page table is full 
            // solution: pop from the front and push the new page at the end of the page table
            else if(pageExists == 0 && pageTable.size() == capacity) {
                faults++;
                reads++;

                if(debug) printf("Event time: %d, Page Number: %d - ", events, targetPage);

                if(rw == 'W') { 
                    dirtyBit = 1; // replace the "R" with "W"
                    if(debug) printf("Dirty bit: 0 -> 1 / ", targetPage);
                }

                if(pageTable.front().second == 1) {
                    // if "W", then increase write count
                    writes++;
                    if(debug) printf("Frame with W saved to disk / ");
                }

                pageTable.pop_front();
                pageTable.push_back(make_pair(targetPage, dirtyBit));

                if(debug) printf("Page fault time: %d\n", faults);
            }
        }
};