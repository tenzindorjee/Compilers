#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <iomanip>
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
    
    //FSM table for identifiers
    //inputs: letter, digit, or $
    const int ID_FSM_States[5][3] = {
        {2, 5, 5},      //state 1(starting state); only accepts a letter initially, goes to dead state otherwise
        {2, 3, 4},      //state 2(final state)
        {5, 5, 4},      //state 3(final state); goes to dead state if input is a letter or digit
        {5, 4, 5},      //state 4(final state); goes to dead state if input is a letter or $
        {1, 1, 1}       //state 5(dead state); goes back to starting state
    };
    
    //FSM table for real and floating point numbers
    //inputs: digit or .
    const int RF_FSM_States[4][2] = {
        {2, 4},     //state 1(starting state)
        {2, 3},     //state 2(final state)
        {2, 4},     //state 3
        {1, 1}      //state 4
    };
        
    }
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
    {
        //iterates through the token vector until it reaches max size might need to fix up
        //Will output into a text file
        fstream outfile;
        outfile.open("output.txt");
        outfile << "TOKENS" << setw(15) << "LEXEMES" << endl;

        for (int i = 0; i < vectorToken.size(); i++)
        {
            int tempToken = vectorToken[i].identifierState;
            int tempLexemes = vectorToken[i].lexemes;

            outfile << tempToken << setw(13) << "=" << tempLexemes << endl;
        }
        outfile.close();
    }
    // NEED TO WORK ON THIS AND THE TABLE
    token LexicalAnalyzer::Lexer()
    {
        
    }

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
