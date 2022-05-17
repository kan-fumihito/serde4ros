generate: generator.cc
	clang++ generator.cc -o generator -std=c++17
	mkdir -p include/std_msgs
	mkdir -p src/std_msgs
	./generator

test: test.cc src/std_msgs/*.cc src/primitives/*.cc include/std_msgs/*.h include/primitives/*.h
	clang++ test.cc src/std_msgs/*.cc src/primitives/*.cc -o test -Iinclude -std=c++17
	./test

all: generate test

clear:
	rm -r src/std_msgs
	rm -r include/std_msgs
