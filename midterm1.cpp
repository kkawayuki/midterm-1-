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

        for (int i = 1; i < pos; i++) //run the following until 
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
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