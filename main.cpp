#include "include/DataParser.h"
#include "include/DirectoryParser.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void printUsage()
{
    cout << "Invisible AI Takehome" << endl;
    cout << "Usage: ./takehome <path to data directory>" << endl;
}

void runParser(DataParser &parser)
{
    if (!parser.parse()) {
        cout << "Parser failed to parse data" << endl;
        printUsage();
        return;
    }

    parser.printResult();
}

int main(int argc, char** argv)
{
    // Verify expected number of arguments present
    if (argc != 2) {
        printUsage();
        return 0;
    }

    DirectoryParser directoryParser(argv[1]);
    runParser(directoryParser);

    return 0;
}
