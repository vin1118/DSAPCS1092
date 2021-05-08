#// 學號:OCE222883530  姓名:莊郁琳 
//*************************************************************/
//Header file for expLIST class Yi-Hung Wu    2021
//*************************************************************/
#include <iostream>	                                    // endl
#include <new>	                                        // new

using namespace std;								    // standard naming space

template <class T>                                      // type template for data value in list node

class   expLIST
{   typedef struct qN								    // structure of each node in list
    {   T           value;
        struct qN   *next;    						    // next node
    }   listNode;
    listNode *head, *tail; 						        // only two data members
public:
    expLIST(): head(NULL), tail(NULL)        		    // constructor with initialization
    {	} //end expLIST initializer
  
    bool isEmpty()  const 							    // decide whether list is empty
    {   return head == NULL;
// (1) correct the code to check whether it is empty
    }  //end expLIST::isEmpty

    void ins(const T inValue)					        // append one value into list
    {   try
        {	listNode *newPtr = new listNode;

            newPtr->value = inValue;
            newPtr->next = NULL;
// (2) complete the code to insert a node (newPtr)
            if (isEmpty())                              // create the first node
               head = newPtr;
            else
               tail->next = newPtr;               		// append the last node
               tail = newPtr;                         	// move to the tail
        } // end try
        catch (std::bad_alloc& ba)					    // unable to allocate space
        {   std::cerr << endl << "bad_alloc on list caught: " << ba.what() << endl;
        }   // end catch
    }	// end expLIST::ins

    void getHead(T& outValue)						    // get the head of list without removal
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty list!" << endl;
        else
            outValue = head->value;
    }	// end expLIST::getHead

    void del()									        // remove the head of list
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty list!" << endl;
        else
        {	listNode *tempPtr = head;
            head = head->next;
// (3)  the code to delete the first node (temp)
            if (isEmpty())                              // the last node is removed
            tail = NULL;
            tempPtr->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
        } // end else
    }	// end expLIST::del without output parameter

    void del(T& outValue)						        // get the head of stack and remove it
    {	getHead(outValue);
        del();
    }	// end expLIST::del with output parameter

    void show()                                         // display the content of each node in sequence
    {   if (!isEmpty())
        {   cout << head->value;						// print the 1st value
// (4) fill the code to print the next values in the order of linked list (head->next)
         for(listNode *cur = head->next; cur != NULL; cur = cur->next)
            cout <<"," << cur->value;
		    cout << endl;
        }   // end if
    }   //end expLIST:show

    void clearUp()									    // clear up the entire list
    {   while (!isEmpty())
            del();
    }   // end clearUp

    ~expLIST()										    // destructor
    {   clearUp();
    }   // end destructor
};	//end expLIST class
//********************************************************************************/
// The above is self-defined expLIST class, used for keeping a series of strings
//********************************************************************************/
