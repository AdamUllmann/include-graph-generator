#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace fs = std::filesystem;

using IncludeMap = std::unordered_map<std::string, std::unordered_set<std::string>>;

void processFile(const fs::path& filePath, IncludeMap& includeMap, const fs::path& rootDir) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return;
	}

	std::string line;
	std::regex includeRegex(R"(^\s*#\s*include\s*["<](.*)[">])");
	std::smatch match;

	std::string relativeFilePath = fs::relative(filePath, rootDir).string();

	while (std::getline(file, line)) {
		if (std::regex_search(line, match, includeRegex)) {
			std::string includeFile = match[1].str();
			includeMap[relativeFilePath].insert(includeFile);
		}
	}

	file.close();
}

void traverseDirectory(const fs::path& directory, IncludeMap& includeMap) {
	for (const auto& entry : fs::recursive_directory_iterator(directory)) {
		if (entry.is_regular_file() && (entry.path().extension() == ".c" || entry.path().extension() == ".cpp" || entry.path().extension() == ".h" || entry.path().extension() == ".hpp")) {
			processFile(entry.path(), includeMap, directory);
		}
	}
}

void generateDotFile(const IncludeMap& includeMap, const std::string& outputPath) {
	std::ofstream outFile(outputPath);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open output file: " << outputPath << std::endl;
		return;
	}

	outFile << "digraph IncludeHierarchy {" << std::endl;
	outFile << "  rankdir=LR;" << std::endl;
	outFile << "  nodesep=0.5;" << std::endl;
	outFile << "  ranksep=1.2;" << std::endl;
	outFile << "  node [shape=ellipse, style=filled, fillcolor=lightgrey, fontsize=10];" << std::endl;
	outFile << "  edge [color=black];" << std::endl;

	for (const auto& [file, includes] : includeMap) {
		for (const auto& include : includes) {
			outFile << "  \"" << file << "\" -> \"" << include << "\";" << std::endl;
		}
	}

	outFile << "}" << std::endl;

	outFile.close();
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <directory> <output_dot_file>" << std::endl;
		return 1;
	}

	fs::path directory = argv[1];
	std::string outputPath = argv[2];

	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		std::cerr << "The provided path is not a valid directory." << std::endl;
		return 1;
	}

	IncludeMap includeMap;
	traverseDirectory(directory, includeMap);
	generateDotFile(includeMap, outputPath);

	std::cout << "DOT file saved to " << outputPath << std::endl;

	return 0;
}

