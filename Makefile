generate: generator.cc
	g++ generator.cc -o generator -std=c++17
	./generator

main: main.cc
	g++ main.cc src/*.cc -o main -Iinclude -std=c++17
	./main

all: main.cc generate
	g++ main.cc src/*.cc -o main -Iinclude -std=c++17
	./main
