#//學號：OCE222883530 姓名:莊郁琳 
//********************************************************************************/
//Header file for expSTACK class Yi-Hung Wu    2015/11/20
//********************************************************************************/
#include <iostream>	                                            // endl
#include <new>	                                                // new

using namespace std;										    // standard naming space

template <class T>                                              // type template for data value in stack node

class   expSTACK
{   typedef struct sN										    // structure of each node in stack
    {   T           value;
        struct sN   *next;    								    // next node
    }   stackNode;
    stackNode *topPtr; 										    // only one data member
public:
    expSTACK(): topPtr(NULL)        						    // constructor with initialization
    {	} //end expSTACK initializer

    bool isEmpty()  const 									    // decide whether stack is empty
    {   return topPtr == NULL;
    }  //end expSTACK::isEmpty

    void push(const T inValue)								    // add one value into stack
    {   try
        {	stackNode *newPtr = new stackNode;

            newPtr->value = inValue;
            newPtr->next = topPtr;
            topPtr = newPtr;
        } // end try
        catch (std::bad_alloc& ba)						        // unable to allocate space
        {   std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
        }   // end catch
    }	// end expSTACK::push

    void getTop(T& outValue)								    // get the top of stack without removal
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty stack!" << endl;
        else
            outValue = topPtr->value;
    }	// end expSTACK::getTop

    void pop()											        // remove the top of stack
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty stack!" << endl;
        else
        {	stackNode *tempPtr = topPtr;

            topPtr = topPtr->next;
            tempPtr->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
        } // end else
    }	// end expSTACK::pop without output parameter

    void pop(T& outValue)									    // get the top of stack and remove it
    {	getTop(outValue);
        pop();
    }	// end expSTACK::pop with output parameter

    ~expSTACK()											        // destructor
    {   while (!isEmpty())
            pop();
    }   // end destructor
};	//end expSTACK class
//********************************************************************************/
// The above is self-defined expSTACK class, used for keeping a series of values
//********************************************************************************/
