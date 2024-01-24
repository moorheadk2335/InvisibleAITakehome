#include "DirectoryParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

DirectoryParser::DirectoryParser(std::filesystem::path directoryPath)
    : path(directoryPath)
{

}

bool DirectoryParser::parse()
{
    // Result our current result
    result.any = 0;
    result.all = 0;
    result.majority = 0;

    // Verify valid directory
    if (!filesystem::is_directory(path)) {
        cerr << "Invalid directory path [" << path << "] provided, please provide directory path containing test data" << endl;
        return false;
    }

    int frameCount = 0;

    // Preprocess our files to determine the overall frame count
    // We're only reading the last line of each file, so this should be fast
    for (const auto &entry : filesystem::directory_iterator(path)) {
        frameCount = max(frameCount, getTotalFrames(entry));
    }

    // Assume zero based array, so frameCount + 1 for total items
    vector<FrameInfo> frameInfo(frameCount + 1);

    // Parse each file
    for (const auto &entry : filesystem::directory_iterator(path)) {
        // Skip anything that is not a regular file
        if (!entry.is_regular_file()) continue;

        // Parse each line of the file
        ifstream input(entry.path());
        for (string line; getline(input, line); ) {
            // Ensure the line contains data
            if (line.length() == 0) continue;

            // Parse the given line
            auto[frameNumber, vote] = parseLine(line);

            // If we failed to parse the line, don't try to set the frame count from this
            if (frameNumber == -1) continue;

            // Grow our array if needed, this shouldn't happend thanks to the preprocessing
            if (frameInfo.size() < (frameNumber + 1)) {
                frameInfo.resize(frameNumber + 1);
            }

            frameInfo[frameNumber].totalVotes++;
            if (vote == true) frameInfo[frameNumber].positiveVotes++;
        }
    }

    // Finally, tally the voting information
    for (auto info : frameInfo) {
        // If no cameras voted on this frame, skip it
        if (info.totalVotes == 0) continue;

        if (info.positiveVotes > info.totalVotes / 2) result.majority++;
        if (info.positiveVotes > 0) result.any++;
        if (info.positiveVotes == info.totalVotes) result.all++;
    }

    return true;
}

void DirectoryParser::printResult()
{
    cout << "Frames with majority of the present votes true: " << result.majority << endl;
    cout << "Frames with any of the present votes true: " << result.any << endl;
    cout << "Frames with all of the present votes true: " << result.all << endl;
}

void DirectoryParser::setPath(std::filesystem::path newPath)
{
    path = newPath;
}

pair<int, bool> DirectoryParser::parseLine(string line)
{
    // Example line: 4, true
    string delimiter = ", ";
    size_t index = line.find(delimiter);
    if (index == string::npos) {
        cout << "Failed to parse line: " << line << endl;
        return pair<int, bool>(-1, false);
    }
    int frameNumber = stoi(line.substr(0,index));
    bool vote = line.substr(index + delimiter.length(), line.length()) == "true";
    return pair<int, bool>(frameNumber, vote);
}

int DirectoryParser::getTotalFrames(const filesystem::directory_entry &entry)
{
    // Skip anything that is not a regular file, or if the file is empty
    if (!entry.is_regular_file() || filesystem::file_size(entry) == 0) return -1;

    ifstream input(entry.path(), ios::ate);
    streampos totalSize = input.tellg();

    // Seek backwards from the end of the file until we find the first newline character
    int searchIndex;
    // Set to 2 to skip the final new line
    for (searchIndex = 2; searchIndex <= totalSize; searchIndex++) {
        input.seekg(-searchIndex, ios::end);
        if (input.peek() == '\n') break;
    }

    // Create a buffer big enough to hold the last line
    int lastLineLength = totalSize - input.tellg();
    vector<char> buffer(lastLineLength);
    input.read(&buffer[0], lastLineLength);

    auto [frameNumber, vote] = parseLine(string(buffer.begin(), buffer.end()));
    return frameNumber;
}
