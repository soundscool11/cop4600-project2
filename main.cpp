#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>

using namespace std;

void fifo(string tracefile, int nframe) {
  
}


void lru(string tracefile, int nframe) {
  printf("smth");
}


void segmentedFifo(string tracefile, int nframe, float p) {
  
}


int main(int argc, char** argv) {
  if(argc != 5 && argc != 6) {
    printf("Please enter the following arguments.\n");
    printf("./memsim <tracefile> <nframes> <lru|fifo|vms> (<p> if vms) <debug|quite>");
    exit(0);
  }

  string tracefile = argv[1];
  int nframe = stof(argv[2]);
  string selectedAlgo = argv[3];
  string outputFormat = argv[argc-1];

  if(selectedAlgo == "lru") {
    lru(tracefile, nframe);
  } else if(selectedAlgo == "fifo") {
    fifo(tracefile, nframe);
  } else if(selectedAlgo == "vms") {
    int p = stoi(argv[4]);
    segmentedFifo(tracefile, nframe, p);
  } else {
    printf("Please enter <lru|fifo|vms> correctly.\n");
    exit(0);
  }
   
  if(outputFormat == "debug") {
    
  } else if(outputFormat == "quite") {
    
  } else {
    printf("Please enter <debug|quiet> correctly.\n");
    exit(0);
  }

  return 0;
}