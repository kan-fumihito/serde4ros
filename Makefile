generate: generator.cc
	clang++ generator.cc -o generator -std=c++17
	./generator

main: main.cc src/std_msgs/*.cc src/primitives/*.cc include/std_msgs/*.h include/primitives/*.h
	clang++ main.cc src/std_msgs/*.cc src/primitives/*.cc -o main -Iinclude -std=c++17
	./main

all: generate main


