
#include "LexicalAnalyzer.h"
#include <iostream>
#include <vector>
using namespace std;

class SyntaxAnalyzer
{
private:
  typedef struct tokens
  {
    string lexemes;
    string tokens;
  } token;

  vector<token> tempVector;
  int indexCounter;

public:
  SyntaxAnalyzer()
  {
    indexCounter = 0;
  }

  void startThisShit(string fileName)
  {
    LexicalAnalyzer lmao;
    lmao.textToString(fileName);
    tempVector = lmao.returnTokenVector();
  }
};