#pragma once
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

class LexicalAnalyzer
{
  private:
    string KEYWORDS[15] = {"int", "float", "bool", "if", "else", "then", "do", "while", "whileend", "do", "doend", "for", "and", "or", "function"};
    string OPERATORS[8] = {"*", "+", "-", "=", "/", ">", "<", "%"};
    string SEPERATORS[13] = {"'", "(", ")", "{", "}", "[", "]", ",", ".", ":", ";", "!", " "};
    string STATE[8] = {"UNKNOWN", "IDENTIFIER", "INTEGER", "KEYWORD", "SEPERATOR", "OPERATOR", "REAL", "DECIMAL"};
    const int legal_identifier[5][3] = {{2, 5, 5}, {2, 3, 4}, {5, 5, 4}, {5, 4, 5}, {1, 1, 1}}; // legal identifier fsm
    const int digit_or_float_fsm[4][2] = {{4, 2}, {3, 2}, {4, 2}, {1, 1}};                      // real or float fsm
    int vectorIndex = 0;                                                                        //contains current index of the vector of chars so we can test which index we are at
    int currentState = 1;                                                                       // default state
    bool acceptedOrNot = false;                                                                 //whether the state is accepted or not
    string textFileHolder;                                                                      //holds the text file into a string to iterate later on
    vector<char> charVector;

    typedef struct tokens
    {
        string identifierState; // token identifier
        string lexemes;         //lexemes
    } token;

    vector<token> tokenVector; //holds the token
  public:
    void textToString(string textFile)
    { //opens textfile and then stores it into a string for further use

        ifstream file(textFile);
        string tempString;
        if (file.is_open())
        {
            cout << "hello" << endl;
            while (getline(file, tempString))
            {
                tempString += tempString;
                tempString += " ";
            }
            cout << tempString;
            textFileHolder = tempString;
            cout << textFileHolder << endl;
            file.close();
        }

        //string_to_charVector(textFileHolder);
    }
    void printTokenAndLexemes(vector<token> vectorToken)
    { //iterates through the token vector until it reaches max size might need to fix up
        cout << "TOKENS" << setw(15) << "LEXEMES" << endl;

        for (int i = 0; i < vectorToken.size(); i++)
        {
            string tempToken = vectorToken[i].identifierState;
            string tempLexemes = vectorToken[i].lexemes;

            cout << tempToken << setw(13) << "=" << tempLexemes << endl;
        }
    }

    void string_to_charVector(string textFileHolder)
    { //converts the string that holds all the text file to a char vector for further manipulation
        for (int i = 0; i < textFileHolder.length(); i++)
        {
            charVector[i] = textFileHolder[i];
        }
        Lexer(charVector);
    }

    void Lexer(vector<char> charVector)
    { //NEED TO NO LIFE THE FUCK OUT OF THIS PART BRUH
        if (charVector[vectorIndex] == '!')
        {
            indexUpdate();

            while (charVector[vectorIndex] != '!')
            {
                indexUpdate();
                cout << vectorIndex << endl;
            }
            cout << vectorIndex << endl;
        }
    }
    void indexUpdate()
    {
        vectorIndex++;
    }
    bool isSeperator(char c)
    {
        string tempString; // a temporary string so that we can convert the char to string for comparison to the seperator array
        tempString += c;   // tempString = tempString + char

        for (unsigned int i = 0; i < 13; i++)
        {
            if (tempString == SEPERATORS[i])
            {
                return 1; // returns true if the char/string is equivalent to a valid seperator
            }
        }
        return 0;
    }

    bool isOperator(char c)
    {
        string tempString;
        tempString += c;

        for (unsigned int i = 0; i < 8; i++)
        {
            if (tempString == OPERATORS[i])
            {
                return 1;
            }
        }
        return 0;
    }

    int char_to_column(char c)
    { //functions to find the column the char belongs to so it can go through the table to find if accepted or not
        int tempInt;
        if (isalpha(c) || c == '.')
        {
            tempInt = 1;
        }

        else if (isdigit(c))
        {
            tempInt = 2;
        }

        else if (c == '$')
        {
            tempInt = 3;
        }
        else
            cerr << "Error Column doesnt exist" << endl;

        return tempInt;
    }
};
