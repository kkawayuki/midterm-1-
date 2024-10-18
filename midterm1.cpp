#include <iostream>  //allows for user input/output in terminal
#include <time.h>    //I added for better random variables, (seeding using time 0)
using namespace std; // allows usage of shortened syntax for standard (std::) relevant

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // intialization of constant constraint variables at global scope

class DoublyLinkedList // declare user-defined class "DoublyLinkedList"
{
private:        // list private variables/methods
    struct Node // define node struct in private scope of DoublyLinkedList class, DLL "has" Nodes (encapsulation)
    {
        int data; // the "data" stored in each node of DLL, an integer value
        Node *prev; // pointer to previous node in linked list
        Node *next; //pointer to next node in linked list
        Node(int val, Node *p = nullptr, Node *n = nullptr) //constructor for node, parameter-based, takes in an integer value, assigns *p and *n to nullptr
        {
            data = val; //assign data field in Node to parameter val
            prev = p; // assign pointer to previous node to p (nullptr)
            next = n; // assign pointer to next node to n (nullptr)
        }
    };

    Node *head; //the pointer to the head of the DLL
    Node *tail; //pointer to the tail of the DLL 

public:
    DoublyLinkedList() //parameterless constructor for DLL
    {
        head = nullptr; //assigns head field to nullptr
        tail = nullptr; //and tail. This is because at declaration-time of DLL class, it'll be empty, hence, head/tail ptrs will have nothing to point to.
    }

    void insert_after(int value, int position) //function to insert a node with int "value" after a specific int "poition" in the DLL
    {
        if (position < 0) //position parameter cannot be negative, can be zero because DLL starts at position 0, (head is 0)
        {
            cout << "Position must be >= 0." << endl; //output error message
            return; //terminate void function early with empty return
        }

        Node *newNode = new Node(value); // dynamically create a new node to populate, create pointer to node  
        if (!head) // if there's no head in DLL
        {
            head = tail = newNode; // set head and tail pointer to address of newNode
            return; //end function
        }

        Node *temp = head; //initialize a pointer to the head of the DLL
        for (int i = 0; i < position && temp; ++i) //run the following until arriving at the integer specified by position (so long as it's valid, &&temp signifies that temp!=nullptr)
            temp = temp->next; //go to location of next Node

        if (!temp) //if temp goes out of range of DLL, temp == nullptr
        {
            cout << "Position exceeds list size. Node not inserted.\n"; //output error message
            delete newNode; //delete the dynamically allocated node made earlier (as unable to insert into DLL)
            return; //end function
        }

        //assuming that no errors in input/reaching target location 
        newNode->next = temp->next; //have newNode's next pointer point to the next variable of temp (temp is location of insertion)
        newNode->prev = temp; //have newNode's previous pointer point to the current location (temp), because we're inserting newNode after location of current
        if (temp->next) //if it wasn't the last Node in DLL
            temp->next->prev = newNode; //make the node past the current node's previous value point to newNode (instead of current)
        else //if it is the last Node in DLL
            tail = newNode; //make the tail ptr of the DLL point to the location of the newNode
        temp->next = newNode; //have current node's next value be the location of the newNode
    }

    void delete_val(int value) //function to delete Nodes based on their int data in comparison to a passed int "value" parameter
    {
        if (!head) //if DLL empty
            return; //terminate

        Node *temp = head; // make pointer to iterate through DLL

        while (temp && temp->data != value) //while address temp != nullptr and its data isn't equivalent to parameter "value"
            temp = temp->next; //go to location of next Node

        if (!temp) //if temp == nullptr
            return; //terminate 

        if (temp->prev) //assumes now have reached desired node with data == value, so if it's not the head: 
            temp->prev->next = temp->next; //the current Node's previous value is becoming the next
        else //if it is the head
            head = temp->next; //make DLL's head point to the location of the current Node's next (because this one is getting deleted)

        if (temp->next) //if current not the tail
            temp->next->prev = temp->prev; //then make the Node after current's previous value point to the location of the current's previous (remove current from chain)
        else //if it is the tail
            tail = temp->prev; //then make the DLL's tail field point to the value before the tail

        delete temp; //delete node based off of pointer to current node
    }

