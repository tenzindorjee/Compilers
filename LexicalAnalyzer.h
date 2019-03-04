#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>

using namespace std;

class LexicalAnalyzer
{
  private:
    string KEYWORDS[15] = {"int", "float", "bool", "if", "else", "then", "do", "while", "whileend", "do", "doend", "for", "and", "or", "function"};
    string OPERATORS[8] = {"*", "+", "-", "=", "/", ">", "<", "%"};
    string SEPERATORS[13] = {"'", "(", ")", "{", "}", "[", "]", ",", ".", ":", ";", "!", " "};
    string STATE[8] = {"UNKNOWN", "IDENTIFIER", "INTEGER", "KEYWORD", "SEPERATOR", "OPERATOR", "REAL", "DECIMAL"};

    // list tokenList; // idk yet
    // list lexemeList;
    int currentState = 1;       // default state
    bool acceptedOrNot = false; //whether the state is accepted or not
    string textFileHolder;      //holds the text file into a string to iterate later on
    typedef struct tokens
    {
        string identifierState; // token identifier
        string lexemes;
    } token;

    vector<token> tokenVector; //holds the token
  public:
    void LexicalAnalyzer::textToString(string textFile)
    {
        fstream holder;
        holder.open(textFile);
        if (holder.fail())
        {
            cerr << "Error Opening TextFile" << endl;
            exit(1);
        }
        holder >> textFileHolder;
    }
    void LexicalAnalyzer::printTokenAndLexemes(vectorToken[])
    {
        cout << "TOKENS" << setw(15) << "LEXEMES" << endl;

        for (int i = 0; i < vectorToken.size(); i++)
        {
            int tempToken = vectorToken[i].identifierState;
            int tempLexemes = vectorToken[i].lexemes;

            cout << tempToken << setw(13) << "=" << tempLexemes << endl;
        }
    }

    token LexicalAnalyzer::Lexer()
