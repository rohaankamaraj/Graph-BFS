/*
 Name: Rohaan Kamaraj
 Email: rkamara1@asu.edu
 Description: This file contains a Queue implementation using a LinkedList with some basic methods
 */

#include "LinkedList.h"

using namespace std;

//QUEUE IMPLEMENTATION
class Queue {

private:
    // private instance data
    LinkedList* queue;

public:
    // public methods
    Queue(int);
    void enqueue(string);
    void dequeue();
    void printQueue();
    bool isEmpty();
    Node* getHead();
};

// constructor for Queue
Queue::Queue(int userSize) {
    queue = new LinkedList[userSize];
}

//Adds node to the back of the queue
void Queue::enqueue(string userInformation) {
    queue->addNode(userInformation);
}

//Removes node from the front of the queue
void Queue::dequeue() {
    queue->removeNode();
}

//prints the queue
void Queue::printQueue() {
    queue->print();
}

//returns true if the Queue is empty, false if the Queue is populated
bool Queue::isEmpty() {
    return queue->isEmpty();
}

//gets the first element of the Queue
Node* Queue::getHead() {
    return queue->getHead();
}