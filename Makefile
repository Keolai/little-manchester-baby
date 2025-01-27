all: clean build

build:
	gcc main.cpp -o baby -g

clean:
	rm -f baby