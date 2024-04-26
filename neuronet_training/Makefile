LIBRARIES = -l png
TEMP_PATH = ../temp/neucat
BUILD_PATH = ../build

all: build

build: main.cpp help_message.hpp option_parser.hpp
	mkdir -p $(BUILD_PATH)
	g++ main.cpp $(LIBRARIES) -o $(BUILD_PATH)/neucat
