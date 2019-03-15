#include <iostream>
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    string textFile;
    textFile = "SampleInputFile1.txt";
    LexicalAnalyzer testCase;
    testCase.textToString(textFile);
    EXIT_SUCCESS;
}