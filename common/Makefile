TEMP_PATH = ../temp/common

all: test

test: build_test
	./$(TEMP_PATH)/test

build_test:
	mkdir -p $(TEMP_PATH)
	g++ tests/test_main.cpp -o $(TEMP_PATH)/test -Wno-write-strings