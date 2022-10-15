## COP4600 Operating Systems Project 2 ##

The project requirements are described in p2-memsim.pdf. Use memory traces that are stored in two files:

bzip.trace.zip and sixpack.trace.zip. You are to implement a page replacement algorithm presented in this paper.

Files necessary to compile the program:
- memsim.c : main interface of the simulator, it takes user input in two forms
- fifo.c: file that implements first-in first-out replacement policy
- lru.c: file that implements least recently used policy
- vms.c: file that implements segmented-fifo polciy
- dataStructures.c: file that initializes the data structures necessary to run the program such as the page table

In addition to that the folder must also include policies.h, and dataStructures.h. The first one declares the policies
previously mentioned to be used by the simulator, and the second one makes the dataStructures accessible to all the
policies. Also, make sure to include any trace file to be tested in the same directory as well.


To compile the program:
1. You can use command "make" and it will compile all the files for you which creates memsim executable.
2. alternatively, you can also try "gcc -o memsim memsim.c fifo.c lru.c vms.c dataStructures.c", to compile the
program.

To run the program:
The program can be run with two types of input format
1. For fifo and lru use the following format:
./memsim tracefile nFrames policy quiet/debug
2. For segmented fifo use the following format:
./memsim tracefile nframes policy percentage quiet/debug


__________Running Examples________________
./memsim bzip.trace 64 fifo quiet
total memory frames: 64
events in trace: 1000000
total disk reads: 1467
total disk writes: 514

./memsim bzip.trace 64 vms 0 quiet
Memory Frames: 64
Trace Count: 1000000
Read Count: 1467
Write Count: 514

./memsim bzip.trace 64 vms 25 quiet
Memory Frames: 64
Trace Count: 1000000
Read Count: 1367
Write Count: 471

./memsim bzip.trace 64 vms 50 quiet
Memory Frames: 64
Trace Count: 1000000
Read Count: 1290
Write Count: 427

./memsim bzip.trace 64 vms 75 quiet
Memory Frames: 64
Trace Count: 1000000
Read Count: 1267
Write Count: 416

./memsim bzip.trace 64 vms 100 quiet
Memory Frames: 64
Trace Count: 1000000
Read Count: 1264
Write Count: 420

./memsim bzip.trace 64 lru quiet
total memory frames: 64
events in trace: 1000000
total disk reads: 1264
total disk writes: 420
__________________________________________

where:
-policy: fifo, lru or vms
-percentage: 1-100
-tracefile: name of the tracefile
-nFrames: number of frames to use
- quiet/debug: quiet will just print the stats while debug will print every event that happens
This program was tested and compiled with no warnings under the student cluster
