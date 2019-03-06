#include <iostream>
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    string textFile;
    cout << "enter name of text file you want to parse." << endl;
    cin >> textFile;

    LexicalAnalyzer testCase;
    testCase.textToString(textFile);
    EXIT_SUCCESS;
}