#include <vector>
#include <stack>

class SyntaxAnalyzer
{
  private:
    stack<string> TDPstack;

  public:
    vector<LexicalAnalyzer::token> tokenVect;
    bool enablePrint = true;
    int incrementCount = 0;

    // constructor
    SyntaxAnalyzer(vector<LexicalAnalyzer::token> tvec)
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

    void tdpParser()
    {
        if (tokenVect[incrementCount].lexemes == "$")
        {
            
            if (tokenVect[incrementCount].lexemes == "$")
            {
                incrementCount++;
                incrementCount++;
            }
        }

        if (tokenVect[incrementCount].lexemes == "%")
        {
            
            if (tokenVect[incrementCount].lexemes == "%")
            {
                incrementCount++;
                incrementCount++;
            }
        }



        TDPstack.push("$");
        KMS();


        
    }


    void KMS(){



        if(S() == true){

        TDPstack.push("E");

        }
        else
            cout << "ERROR: S-> i = E" << endl;


        while(TDPstack.top() != "$"){

           

            if(TDPstack.top() ==  tokenVect[incrementCount].tokens || TDPstack.top() == "IDENTIFIER")
            {
                incrementCount++;
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
            else if (getCurrentToken() == ";")
            {
                
                cout << "string is accepted" << endl;

                if(incrementCount!= tokenVect.size()){
                    incrementCount++;
                    KMS();
                }
                else {
                    cout << "DONE" << endl;
                }
                
            }



        }

            










    }

    bool S()
    {
        if(tokenVect[incrementCount].tokens == "IDENTIFIER")
        {
            incrementCount++;
            if(tokenVect[incrementCount].lexemes == "=")
            {
            cout << "works";
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
        if (tokenVect[incrementCount].lexemes == "(")
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

    bool Q()
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

    bool T()
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
        else
        {
            cout << "ERROR: <TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>" << endl;
            return false;
        }
    }

    bool F()
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
