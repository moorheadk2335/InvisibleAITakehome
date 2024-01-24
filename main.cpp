#include "include/DataParser.h"
#include "include/DirectoryParser.h"

#include <chrono>
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

void printTiming(chrono::system_clock::time_point start, chrono::system_clock::time_point stop)
{
    auto runTimeUSeconds = chrono::duration_cast<chrono::microseconds>(stop - start);
    auto runTimeSeconds = chrono::duration_cast<chrono::seconds>(stop - start);
    auto runTimeMilliseconds = chrono::duration_cast<chrono::milliseconds>(stop - start);

    auto secondCount = runTimeSeconds.count();
    auto millisecondCount = runTimeMilliseconds.count() - (runTimeSeconds.count() * 1000);

    cout << "Total execution time: " << runTimeUSeconds.count() << " microseconds (" <<
        secondCount << "." << setfill('0') << setw(3) << millisecondCount  << " seconds)" << endl;
}

void runParser(DataParser &parser)
{
    auto start = chrono::high_resolution_clock::now();
    if (!parser.parse()) {
        cout << "Parser failed to parse data" << endl;
        printUsage();
        return;
    }
    auto stop = chrono::high_resolution_clock::now();

    // We are removing this print from the timing since cout can add arbitrary time
    parser.printResult();
    
    // Optional code to print timing information
    // printTiming(start, stop);
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
