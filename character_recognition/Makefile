LIBRARIES = -l png
BUILD_PATH = ../build

all: build

build: main.cpp
	mkdir -p $(BUILD_PATH)
	g++ main.cpp ../common/image/image.cpp weights.cpp $(LIBRARIES) -o $(BUILD_PATH)/spchar