LIBRARIES = -l png -l boost_system -l boost_filesystem
FILES = filesystem.cpp random.cpp ../image.cpp

all: build

build: main.cpp args.hpp generator.hpp
	mkdir -p build
	g++ main.cpp $(FILES) $(LIBRARIES) -o build/noise_selection_generator

test: build_test
	./temp/test

build_test:
	mkdir -p temp
	g++ tests/test_main.cpp $(FILES) $(LIBRARIES) -o temp/test  -Wno-write-strings