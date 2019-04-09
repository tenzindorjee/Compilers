#include <iostream>
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    string textFile;
    // textFile = "SampleInputFile1.txt";
    cout << "enter name of textfile you wish to use" << endl;
    getline(cin, textFile);
    LexicalAnalyzer testCase;
    testCase.textToString(textFile);
    EXIT_SUCCESS;
}