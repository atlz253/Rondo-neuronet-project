all: build

run: build
	./build/neuronet

build:
	mkdir -p build
	g++ main.cpp -o build/neuronet
