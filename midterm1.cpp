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
        Node *prev; // po
        Node *next;
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(int value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value)
    {
        if (!head)
            return;

        Node *temp = head;

        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
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