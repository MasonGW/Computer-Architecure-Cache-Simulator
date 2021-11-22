Homework 3: Cache Simulator 
Fall 2021 CS3339

**this was worked on in replit.com and that is why we are uploading it once**

~~ TEAM MEMBERS ~~
Jordan Finney
Mason Greenwell
Katelin Vincent

i. takes input
ii. configuration of parameters of a chache
iii. has a sequence of memory addresses requested by the CPU 

OUTPUT: ADDR : HIT/MISS 

1. each cache has a vaild bit and tag
2. at the outset, each cache is empty 
3. each cache entry/block contains one word
4. the given memory references are specified as word addresses 
5. num_entries is the total number of entries in the cache

BUILDME - 

to compile: clang++-7 -pthread -std=c++17 -o main main.cpp

To run: ./main entries associativity cache
- can change enteries and assciativity 

BUGS AND LIMITS - 
- cache size can not exceed 1000.
- must fill cache with 0's in order prevent code from reaching out of range. If any of the first X numbers from input are 0, will give a false hit.

