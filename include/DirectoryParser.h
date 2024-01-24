#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "DataParser.h"

#include <filesystem>
#include <utility>

/**
 * Class to parse all data files in a given directory
*/
class DirectoryParser : public DataParser {
public:
    DirectoryParser(std::filesystem::path directoryPath);

    bool parse() override;
    void printResult() override;
    void setPath(std::filesystem::path newDirectoryPath);

private:
    std::filesystem::path path;
    Result result;

    std::pair<int, bool> parseLine(std::string line);
};

#endif //FILE_PARSER_H