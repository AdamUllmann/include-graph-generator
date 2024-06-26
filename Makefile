# Makefile
all: code_to_dot

code_to_dot: code_to_dot.cpp
	g++ -std=c++17 -o code_to_dot code_to_dot.cpp

clean:
	rm -f code_to_dot
