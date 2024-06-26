#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

void saveIncludeHierarchy(const IncludeMap& includeMap, const std::string& outputPath) {
	std::ofstream outFile(outputPath);
	if (!outFile.is_open()) {
		std::cerr << "Failed to open output file: " << outputPath << std::endl;
		return;
	}

	for (const auto& [file, includes] : includeMap) {
		outFile << file << " includes:\n";
		for (const auto& include : includes) {
			outFile << "  " << include << "\n";
		}
		outFile << "\n";
	}

	outFile.close();
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <directory> <output_file>" << std::endl;
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
	saveIncludeHierarchy(includeMap, outputPath);

	std::cout << "Include hierarchy saved to " << outputPath << std::endl;

	return 0;
}

