#學號:OCE222883530  姓名:莊郁琳 
//********************************************************************************/
// Exercise 03: Infix2Postfix & Postfix Evaluator by Wu, Yi-Hung@ICE.CYCU, 2021
//********************************************************************************/
#define QUIZ

#include <string>                                               // string class
#include <cstdlib>                                              // system, atoi
#include "DSAPCS1092ex3__OCE222883530.hpp"                                       // header file for expLIST class
#include "DSAPCS1092ex4__OCE222883530.hpp"                                      // header file for expSTACK class

#define MAX_LEN 255                                             // maximum string length
#define TAB     '\t'                                            // tabular key character
#define WS      ' '                                             // white space character

using namespace std;

bool isExp(string&);		                                    // check the validity of each symbol
bool isNumber(const char);		                                // check whether the character is a number
bool isOp(const char);		                                    // check whether the character is an operator
bool isPar(const char);		                                    // check whether the character is a parenthesis
bool isBalanced(const string);		                            // check the validity of balanced parentheses
bool isInfix(const string);		                                // check whether it is an infix expression
void str2list(const string, expLIST<string>&);                  // parse a string into a linked list
bool infix2postfix(expLIST<string>&, expLIST<string>&);         // transform infix into postfix
void postfixEval(expLIST<string>&);                             // evaluate the value of postfix

int main(void)
{   int command;									            // user command

    do
    {   string  infixS;

        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Infix2postfix Evaluation     *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice(0, 1): ";
        cin >> command;     							        // get a command
        cin.ignore(MAX_LEN, '\n');							    // clear the input buffer
        switch (command)
        {	case 0: break;
            case 1: cout << endl << "Input an infix expression: ";
                    getline(cin, infixS);
                    if (isExp(infixS) &&                        // check each symbol & remove useless ones
                        isBalanced(infixS)                      // check the validity of balanced parentheses
                        && isInfix(infixS))                     // check whether it is an infix expression
                    {   expLIST<string> infixE, postfixE;

                        str2list(infixS, infixE);               // parse a string into a linked list
                        if (infix2postfix(infixE, postfixE))    // transform infixS into postfixS
#ifdef QUIZ
                            postfixEval(postfixE);              // evaluate the value of postfixS
#else
                            ;
#endif
                    }   // end if
                    break;
            default: cout << endl << "Command does not exist!" << endl;
        }	// end switch
    } while (command != 0);						                // '0': stop the program
    system("pause");										    // pause the display
    return 0;
}	// end main

//********************************************************************************/
// Mission I. inExp(), isNumber(), isOp(), isDel(), isBalanced(), isInfix()
//********************************************************************************/
bool isExp(string &S)		                                    // check the validity of each symbol
{   for (int i = 0; i < S.size(); ++i)
        if ((S[i] == WS) || (S[i] == TAB))
        {   S.erase(S.begin()+i);                               // remove white space characters
            --i;                                                // move backward one position
        }   // end if
        else if ((!isNumber(S[i])) && (!isOp(S[i])) && (!isPar(S[i])))   // numbers, operators, parentheses only
        {   cout << "Error 1: " << S[i] << " is not a legitimate character." << endl;
            return false;
        }   // end else-if
    return true;
}   // end isExp

bool isNumber(const char c)		                                // check whether the character is a number
{   return ((c >= '0') && (c <= '9'));						    // only a single number in [0,9] is allowed
}   // end isNumber

bool isOp(const char c)		                                    // check whether the character is an operator
{   return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));  // only 4 types of operators are allowed
}   // end isOp

bool isPar(const char c)		                                // check whether the character is a parenthesis
{   return ((c == '(') || (c == ')'));                          // only 2 types of parentheses are allowed
}   // end isDel

bool isBalanced(const string S)		                            // check the validity of balanced parentheses
{   int leftC = 0;

    for (int i = 0; (i < S.size()) && (leftC >= 0); i++)
        switch (S[i])
        {   case '(':   leftC++;
                        break;
            case ')':	leftC--;
        }   // end switch
    if (leftC)
    {   if (leftC > 0)
            cout << "Error 2: there is one extra open parenthesis." << endl;
        else
            cout << "Error 2: there is one extra close parenthesis." << endl;
        return false;
    }   // end if
    return true;
}   // end isBalanced

bool isInfix(const string S)		                            // check whether it is an infix expression
{   int NO_OP = -1;

    for (int j, i = 0; ((i < S.size()) && ((NO_OP == 0) || (NO_OP == -1))); i++)
        if (isNumber(S[i]))                                     // gather contiguous numbers
        {   ++NO_OP;
            j = 1;
            while ((i+j < S.size()) && (isNumber(S[i+j])))
                ++j;
            i += j - 1;
        }   // end if
        else if (isOp(S[i]))
            --NO_OP;
        else if (isPar(S[i]))
            if (((S[i] == '(') && (isOp(S[i+1]) || (S[i+1] == ')'))) ||
                ((S[i] == ')') && (isOp(S[i-1]) || (S[i-1] == '('))))
            {   cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }   // end inner-if
    if (NO_OP)
    {   if (NO_OP > 0)
            cout << "Error 3: there is one extra operand." << endl;
        else
            cout << "Error 3: there is one extra operator." << endl;
        return false;
    }   // end if
    cout << "It is a legitimate infix expression." << endl;
    return true;
}   // end isInfix

