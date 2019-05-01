#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "SyntaxAnalyzer.h"
using namespace std;
class LexicalAnalyzer
{
  private:
    string KEYWORDS[15] = {"int", "float", "bool", "if", "else", "then", "do", "while", "whileend", "do", "doend", "for", "and", "or", "function"};
    char OPERATORS[8] = {'*', '+', '-', '=', '/', '>', '<', '%'};
    char SEPERATORS[13] = {'\'', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', '!'};
    const int legal_identifier[5][3] = {{1, 4, 4}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {4, 4, 4}}; // legal identifier fsm
    const int digit_or_float_fsm[4][2] = {{3, 1}, {2, 1}, {3, 1}, {3, 3}};                      // real or float fsm                                                                                                               // default state                                                                //whether the state is accepted or not
    string textFileHolder;                                                                      //holds the text file into a string to iterate later on
    vector<char> charList;                                                                      //list of chars to
    typedef struct tokens                                                                       //token struct
    {
        string lexemes;
        string tokens;
    } token;

    vector<token> tokenVector; //holds the token in a vector
    bool commentCheck = false; //comment check so that we dont have to deal with it interfering with our fsm functions
    bool invalidFlag = false;

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
        cout << "TOKEN        LEXEMES" << endl;
        for (int i = 0; i < tokenVector.size(); i++)
        {
            string tempToken = tokenVector[i].tokens;
            string tempLexemes = tokenVector[i].lexemes;
            cout << setw(10) << left << tempToken << " = " << tempLexemes << endl;
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
                commentCheck = true; //basically an iterator catch up to get rid of the comment part and a flag so that we dont mess up when advancing through
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
                //compares char to array of seperators
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
                //compares char to array of operators
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

            else if (isalpha(*it) == true && commentCheck == false)
            {
                bool errorFlag = false; // if a valid identifier is an alpha followed by num,$, or another alpha then all we have to worry about is there being a $ before the first alpha so this a flag for this
                int finalStateL = 1;    //final states
                int finalStateD = 2;
                int finalState$ = 3;
                string tempString;
                int defaultS = 0; //state holder defaults at 0 for state transition had a lot of problems because didnt account for decrement
                string anotherString;
                vector<char>::iterator previousIterator = it; //an previous iterator
                string invalidID;
                --previousIterator;

                if (*previousIterator == '$') // basically if there is a $ or num before the alpha the function wouldnt recognize this as not a valid identifier so this gets rid of could also delete token after inputting
                {
                    invalidID = "$";
                    errorFlag = true;
                    while (commentCheck == false && isAlphanumeric(*it) == true)
                    {
                        invalidID += *it;
                        it++;
                    }
                    invalidFlag = true;
                }
                else if (isdigit(*previousIterator) == true)
                {

                    invalidID += *previousIterator;
                    errorFlag = true;
                    while (commentCheck == false && isAlphanumeric(*it) == true)
                    {
                        invalidID += *it;
                        it++;
                    }
                    invalidFlag = true;
                }

                else // if no other issues it would go to the loop that deals with the fsm as long as not in garbage state it will append and iterate
                {
                    while (defaultS != 4 && commentCheck == false && isAlphanumeric(*it) == true)
                    {

                        defaultS = legal_identifier[defaultS][findColumn(*it)];

                        if (defaultS != 4)
                            tempString += *it;
                        it++;
                    }
                }

                it--;
                if (defaultS == finalStateL || defaultS == finalStateD || defaultS == finalState$ || errorFlag == false) //basically checking if the state for the string was in a final state else wouldnt work
                {
                    anotherString += tempString;
                }
                if (keywordTrue(anotherString) == true && errorFlag == false) //checks if keyword
                {
                    for (int i = 0; i < 15; i++)
                    {
                        if (tempString == KEYWORDS[i])
                        {
                            token TempToken;
                            TempToken.lexemes = anotherString;
                            TempToken.tokens = "KEYWORD";
                            tokenVector.push_back(TempToken);
                        }
                    }
                }
                else if (errorFlag == false) //else adds as an identifier if previous test were valid
                {
                    token TempToken;
                    TempToken.lexemes = anotherString;
                    TempToken.tokens = "IDENTIFIER";
                    tokenVector.push_back(TempToken);
                }

                else //otherwise just throws error
                {
                    cerr << "error invalid identifier " << invalidID << endl;
                }
            }

            else if (isnumber(*it) == true && commentCheck == false)
            {
                //same thing as previous function for alphanumeric except for floats and numbers
                string tempString;
                int currentState = 0; //defaults at 0 but when looping it changes to current state
                int finalState = 1;
                bool floatCheck = false;
                bool brokeCheck = false;
                string loopString;
                vector<char>::iterator beforeIt = it;
                vector<char>::iterator afterIt = it;
                beforeIt--;
                afterIt++;
                cout << "before " << *beforeIt << " after " << *afterIt << endl;
                if (isalpha(*beforeIt) == true || isalpha(*afterIt) == true) // uses two iterators so that when you have an identifier thats not valid the extra num would get picked up so to prevent that I added this
                {
                    brokeCheck = true;
                    while ((isnumber(*it) == true) && commentCheck == false)
                    {
                        beforeIt++;
                        it++;
                        afterIt++;
                    }
                }
                while (((isnumber(*it) == true) || *it == '.') && currentState != 3 && commentCheck == false && brokeCheck == false && (isalpha(*beforeIt) != true || isalpha(*afterIt) != true))
                {

                    if (isalpha(*beforeIt) == true || isalpha(*afterIt) == true)
                    {
                        brokeCheck = true;
                    }

                    if (*it == '.') //checks for for . to tell if its a float
                    {
                        floatCheck = true;
                    }

                    currentState = digit_or_float_fsm[currentState][findNumColumn(*it)];

                    if (currentState != 3)
                    {
                        loopString += *it;
                    }

                    it++;
                }
                it--;

                if (currentState != 3 && currentState == finalState && brokeCheck == false) // if not in garbage state and the current state is the same then it can be stored as token
                {
                    tempString += loopString;
                }

                if (floatCheck == true && brokeCheck == false) //float check is true then added as a REAL
                {
                    token TempToken;
                    TempToken.lexemes = tempString;
                    TempToken.tokens = "REAL";
                    tokenVector.push_back(TempToken);
                }
                else if (floatCheck == false && brokeCheck == false) //otherwise an INTEGER
                {
                    token TempToken;
                    TempToken.lexemes = tempString;
                    TempToken.tokens = "INTEGER";
                    tokenVector.push_back(TempToken);
                }

                floatCheck = false; //sets float flag back to normal
            }
        }

        //printTokenAndLexemes(tokenVector);
    }

    vector<token> returnTokenVector()
    {
        vector<token> tempVector = tokenVector;
        return tempVector;
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

    bool isOperator(char c) //operator check function
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

    bool isAlphanumeric(char c) //is alphanumeric or $
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

    bool isNumber(char c) // checks if number or .
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
    bool keywordTrue(string s) //checks if lexeme is a keyword
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
        if (isalpha(c) == true)
        {
            tempInt = 0;
        }
        else if (isdigit(c) == true)
        {
            tempInt = 1;
        }
        else if (c == '$')
        {
            tempInt = 2;
        }
        else //otherwise error
        {

            cerr << "Error Column doesnt exist" << endl;
        }
        return tempInt;
    }

    int findNumColumn(char c) //seperate column finding functions for integers or real floats
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
