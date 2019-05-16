#include <vector>
#include <stack>
#include <queue>

//assuming you have a semi-colon at the end like in our test.txt  or structured like our test.txt it should work and show the actions of the stack
//if there is an error will print out the production rule where it hit the error 
//also assuming if there is the start symbol %% or $$
// couldnt turn in assignment 2 on time turning this in for assignment 2 late as well 
// if it doesnt work try our test.txt 

class SyntaxAnalyzer
{
  private:
    stack<string> TDPstack; // the stack which holds the production rules

  public:
    vector<LexicalAnalyzer::token> tokenVect; // the vector that holds the token 
    bool enablePrint = true; // print bool
    int incrementCount = 0; // the counter for the vector 
    int testCounter = 0; // counter to peek for start symbol $$ or %%

    // constructor
    SyntaxAnalyzer(vector<LexicalAnalyzer::token> tvec) // pulls the vector from LA 
    {
        tokenVect = tvec;
    }

    string getCurrentToken()
    {
        return tokenVect[incrementCount].lexemes;
    }

    string getNextToken()
    {
        incrementCount++;
        if (incrementCount < tokenVect.size())
        {
            return tokenVect[incrementCount].tokens;
        }
        else
        {
            return "";
        }
    }

    void tdpParser() // parser function 
    {

        if (tokenVect[testCounter].lexemes == "$")
        {
            
            if (tokenVect[testCounter++].lexemes == "$") //checks start symbol 
            {
                incrementCount++;
                incrementCount++;
                
            }
        }

        if (tokenVect[testCounter].lexemes == "%")
        {

            
            if (tokenVect[testCounter++].lexemes == "%")
            {
                incrementCount++;
                incrementCount++;
            }
        }



        TDPstack.push("$"); // initiates the stack and calls the main function 
        stackImplementation();


        
    }


    void stackImplementation(){



        if(S() == true){ // basically if there is a starting symbol S-> i = E will return a true and hence the syntax starts off right 

        TDPstack.push("E"); // since the Starting symbol is right and there is a identifier followed by a = calls the E or expression function 

        }
        else if (S() == false)
        {
        cout << "ERROR: S-> i = E" << endl; // if this returns false will send out an error the start of the string is wrong;
        }
            


        while(!TDPstack.empty()){

            // basically implemented the table through functions and the ideals if the top of the stack matches will call the function
            //then the function will match it with input like the table would 

            if(TDPstack.top() == "*" || TDPstack.top() == "+" || TDPstack.top() == "(" || TDPstack.top() == ")" || TDPstack.top() == "-" || TDPstack.top() == "/" || TDPstack.top() == "-" || TDPstack.top() == "IDENTIFIER" || TDPstack.top() == "$")
            {
                incrementCount++;
                cout << "popping: " << TDPstack.top() << endl; // accounting for epsilon 
                TDPstack.pop();
            }

            else if(TDPstack.top() == "E"){

                E();
            }

            else if(TDPstack.top() == "Q" ){
                Q();
            }

            else if(TDPstack.top() == "T"){
                T();
            }

            else if(TDPstack.top() == "R"){
                R();
            }

            else if(TDPstack.top() == "F"){
                F();
            }
            
            else if (tokenVect[incrementCount].lexemes == ";") // when gets to semi colon and there are no errors will print out that its accepted
            {
                
                cout << "string is accepted" << endl; // increments to the next token and then restarted the cycle 

                if(incrementCount!= tokenVect.size()){ // compares the current token holder to the end size of the vector 
                    incrementCount++;
                    stackImplementation();
                }
                else {
                    cout << "DONE" << endl; // if its at the end will end 
                }
                
            }



        }

    }

    bool S()
    {
        if(tokenVect[incrementCount].tokens == "IDENTIFIER") // S production function checks S-> i = E
        {
            incrementCount++;
            if(tokenVect[incrementCount].lexemes == "=")
            {
            cout << "S->i=E" << endl;
            incrementCount++;
            return true;

            }
            else
            {
                cout << "RIP";
                return false;
            }
                
        }
        else 
        {
            cout << "RIP";
             return false;
        }
           
    }
    
    bool E()
    {
        if (tokenVect[incrementCount].lexemes == "(") // E production function 
        {
            TDPstack.pop();
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.push("Q");
            cout << "PUSH " << TDPstack.top() << endl;
            TDPstack.push("T");

            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].tokens == "IDENTIFIER")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("Q");
            cout << "PUSH " << TDPstack.top() << endl;
            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else
        {
            cout << "ERROR: <Expression> -> <Term> <ExpressionPrime>" << endl;
            return false;
        }
    }

    bool Q() // q production function 
    {
        if (tokenVect[incrementCount].lexemes == "+")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            

            TDPstack.push("Q");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("+");
            cout << "PUSH " << TDPstack.top() << endl;

            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "-")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("Q");
            cout << "PUSH " << TDPstack.top() << endl;

            

            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;
            
            TDPstack.push("-");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == ")")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "$")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }

        else
        {
            
            cout << "ERROR: <ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>" << endl;
            return false;
        }
    }

    bool T() // T production function 
    {
        if (tokenVect[incrementCount].tokens == "IDENTIFIER")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;

            
            return true;
            
        }

        else if (tokenVect[incrementCount].lexemes == "(")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }
        else
        {
            cout << "ERROR: <Term> -> <Factor> <TermPrime> ";
            return false;
        }
    }

    bool R()
    {
        if (tokenVect[incrementCount].lexemes == "+")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "-")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "*")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("*");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "/")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");

            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("/");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }
        else if (tokenVect[incrementCount].lexemes == ")")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }
        else if (tokenVect[incrementCount].lexemes == "$")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == ";") // basically had an error where the loop would go infinitely after the final string 
        {
            cout << "STRING: ACCEPTED" << endl;
            incrementCount++;
            if(incrementCount != tokenVect.size()){
                stackImplementation();
            }
            else {

                cout << "END" << endl; // throws exit and ends when reching end 
                exit(1);
            }

            
            return true;
        }

        else
        {
            //cout << "ERROR: R" << endl;
            // throws out the error for the production rules then exits this function when it reached r in the stack was tricky 
            cout << "ERROR: <TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>" << endl;
            
            exit(1);
            return false;
        }
    }

    bool F() // function for F production rules 
    {
        if (tokenVect[incrementCount].tokens == "IDENTIFIER")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("IDENTIFIER");
            cout << "POP " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "(")
        {

            TDPstack.push(")");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("E");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("(");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else
        {
            cout << "ERROR: F->(E)|i " << endl;
            return false;
        }
    }
};