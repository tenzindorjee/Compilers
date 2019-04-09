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
/* had problems with literals because of the apostrophe char turned everything to string but ended up turning everything to chars because thats how a compiler is supposed to work */
class LexicalAnalyzer
{
  private:
    string KEYWORDS[15] = {"int", "float", "bool", "if", "else", "then", "do", "while", "whileend", "do", "doend", "for", "and", "or", "function"};
    char OPERATORS[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};
    char SEPERATORS[13] = {'\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', '!'};
    const int legal_identifier[5][3] = {{2, 5, 5}, {2, 3, 4}, {5, 5, 4}, {5, 4, 5}, {1, 1, 1}}; // legal identifier fsm
    const int digit_or_float_fsm[4][2] = {{3, 1}, {2, 1}, {3, 1}, {3, 3}};
    //const int digit_or_float_fsm[4][2] = {{4, 2}, {3, 2}, {4, 2}, {1, 1}};
    // real or float fsm                                                                      //contains current index of the vector of chars so we can test which index we are at                                                   // default state                                                                //whether the state is accepted or not
    string textFileHolder; //holds the text file into a string to iterate later on
    vector<char> charList;
    typedef struct tokens
    {
        string lexemes;
        string tokens;
    } token;
    vector<token> tokenVector; //holds the token
    int tempIndex = 0;
    bool commentCheck = false;

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
            string tempToken = tokenVector[i].tokens;
            string tempLexemes = tokenVector[i].lexemes;
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
                commentCheck = true;
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
                commentCheck = false;
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

            else if (isalpha(*it) == true && commentCheck == false && *it != ' ')
            {

                string tempString;
                int defaultS = 1;
                vector<char>::iterator neext = it++;
                it--;
                while (isAlphanumeric(*neext) == true && *neext != ' ' && defaultS != 5 && commentCheck == false && isAlphanumeric(*it) == true)
                {

                    defaultS = legal_identifier[defaultS][findColumn(*it)];
                    tempString += *it;
                    it++;

                    neext++;
                }
                it--;

                if (keywordTrue(tempString) == true)
                {
                    for (int i = 0; i < 15; i++)
                    {
                        if (tempString == KEYWORDS[i])
                        {
                            token TempToken;
                            TempToken.lexemes = tempString;
                            TempToken.tokens = "KEYWORD";
                            tokenVector.push_back(TempToken);
                        }
                    }
                }
                else
                {
                    token TempToken;
                    TempToken.lexemes = tempString;
                    TempToken.tokens = "IDENTIFIER";
                    tokenVector.push_back(TempToken);
                }

                defaultS = 1;
            }

            else if (isnumber(*it) == true && commentCheck == false)
            {
                cout << *it << "before " << endl;
                string tempString;
                int defaultS = 0;
                vector<char>::iterator floatPeek = it;
                floatPeek++;
                //vector<char>::iterator previousPeek = it--;
                //it--;
                bool floatCheck = false;
                //(isdigit(*it) || (*it == '.' && isdigit(*previousPeek))) && (*floatPeek != ' ') && (defaultS != 4) && !commentCheck
                //(isdigit(*floatPeek) == true || *floatPeek == '.') && (isdigit(*it) == true || *it == '.') && *floatPeek != ' ' && defaultS != 4 && commentCheck == false

                while (((isnumber(*it) == true) || *it == '.') && defaultS != 3 && commentCheck == false)
                {
                    // cout << *it << " in loop " << endl;
                    // cout << *floatPeek << "in floatPeek loop " << endl;
                    if (*it == '.')
                    {
                        std::cout << "We found a float boss! " << endl;
                        floatCheck = true;
                    }

                    //{{4, 2}, {3, 2}, {4, 2}, {1, 1}};
                    cout << "current state for " << *it << " before is " << defaultS << endl;
                    defaultS = digit_or_float_fsm[defaultS][findNumColumn(*it)];
                    cout << " column is " << findNumColumn(*it) << endl;
                    cout << "current state for " << *it << " is state " << defaultS << endl;
                    if (defaultS != 3)
                        tempString += *it;
                    //previousPeek++;
                    it++;
                    floatPeek++;
                }
                //it--;
                if (floatCheck == true)
                {
                    token TempToken;
                    TempToken.lexemes = tempString;
                    TempToken.tokens = "REAL";
                    tokenVector.push_back(TempToken);
                }
                else if (floatCheck == false)
                {
                    token TempToken;
                    TempToken.lexemes = tempString;
                    TempToken.tokens = "INTEGER";
                    tokenVector.push_back(TempToken);
                }
                defaultS = 1;
                floatCheck = false;
            }
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
    bool isAlphanumeric(char c)
    {
        if (isalpha(c) == true || c == '$' || isdigit(c) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isNumber(char c)
    {
        if (isdigit(c) == true || c == '.')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool keywordTrue(string s)
    {
        for (int i = 0; i < 15; i++)
        {
            if (s == KEYWORDS[i])
            {
                return true;
            }
        }
        return false;
    }

    int findColumn(char c)
    { //functions to find the column the char belongs to so it can go through the table to find if accepted or not
        int tempInt;
        if (isAlphanumeric(c) == true)
        {
            tempInt = 1;
        }
        else if (isdigit(c) == true)
        {
            tempInt = 2;
        }
        else if (c == '$')
        {
            tempInt = 3;
        }
        else
        {

            cerr << "Error Column doesnt exist" << endl;
        }
        return tempInt;
    }

    int findNumColumn(char c)
    {
        int holderInt;
        if (c == '.')
        {
            holderInt = 0;
        }
        else if (isdigit(c) == true)
        {
            holderInt = 1;
        }
        else
        {
            cerr << "Error Column doesnt exist" << endl;
        }
        return holderInt;
    }
};
