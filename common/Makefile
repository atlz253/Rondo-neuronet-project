TEMP_PATH = ../temp/common
TEST_LIBRARIES = -l png
TEST_FILES = image/image.cpp

all: test

test: build_test
	./$(TEMP_PATH)/test

build_test:
	mkdir -p $(TEMP_PATH)
	g++ tests/test_main.cpp $(TEST_FILES) $(TEST_LIBRARIES) -o $(TEMP_PATH)/test -Wno-write-strings