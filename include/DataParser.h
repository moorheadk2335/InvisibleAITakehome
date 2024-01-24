#ifndef DATA_PARSER_H
#define DATA_PARSER_H

/**
 * Interface class to provide data parsing functionality
*/
class DataParser {
public:
    struct Result {
        int majority = 0;
        int any = 0;
        int all = 0;
    };

    struct FrameInfo {
        int positiveVotes = 0;
        int totalVotes = 0;
    };

    /**
     * Parse the data
     * 
     * \return True if data was succesfully parsed, false otherwise
    */
    virtual bool parse() = 0;

    /**
     * Print the result of the parsed data
    */
    virtual void printResult() = 0;
};

#endif //DATA_PARSER_H