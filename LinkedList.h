/*
 Name: Rohaan Kamaraj
 Email: rkamara1@asu.edu
 Description: This file contains a Node implementation, as well as a LinkedList implementation
 with basic methods
 */

#include <string>
#include <iostream>

using namespace std;

//NODE IMPLEMENTATION
class Node {
private:
    //private instance data
    string information;
    Node* next;

public:
    // constructor + accessor/mutator methods
    Node(string);
    Node* getNext();
    string getInformation();
    void setNext(Node*);

};

//constructor implementation
Node::Node(string userInformation) {
    information = userInformation;
    next = NULL;
}

//accessor for next node
Node* Node::getNext() {
    return next;
}

//accessor for node's information
string Node::getInformation() {
    return information;
}

//mutator to point to next node
void Node::setNext(Node* userNext) {
    next = userNext;
}

//LINKEDLIST IMPLEMENTATION
class LinkedList {
private:
    //private instance data
    Node* head;
    Node* tail;

public:
    // public methods
    LinkedList();
    void addNode(string);
    int getLength();
    Node* getHead();
    void printList();
    void removeNode();
    void print();
    bool isEmpty();
};

// default constructor
LinkedList::LinkedList() {
    head = NULL;
    tail = NULL; // I added a tail to make adding to the end of the LinkedList easier for me to do.
}

//adds node to the end of linked list
void LinkedList::addNode(string information) {
    Node* node = new Node(information);
    if (head == NULL && tail == NULL) { // if the list is empty
        head = node;
        tail = node;
    } else { // if the list isn't empty
        tail->setNext(node);
        tail = node;
    }
}

//gets the amount of elements of linked list
int LinkedList::getLength() {
    int length = 0;
    Node* node = head;

    while (node != NULL) {
        length++;
        node = node->getNext();
    }
    return length;
}

//gets the first element (the head) of the LinkedList
Node* LinkedList::getHead() {
    return head;
}

//prints elements of linked list in a neat format
void LinkedList::printList() {
    if (head == NULL && tail == NULL) {
        // if the list is empty, though it shouldn't be when this method is called in the driver class
    } else {
        Node* node = head;
        //print out the head
        cout << "From: " + node->getInformation() << endl;
        node = node->getNext();
        //print out the other elements
        while (node != NULL) {
            cout << "To: " + node->getInformation() << endl;
            node = node->getNext();
        }
        cout << endl;
    }
}

//removes node from the front of the list
void LinkedList::removeNode() {
    Node* node = head;
    head = head->getNext();
    free(node);
}

//this print method is what I'm going to call in my printQueue() method in my Queue class
void LinkedList::print() {
    if (head == NULL && tail == NULL) {
        cout << "empty" << endl;
    } else {
        // need length & tracker to determine when to add a comma between each node's information and
        // when the comma is not needed
        Node* node = head;
        int length = getLength();
        int tracker = length - 1;
        cout << "{ ";
        while (node != NULL) {
            if (length == 1) { // doesn't need comma
                cout << node->getInformation();
            }
            if (length > 1 && tracker >= 1) { // need comma since another element is going to be printed after
                cout << node->getInformation() + ", ";
            } else if (length > 1 && tracker < 1) { // doesn't need comma
                cout << node->getInformation();
            }
            tracker -= 1;
            node = node->getNext();
        }
        cout << " }" << endl;
    }
}

//returns true if the list is empty, false if the list is populated: I'm only using this method in my
//Queue class.
bool LinkedList::isEmpty() {
    if (getLength() == 0) {
        return true;
    }
    return false;
}
