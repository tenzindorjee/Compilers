#include <iostream>
#include "LexicalAnalyzer.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>
#include <string>
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