    void delete_pos(int pos) //deletion based on the position int "pos" of a Node in the DLL (not value like previous)
    {
        if (!head) //if no head
        {
            cout << "List is empty." << endl; //output explanation message
            return; //terminate 
        }

        if (pos == 1) //if first node wanted to be removed
        {
            pop_front(); //use pop_front() function to "pop" the first Node out of the DLL, (delete it)
            return; //terminate 
        }

        Node *temp = head; //make pointer to iterate through DLL

        for (int i = 1; i < pos; i++) //run the following until i == int position:
        {
            if (!temp) //if temp == nullptr
            {
                cout << "Position doesn't exist." << endl; //out of range, output error
                return; //terminate
            }
            else //if not out of range
                temp = temp->next; //go to location of next node 
        }
        if (!temp) //if final position after iteration invalid
        {
            cout << "Position doesn't exist." << endl;//out of range, output error
            return;//terminate
        }

        if (!temp->next) //if last node in DLL
        {
            pop_back(); //can use pop_back() function to delete last Node
            return; //terminate
        }

        Node *tempPrev = temp->prev; //make pointer to current Node's previous node
        tempPrev->next = temp->next; //make the previous node's next value point to the node after current (remove pointer to current)
        temp->next->prev = tempPrev; //make the Node after current point to the Node before current
        delete temp; //now that pointers don't reference the node (node isolated), delete it
    }

    void push_back(int v) //function to add node to tail of DLL (last element)
    {
        Node *newNode = new Node(v); //make new node dynamically, initialize with parameter v indicating data
        if (!tail) //if there's no tail (empty DLL)
            head = tail = newNode; //make both pointers point to the newNode
        else //if there are Nodes
        {
            tail->next = newNode; //make the tail Node's next value point to the new Node
            newNode->prev = tail; //make the newnode's previous point to the current tail
            tail = newNode; // update tail of DLL to point to newNode
        }
    }

    void push_front(int v) //function to add node to head of DLL
    {
        Node *newNode = new Node(v);//make new node dynamically, initialize with parameter v indicating data
        if (!head)//if there's no head (empty DLL)
            head = tail = newNode; //make both pointers point to the newNode
        else //if there are Nodes
        {
            newNode->next = head; //make the next pointer of the newNode point to the head of the array
            head->prev = newNode; //make the current head's previous pointer point to the newNode
            head = newNode;// update head of DLL to point to newNode
        }
    }

    void pop_front() //function to get delete first element of DLL
    {

        if (!head) // if head == nullptr
        {
            cout << "List is empty." << endl; //error message
            return; //end function
        }

        Node *temp = head; // make pointer temp point to the head (to be popped)

        if (head->next) //if head->next != nullptr
        {
            head = head->next; //move head pointer of DLL to next Node (second node)
            head->prev = nullptr; //make the head's previous pointer nullptr 
        }
        else // or if the DLL is empty
            head = tail = nullptr; //make both head and tail point to null (empty)
        delete temp; //delete firnode
    }

    void pop_back()//function to get delete last element of DLL
    {
        if (!tail) //if no tail
        {
            cout << "List is empty." << endl; //error message
            return; //end function
        }
        Node *temp = tail; // point temp to the location of tail

        if (tail->prev) //if tail has a previous Node
        {
            tail = tail->prev; //make the tail point to that previous node
            tail->next = nullptr; //make the tail's next pointer point to null 
        }
        else //or if empty DLL
            head = tail = nullptr;  //make both head and tail point to null (empty)
        delete temp; //delete last node
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element() // my code, a public method to print every other data struct (node)
    {
        Node *current = head; // set a navigation pointer to start at head of DLL
        if (!current) //if the list is empty
        {
            cout << "List is empty." << endl; //output error message
            return; //return, end function early. Because function is void, doesn't have to return value
        }
        for (int i = 0; current; i++) // essentially a while loop with an iterator built in, (while current != nullptr)
        {
            if (i % 2 == 0) // if the index tracking the number of nodes visited is even (prints first, 0th element, skips second (1st), prints third (2nd), etc.)
            {
                cout << current->data << " "; // output the data of the node, formatted
            }
            current = current->next; // move navigation pointer to address of next node
        }
        cout << '\n'; // format with a new line (endl also works)
    }
};

int main()
{
    srand(time(0)); //seed random with time 0, the current time, allows good random number generation for later code

    const int LISTSIZE = (rand() % (MAX_LS - MIN_LS + 1)) + 5; // random 0-15 number due to %15+1, then, + 5 to make into 5-20, random list size
    DoublyLinkedList list; //declare linked list object to fill later

    for (int i = 0; i < LISTSIZE; i++) // assignment loop that iterates LISTSIZE number of times, listsize being the random 5-20 number generated based on global variables
    {
        list.push_front((rand() % 10) + 1); // populate linked list with nodes of values ranging from 1-10 to distinguish
    }

    cout<< "Printing all: "; // message to explain what the following function call's output means
    list.print(); // show resultant values of Linked List

    cout<< "Printing every other: "; // message to explain what the following function call's output means
    list.every_other_element(); // show what happens when only every other value is printed

    return 0; //signal to main() that application run was successful
}