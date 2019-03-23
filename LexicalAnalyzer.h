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
#include <sstream>
using namespace std;

class LexicalAnalyzer
{
  private:
    string KEYWORDS[15] = {"int", "float", "bool", "if", "else", "then", "do", "while", "whileend", "do", "doend", "for", "and", "or", "function"};
    char OPERATORS[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};
    char SEPERATORS[13] = {'\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', '!'};
    const int legal_identifier[5][3] = {{2, 5, 5}, {2, 3, 4}, {5, 5, 4}, {5, 4, 5}, {1, 1, 1}}; // legal identifier fsm
    const int digit_or_float_fsm[4][2] = {{4, 2}, {3, 2}, {4, 2}, {1, 1}};                      // real or float fsm                                                                      //contains current index of the vector of chars so we can test which index we are at                                                   // default state                                                                //whether the state is accepted or not
    string textFileHolder;                                                                      //holds the text file into a string to iterate later on
    vector<char> charList;
    typedef struct tokens
    {
        string lexemes;
        string tokens;
    } token;
    vector<token> tokenVector; //holds the token
    int tempIndex = 0;

  public:
    void textToString(string textFile)
    { //opens textfile and then stores it into a string for further use
        ifstream inFile;
        inFile.open(textFile); //open the input file
        stringstream strStream;
        strStream << inFile.rdbuf();  //read the file
        string str = strStream.str(); //str holds the content of the file
        textFileHolder = str;
        string_to_charList(textFileHolder);
    }
    void printTokenAndLexemes(vector<token> tokenVector)
    { //iterates through the token vector until it reaches max size might need to fix up
        for (int i = 0; i < tokenVector.size(); i++)
        {
            string tempToken = tokenVector[i].lexemes;
            string tempLexemes = tokenVector[i].tokens;
            cout << tempToken << " = " << tempLexemes << endl;
        }
    }

    void string_to_charList(string textFileHolder)
    { //converts the string that holds all the text file to a char vector for further manipulation
        for (int i = 0; i < textFileHolder.length(); i++)
        {
            charList.push_back(textFileHolder[i]);
            // cout << tempString << endl;
        }
        Lexer(charList, tokenVector);
    }

    void Lexer(vector<char> charList, vector<token> tokenVector)
    {
        for (vector<char>::iterator it = charList.begin(); it < charList.end(); it++)
        {
            if (*it == '!')
            { //change the iterator name from peekIt to something normal DARK TIMES BROOOOOOO
                vector<char>::iterator peekIt = it++;
                while (*peekIt != '!')
                {
                    cout << "not done" << endl;
                    peekIt++;
                }
                while (*it != *peekIt)
                {
                    it++;
                }
                it++;
            }

            else if (isSeperator(*it) == true)
            {
                for (int i = 0; i < 13; i++)
                {
                    if (SEPERATORS[i] == *it)
                    {
                        token TempToken;
                        TempToken.lexemes = *it;
                        TempToken.tokens = "SEPERATOR";
                        tokenVector.push_back(TempToken);
                    }
                }
            }
            else if (isOperator(*it) == true)
            {
                for (int i = 0; i < 8; i++)
                {
                    if (OPERATORS[i] == *it)
                    {
                        token TempToken;
                        TempToken.lexemes = *it;
                        TempToken.tokens = "OPERATOR";
                        tokenVector.push_back(TempToken);
                    }
                }
            }

            // else if (isIdentifier(*it) == true)
            // {
            //     int initialState = 1;     // initial state of the fsm
            //     token tempToken;          //temp token
            //     string comboString = *it; //identifier holder

            //     while (legal_identifier[initialState][findColumn(*it) != 5])
            //     {
            //         if (legal_identifier[initialState][findColumn(*it)] == 2)
            //         {

            //             initialState = 2;
            //             it++;
            //         }
            //         else if (legal_identifier[initialState][findColumn(*it) == 3])
            //         {
            //             initialState = 3;
            //             it++;
            //         }
            //     }
            // }
        }
        printTokenAndLexemes(tokenVector);
    }

    bool isSeperator(char c)
    {
        for (int i = 0; i < 12; i++)
        {
            if (c == SEPERATORS[i])
            {
                return 1; // returns true if the char/string is equivalent to a valid seperator
            }
        }
        return 0;
    }

    bool isOperator(char c)
    {

        for (int i = 0; i < 8; i++)
        {
            if (c == OPERATORS[i])
            {
                return 1;
            }
        }
        return 0;
    }
    // NEED TO FIX
    int findColumn(string s)
    { //functions to find the column the char belongs to so it can go through the table to find if accepted or not
        int tempInt;
        if (isAplhanumeric(s) == true || s == ".")
        {
            tempInt = 1;
        }
        else if (isNumber(s) == true)
        {
            tempInt = 2;
        }
        else if (s == "$")
        {
            tempInt = 3;
        }
        else
            cerr << "Error Column doesnt exist" << endl;

        return tempInt;
    }

    bool isIdentifier(string s)
    {
        string alphaArray[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
                               "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "$"};

        for (int i = 0; i < 53; i++)
        {
            if (s == alphaArray[i])
            {
                return 1;
            }
        }

        return 0;
    }

    bool isNumber(string s)
    {
        string numberArray[] = {"1", "2", "3", "4", "6", "7", "8", "9", "0"};

        for (int i = 0; i < 9; i++)
        {
            if (s == numberArray[i])
            {
                return 1;
            }
        }
        return 0;
    }

    bool isAplhanumeric(string s)
    {
        string alphArray[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
                              "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

        for (int i = 0; i < 52; i++)
        {
            if (s == alphArray[i])
            {
                return 1;
            }
        }

        return 0;
    }
};
