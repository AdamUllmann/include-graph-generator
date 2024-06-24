#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

void parseHierarchy(const std::string& inputPath, std::unordered_map<std::string, std::unordered_set<std::string>>& includeMap) {
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputPath << std::endl;
        return;
    }

    std::string line;
    std::string currentFile;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.find(" includes:") != std::string::npos) {
            currentFile = line.substr(0, line.find(" includes:"));
        } else if (!currentFile.empty()) {
            std::string includeFile = line.substr(2);
            includeMap[currentFile].insert(includeFile);
        }
    }

    inputFile.close();
}

void generateDotFile(const std::unordered_map<std::string, std::unordered_set<std::string>>& includeMap, const std::string& outputPath) {
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputPath << std::endl;
        return;
    }

    outFile << "digraph IncludeHierarchy {" << std::endl;

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
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_dot_file>" << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    std::unordered_map<std::string, std::unordered_set<std::string>> includeMap;
    parseHierarchy(inputPath, includeMap);
    generateDotFile(includeMap, outputPath);

    std::cout << "DOT file saved to " << outputPath << std::endl;

    return 0;
}

