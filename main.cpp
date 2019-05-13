#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

using namespace std;

int main()
{
    string textFile;
    textFile = "SampleInputFile1.txt";
    cout << "enter name of textfile you wish to use" << endl;
    getline(cin, textFile);

    LexicalAnalyzer testCase;
    testCase.textToString("test.txt");

    SyntaxAnalyzer SA(testCase.getTokens());
    SA.tdpParser();
    // SA.getNextToken();

    // SAnalyzer.getNextToken();

    // testCase.textToString(textFile);
    // SyntaxAnalyzer SAnalyzer(testCase.getTokens());
    // SAnalyzer.getNextToken();

    // EXIT_SUCCESS;
}