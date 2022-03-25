generate: generator.cc
	clang++ generator.cc -o generator -std=c++17
	./generator

main: main.cc
	clang++ main.cc src/*.cc -o main -Iinclude -std=c++17
	./main

all: main.cc generate
	clang++ main.cc src/*.cc -o main -Iinclude -std=c++17
	./main
