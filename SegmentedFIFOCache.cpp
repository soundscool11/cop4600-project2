// #include <utility>
// #include <stdio.h>

// class SegmentedFIFOCache {
//     private:
//         int events = 0;
//         int reads = 0;
//         int writes = 0;
//         int faults = 0;
//         int hits = 0;

//     public:
//         std::pair <int, char> pair_first;
//         std::pair <int, char> pair_second;

//         bool inList1 = false;
//         bool inList2 = false;

//         int size_of_secondary;
//         int size_of_primary;
//         bool debug;

//         SegmentedFIFOCache(int n, int p, bool debugMode) {
//             size_of_secondary = (n * p) / 100;
//             size_of_primary = n - size_of_secondary;
//             debug = debugMode
//         }

//         int getEvents() {return events;}
//         int getReads() {return reads;}
//         int getWrites() {return writes;}
//         int getFaults() {return faults;}
//         int getHits() {return hits;}

//         void update(unsigned int targetPage, char rw, int dirtyBit) {
//             // const int targetPage, const char h, const int num, int &write, int &read, int p1
//             if (size_of_primary == 0) {
//                 lru(tFile, nframes, debugMode);
//                 return ;
//             }
//             else if (size_of_secondary == 0) {
//                 fifo(tFile, nframes, debugMode);
//                 return ;
//             }
//             else {
//                 std::pair <int, char> pair_first;
//                 std::pair <int, char> pair_second;

//                 bool inList1 = false;
//                 bool inList2 = false;

//                 pair_first = std::make_pair(targetPage, h);

//                 for (iter1 = Address_list.begin(); iter1 != Address_list.end(); iter1++) {
//                     if (iter1->first == pair_first.first){
//                         inList1 = true;
//                         if (iter1->second == 'R' && pair_first.second == 'W') 
//                         {
//                             iter1->second = 'W';  break;
//                         }
//                         }
//                         }
//                 if (inList1 == false) {
//                     if (Address_list.size() < primarySize) {
//                         Address_list.push_back(pair_first);
//                     }
//                     else {

//                         std::pair<int, char> tmp_Pair;
//                         std::pair<int, char> tmp_Pair2;

//                         tempPair = Address_list.front();


//                         for (iter2 = LRU_list.begin(); iter2 != LRU_list.end(); iter2++) //for loop
//                         {

//                             if(iter2->first == pair_first.first) 
//                             {
//                                 inList2 = true;
//                                 if ((pair_first.second == 'W' && iter2->second == 'R')) {
//                                     iter2->second = 'W';
//                                 }
//                                 Address_list.pop_front();
//                                     LRU_list.erase(iter2);
//                                 Address_list.push_back(pair_first);
//                                 LRU_list.push_back(tmp_Pair);
//                                 break;
//                                 }
//                                 }
//                         if(inList2 == false) 
//                         {
//                         read++;
//                             if (LRU_list.size() < Size_of_secondary) 
//                             {
//                                 Address_list.pop_front();
//                                 LRU_list.push_back(tmp_Pair);
//                             }

//                             else{
//                                 if (tmp_Pair.second == 'W'){
//                                     write++;
//                             }
//                             LRU_list.pop_front();
//                             LRU_list.push_back(tmp_Pair);
//                             Address_list.pop_front();
//                             Address_list.push_back(pair_first);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
// };
