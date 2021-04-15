# naught
T4240 Cache Coherence Identification Benchmark Library

This code base has two components: the benchmarking code itself and a small Python tool to analyze the content of caches.
It also requires CodeWarrior to compile and flash on the T4240.

Check out https://drops.dagstuhl.de/opus/volltexte/2020/12376/pdf/LIPIcs-ECRTS-2020-13.pdf for an explanation of the context.

The main file is in https://github.com/nsensfel/naught/blob/master/Sources/main.c. The `main` function indicates what stable states should be reached by the caches prior to the benchmark being performed as well as the instruction to perform on each cache.

Upon performing an execution (which performs the same benchmark over 8000 elements multiple time with different events being monitored), the results are retrieved in two places:
* The standard output console gives information about each of the performance monitor. To interpret the numbers, see the order of the events written in: https://github.com/nsensfel/naught/blob/master/Sources/bench/three_ways_omnibenchs.c
* CodeWarrior can be used to extract the state of all caches. Giving the file corresponding to the state of a cache as sole parameter to the https://github.com/nsensfel/naught/blob/master/cache_state_extractor.py script will list the stable coherence states it found.
