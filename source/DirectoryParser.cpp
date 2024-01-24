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

    vector<FrameInfo> frameInfo;

    for (const auto &entry : filesystem::directory_iterator(path)) {
        // Skip anything that is not a regular file
        if (!entry.is_regular_file()) continue;

        std::ifstream input(entry.path());

        for (string line; getline(input, line); ) {
            // Ensure the line contains data
            if (line.length() == 0) continue;

            // Parse the given line
            auto[frameNumber, vote] = parseLine(line);

            // Grow our vector containing the current frame counts as needed
            // This code will be slow the first time through a given file as we will be continually resizing,
            // or if the frame numbers are drastically off between files,
            // we could preprocess the files to determine the highest frame number
            // to preallcoate the vector to the correct sizes as one way to avoid this
            // We could also use a map with the frame number as the key to avoid needing to resize
            // This assumes the frame count is zero based
            if (frameInfo.size() < (frameNumber + 1)) {
                frameInfo.resize(frameNumber + 1);
            }

            frameInfo[frameNumber].totalVotes++;
            if (vote == true) frameInfo[frameNumber].positiveVotes++;
        }
    }

    // Finally, tally the voting information
    for (auto info : frameInfo) {
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
    int frameNumber = stoi(line.substr(0,index));
    bool vote = line.substr(index + delimiter.length(), line.length()) == "true";
    return pair<int, bool>(frameNumber, vote);
}

