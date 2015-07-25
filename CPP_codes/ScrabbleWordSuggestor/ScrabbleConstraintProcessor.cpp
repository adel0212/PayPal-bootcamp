#include "ScrabbleConstraintProcessor.h"

using namespace std;

ScrabbleConstraintProcessor::ScrabbleConstraintProcessor(string constraint)
{
    constraintRegExp = generateConstraintRegExp(constraint);
}

string ScrabbleConstraintProcessor::generateConstraintRegExp(string constraint)
{
        string startExp = "";
        string endExp = "";
        string midExp = "";

        int i = 0;
        try {
            while (constraint[i] == '*') {
                startExp += ".{0,1}";
                i++;
            }
            int startInd = i;
            i = constraint.length() - 1;
            while (constraint[i] == '*') {
                endExp += ".{0,1}";
                i--;
            }
            int endInd = i;
            for (int k = startInd; k <= endInd; k++ ) {
                if (constraint[k] == '*') {
                    midExp += ".";
                } else {
                    midExp += constraint[k];
                }
            }
        }
        catch (const std::regex_error& e) {
            std::cout << "regex_error caught: " << e.what() << '\n';
            if (e.code() == std::regex_constants::error_brack) {
                std::cout << "The code was error_back\n";
            }
        }

        return (startExp + midExp + endExp);
}

bool isConstraintPassed(string word){
    try {
            return std::regex_match(word, std::regex(constraintRegExp));
        }
    catch (const std::regex_error& e) {
        std::cout << "regex_error caught: " << e.what() << '\n';
        if (e.code() == std::regex_constants::error_brack) {
            std::cout << "The code was error_back\n";
        }
    }
}