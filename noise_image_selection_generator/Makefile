LIBRARIES = -l png -l boost_system -l boost_filesystem
FILES = filesystem.cpp random.cpp image.cpp

all: build

build: main.cpp random.hpp random.cpp image.hpp image.cpp generator.hpp filesystem.hpp filesystem.cpp args.hpp
	mkdir -p build
	g++ main.cpp $(FILES) $(LIBRARIES) -o build/noisgen

test: build_test
	./temp/test

build_test:
	mkdir -p temp
	g++ tests/test_main.cpp $(FILES) $(LIBRARIES) -o temp/test  -Wno-write-strings