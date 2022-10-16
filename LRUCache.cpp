# include <list>
# include <unordered_map>
# include <iostream>

class LRUCache {

private:

	int events = 0;
	int reads = 0;
	int writes = 0;
	int faults = 0;
	int hits = 0;

public:

	std::list<unsigned int> queue;
	std::unordered_map<unsigned int, std::list<unsigned int>::iterator> queueMap; // page -> page pos in queue
	std::unordered_map<unsigned int, int> readWriteMap;


	int capacity;
	bool debug;

	
	LRUCache(int n, bool debugMode) {
		capacity = n;
		debug = debugMode;
	}

	int getEvents() {return events;}
	int getReads() {return reads;}
	int getWrites() {return writes;}
	int getFaults() {return faults;}
	int getHits() {return hits;}


	void update(unsigned int targetPage, int readWriteBit) {

		events++;

		if (queueMap.find(targetPage) != queueMap.end()) { // If page has been cached

			hits++;

			if (debug) {
				printf("CASE 1 (Page already in cache) - Time: %d, Page Number: %d\n", events, targetPage);
			}
			

			readWriteMap[targetPage] = readWriteMap[targetPage] || readWriteBit;
			
			queue.erase(queueMap[targetPage]); // Remove from queueMap (age is wrong)
			
		} else {

			readWriteMap[targetPage] = readWriteBit;
			
			if (queue.size() == capacity) { // If page not cached AND cache is at cap

				faults++;
				reads++;
	
				if (debug) {
					printf("CASE 3 (Page not in cache AND cache full) - Time: %d, Page Number: %d\n", events, targetPage);
				}
				
				unsigned int lastPage = queue.back();
	
				int dirtyBit = readWriteMap[lastPage];

				if (debug) {
					printf("Popping page %d\n", lastPage);
				}
	
				if (dirtyBit) {
					writes++;
					if (debug) {
						printf("Popped page is a write\n");
					}
				}
	
				readWriteMap.erase(lastPage);
	
				queue.pop_back();
	
				queueMap.erase(lastPage);
			}

		}

		if (debug) {
			printf("ALWAYS CASE (Occurs regardless of if CASES 1 or 2 were met) - Time: %d, Page Number: %d\n", events, targetPage);
		}

		queue.push_front(targetPage);

		queueMap[targetPage] = queue.begin();
		
	}


};