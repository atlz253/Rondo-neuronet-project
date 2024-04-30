LIBRARIES = -l png
BUILD_PATH = ../build
PACKAGES_PATH = ../packages

all: build

build_deb: build
	mkdir -p package/usr/bin
	cp $(BUILD_PATH)/spchar package/usr/bin/spchar
	mkdir -p $(PACKAGES_PATH)
	dpkg-deb --build ./package $(PACKAGES_PATH)/spchar.deb

build: main.cpp
	mkdir -p $(BUILD_PATH)
	g++ main.cpp ../common/image/image.cpp weights.cpp $(LIBRARIES) -o $(BUILD_PATH)/spchar