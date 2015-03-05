.PHONY : all
all: cmake
	$(MAKE) -s -C ./build

.PHONY : cmake
cmake: build
	cd ./build; cmake -DCMAKE_INSTALL_PREFIX=../install ..

build:
	mkdir ./build

.PHONY : clean
clean:
	rm -rf ./build
	rm -rf ./install

.PHONY : test
test: all
	$(MAKE) -s -C ./build test

.PHONY : tests
tests: test
