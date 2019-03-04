#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
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
        string lexemes;         //lexemes
    } token;

    vector<token> tokenVector[100]; //holds the token
  public:
    void LexicalAnalyzer::textToString(string textFile)
    { //opens textfile and then stores it into a string for further use
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
    { //iterates through the token vector until it reaches max size might need to fix up
        cout << "TOKENS" << setw(15) << "LEXEMES" << endl;

        for (int i = 0; i < vectorToken.size(); i++)
        {
            int tempToken = vectorToken[i].identifierState;
            int tempLexemes = vectorToken[i].lexemes;

            cout << tempToken << setw(13) << "=" << tempLexemes << endl;
        }
    }

    //token LexicalAnalyzer::Lexer()
    // NEED TO WORK ON THIS AND THE TABLE


    int LexicalAnalyzer::char_to_column(char c)
    { //functions to find the column the char belongs to so it can go through the table to find if accepted or not
        if (isalpha(c) || c == '$')
        {
            return 1;
        }

        else if (isdigit(c))
        {
            return 2;
        }

        else if (c==' '){
            return 
        }
    }
