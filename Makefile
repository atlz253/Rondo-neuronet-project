LIBRARIES = png

all: build

run: build
	./build/neuronet

build: main.cpp
	mkdir -p build
	g++ main.cpp -l $(LIBRARIES) -o build/neuronet

test: build_test
	./temp/test

build_test:
	mkdir -p temp
	g++ tests/test_main.cpp -l $(LIBRARIES) -o temp/test image.cpp