//********************************************************************************/
// Mission II. str2list(), infix2postfix()
//********************************************************************************/
void str2list(const string S, expLIST<string> &EL)              // parse a string into a linked list
{   for (int j, i = 0; i < S.size(); i++)			            // read the characters one by one
    {   if (isNumber(S[i]))                                     // gather a series of contiguous numbers
        {   j = 1;
            while ((i+j < S.size()) && (isNumber(S[i+j])))
                ++j;
            EL.ins(S.substr(i,j));
            i += j - 1;
        }   // end if
        else if (S[i] != WS)                                    // keep one operator or delimiter
            EL.ins(S.substr(i,1));
    }   // end for
    EL.show();
}   // end str2list

bool infix2postfix(expLIST<string> &ifxE, expLIST<string> &pfxE)    // transform infixS into postfixS
{   expSTACK<string>    aStack;							        // stack object: value type is <char>

    while (!ifxE.isEmpty())                                     // read the list elements one by one
    {   string  cur;

        ifxE.del(cur);
        if (isNumber(cur[0]))							        // directly output the operand
            pfxE.ins(cur);
        else if (isOp(cur[0]))                                  // newcomer is an operator
            while (!aStack.isEmpty())
            {   string  temp;

                aStack.pop(temp);
                if (isOp(temp[0]))                              // another operator on top of stack
                {                                               // validate the operator precedence
                    if (((cur[0] == '*') || (cur[0] == '/')) &&
                        ((temp[0] == '+') || (temp[0] == '-')))
                    {                                           // only case to stop removing top of stack
                        aStack.push(temp);                      // put operator back
                        break;
                    }   // end inner if
                    else
                        pfxE.ins(temp);                         // output the operand (top of stack)
                }   // end outer if
                else if (temp[0] == '(')
                {
                    aStack.push(temp);                          // put '(' back for future ')'
                    break;
                }   // end inner else-if
                else
                    return false;                               // other symbols mean invalid
            }   // end while
        if ((cur[0] == '(') || (isOp(cur[0])))                  // keep the operator in stack
            aStack.push(cur);
        else if (cur[0] == ')')
            do
            {   string  temp;

                if (aStack.isEmpty())                           // unable to find '('
                    return false;
                aStack.pop(temp);
                if (temp[0] == '(')                             // find a matched '('
                    break;
                if (isOp(temp[0]))
                    pfxE.ins(temp);                             // output the operator
                else
                    return false;                               // other symbols mean invalid
            } while (1);
    }   // end for
    while (!aStack.isEmpty())
    {   string  temp;

        aStack.pop(temp);
        if (isOp(temp[0]))
            pfxE.ins(temp);                                     // output the operator
        else
            return false;                                       // other symbols such as '(' mean invalid
    }   // end while
    cout << "Postfix expression: ";
    pfxE.show();                                                // show the postfix expression as a result
    return true;
}   // end infix2postfix

//********************************************************************************/
// Mission III. postfixEval()
//********************************************************************************/
void postfixEval(expLIST<string> &pE)                           // evaluate the value of postfix
{   bool            success = true;                             // see whether it is an invalid expression
    int             value;
    expSTACK<int>   aStack;                                     // stack object with type <int>

    while (success && (!pE.isEmpty()))                          // read the list elements one by one
    {   string  cur;

        pE.del(cur);
        if (isNumber(cur[0]))                                   // keep the operands in stack
            aStack.push(atoi(cur.c_str()));					    // transform a character into a number
        else if (isOp(cur[0]) && (!aStack.isEmpty()))		    // newcomer is an operator
        {   int   v2;

            aStack.pop(v2);					                    // the second operand
            if (!aStack.isEmpty())
            {   int   v1, temp;

                aStack.pop(v1);						            // the first operand
                switch (cur[0])					                // calculate the temporary result
                // (1) add the codes to do the arithmetic
				{   case '+':  temp = v1+ v2  ;
                               break;
                    case '-':  temp = v1-v2 ;
                               break;
                    case '*':  temp = v1*v2 ;
                               break;
                    case '/':  if(v2!=0)                              
// (2) avoid the division by zero
                               temp = v1/v2;
                               else
                               {
                               	success = false;
							   }
                                break;
                    default:    success = false;
                }   // end switch
                aStack.push(temp);                              // save the temporary result
            }   // end inner if
            else
                success = false;
        }   // end else-if
        else
            success = false;
    }   // end while
    if (!aStack.isEmpty())
        aStack.pop(value);
    if (success && aStack.isEmpty())
        cout << "Answer: " << value << endl;                   // show the computed value as a result
    else
        cout << "### It cannot be successfully evaluated! ###" << endl;
}   // end postfixEval
//********************************************************************************/
