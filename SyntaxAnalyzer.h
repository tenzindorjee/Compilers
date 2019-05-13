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
        return tokenVect[0].tokens;
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

    void TDPparser()
    {
        if (tokenVect[incrementCount].lexemes == "$" || tokenVect[incrementCount].lexemes == "%")
        {
            incrementCount++;
            if (tokenVect[incrementCount].lexemes == "$" || tokenVect[incrementCount].lexemes == "%")
            {
                incrementCount++;
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
            increment++;
            return true;
            }
            else
            {
                return false;
            }
                
        }
        else 
        {
             return false;
        }
           
    }
    
    bool E()
    {
        if (tokenVect[incrementCount].lexemes == "(")
        {
            TDPstack.pop();
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;
            TDPstack.push("Q");

            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].tokens == "IDENTIFIER")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;
            TDPstack.push("Q");
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

            TDPstack.push("+");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("Q");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "-")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("-");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("T");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("Q");
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

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
            j
        }

        else if (tokenVect[incrementCount].lexemes == "(")
        {

            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }
        else
        {
            cout << "ERROR: <Term> -> <Factor> <TermPrime> ";
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

            TDPstack.push("*");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("R");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else if (tokenVect[incrementCount].lexemes == "/")
        {
            cout << "POP " << TDPstack.top() << endl;
            TDPstack.pop();

            TDPstack.push("/");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("F");

            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("R");
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

            TDPstack.push("(");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push("E");
            cout << "PUSH " << TDPstack.top() << endl;

            TDPstack.push(")");
            cout << "PUSH " << TDPstack.top() << endl;
            return true;
        }

        else
        {
            cout << "ERROR: F->(E)|i " << endl;
        }
    }
};
