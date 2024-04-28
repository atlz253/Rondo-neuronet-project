LIBRARIES = -l png -l boost_system -l boost_filesystem
FILES = filesystem.cpp random.cpp ../common/image/image.cpp
TEMP_PATH = ../temp/noisgen
BUILD_PATH = ../build

all: build

build: main.cpp random.hpp random.cpp generator.hpp filesystem.hpp filesystem.cpp help_message.hpp options_parser.hpp
	mkdir -p $(BUILD_PATH)
	g++ main.cpp $(FILES) $(LIBRARIES) -o $(BUILD_PATH)/noisgen

test: build_test
	./$(TEMP_PATH)/test

build_test:
	mkdir -p $(TEMP_PATH)
	g++ tests/test_main.cpp $(FILES) $(LIBRARIES) -o $(TEMP_PATH)/test