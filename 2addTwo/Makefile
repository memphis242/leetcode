.POSIX:

bench.exe: addTwo1.cpp addTwo2.cpp ListNodeType.cpp ListNodeType.hpp bench_testcases.cpp bench.cpp
	g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic --pedantic-errors -DBENCHMARK_STATIC_DEFINE -o bench.exe addTwo1.cpp addTwo2.cpp ListNodeType.cpp bench_testcases.cpp bench.cpp $(pkg-config --libs benchmark_main) -pthread -lshlwapi

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.exe
