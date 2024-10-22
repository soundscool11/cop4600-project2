## COP4600 Operating Systems Project 2 ##

Files necessary to compile the program:
- main.cpp : main interface of the simulator, it takes user input in two forms
- FIFOCache.cpp : file that implements first-in first-out replacement policy
- LRUCache.cpp : file that implements least recently used policy

To compile the program:
1. You can use command "make" and it will compile all the files for you which creates memsim executable.
2. alternatively, you can also try "g++ -std=c++11 *.cpp -o memsim", to compile the program.

To run the program: 
The program can be run with two types of input format

For fifo and lru use the following format:
./memsim tracefile nFrames policy quiet/debug


__________Running Examples________________

./memsim bzip.trace 64 fifo quiet
total memory frames: 64
events in trace: 1000000
total disk reads: 1467
total disk writes: 514


./memsim bzip.trace 64 lru quiet
total memory frames: 64
events in trace: 1000000
total disk reads: 1264
total disk writes: 420

__________________________________________

where:
-policy: fifo, lru or vms
-percentage: 1-100
-tracefile: name of the tracefile (bzip.trace & sixpack.trace)
-nFrames: number of frames to use
-quiet/debug: quiet will just print the stats while debug will print every event that happens

This program was tested and compiled with no warnings under the student cluster
