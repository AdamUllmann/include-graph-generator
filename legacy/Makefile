# legacy
all: include_hierarchy generate_dot

include_hierarchy: include_hierarchy.cpp
	g++ -std=c++17 -o include_hierarchy include_hierarchy.cpp
generate_dot: generate_dot.cpp
	g++ -std=c++17 -o generate_dot generate_dot.cpp
clean:
	rm include_hierarchy && rm generate_dot
