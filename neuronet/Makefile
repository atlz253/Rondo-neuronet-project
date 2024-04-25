LIBRARIES = -l png
TEMP_PATH = ../temp/neuronet
BUILD_PATH = ../build

all: build

run: build
	./build/neuronet

build: main.cpp softmax.hpp neuronet.hpp matrix.hpp linear_algebra.hpp activation_functions.hpp
	mkdir -p $(BUILD_PATH)
	g++ main.cpp $(LIBRARIES) -o $(BUILD_PATH)/neuronet

test: build_test
	./$(TEMP_PATH)/test

build_test:
	mkdir -p $(TEMP_PATH)
	g++ tests/test_main.cpp $(LIBRARIES) -o $(TEMP_PATH)/test