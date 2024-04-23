LIBRARIES = -l png

all: build

run: build
	./build/neuronet

build: main.cpp softmax.hpp neuronet.hpp matrix.hpp linear_algebra.hpp activation_functions.hpp
	mkdir -p build
	g++ main.cpp $(LIBRARIES) -o build/neuronet

test: build_test
	./temp/test

build_test:
	mkdir -p temp
	g++ tests/test_main.cpp $(LIBRARIES) -o temp/test