/*
 Name: Rohaan Kamaraj
 Email: rkamara1@asu.edu
 Description: This file contains a Graph implementation with some basic methods and a breadth
 first search implementation
 */

#include <string>
#include <iostream>
#include "Queue.h"

//GRAPH IMPLEMENTATION
class Graph {

private:
    //private instance data
    LinkedList* graph;
    int size;

public:
    //public methods
    Graph(int);
    void insertNode(string, string);
    void insertEdge(string, int);
    void printGraph();
    void breadthFirstSearch();
};

//Graph constructor
Graph::Graph(int userSize) {
    graph = new LinkedList[userSize];
    size = userSize;
}

//Finds where the pair should be inserted in the Graph, and inserts it in that place
void Graph::insertNode(string originalInfo, string newInfo) {
    for (int i = 0; i < size; i++) {
        if (graph[i].getHead()->getInformation() == originalInfo) {
            graph[i].addNode(newInfo);
            for (int i = 0; i < size; i++) {
                if (graph[i].getHead()->getInformation() == newInfo) {
                    graph[i].addNode(originalInfo);
                }
            }
        }
    }

}

//Used to initially populate the adjacency list with all the edges.
void Graph::insertEdge(string userInformation, int placement) {
    graph[placement].addNode(userInformation);
}

//Prints the graph out in a nice format.
void Graph::printGraph() {

    cout << "The Graph Content:" << endl;
    cout << "-------------------" << endl;

    for (int i = 0; i < size; i++) {
        graph[i].printList();
    }

}

//My BreadthFirstSearch implementation for Graph
void Graph::breadthFirstSearch() {

    cout << "BFS being performed..." << endl;

    //create my colors (used for Queue population/depopulation), pi and distance arrays
    string colors[size];
    string pi[size];
    int distance[size];

    //paint all the vertices white
    for (int i = 0; i < size; i++) {
        colors[i] = "white";
        pi[i] = "none";
        distance[i] = 0;
    }

    //since the search always starts with the head of the first linked list in the adjacency list,
    //i paint that vertice gray.
    colors[0] = "gray";
    pi[0] = "none";
    distance[0] = 0;

    //Create my queue, and then enqueue the head of the first linked list in the adjacency list
    Queue *queue = new Queue(size);
    queue->enqueue(graph[0].getHead()->getInformation());
    int count = 1, traversal = 0; // these are used to help determine the distance for all the vertices

    cout << "The Queue content:" << endl << endl;

    while (!queue->isEmpty()) {
        queue->printQueue();
        Node *head = queue->getHead();

        //determine which linked list from the adjacency list we are going into based on the
        //head of the Queue
        int start = 0;
        for (int i = 0; i < size; i++) {
            if (head->getInformation() == graph[i].getHead()->getInformation()) {
                start = i;
                break;
            }
        }

        //check if those elements from the linked list determined are visited
        Node *node = graph[start].getHead();
        for (int i = 1; i < graph[start].getLength(); i++) {
            node = node->getNext();
            //find the position of current element in the graph
            int position = 0;
            for (int i = 0; i < size; i++) {
                if (node->getInformation() == graph[i].getHead()->getInformation()) {
                    position = i;
                    break;
                }
            }
            //position has been found, now process it if it's color is white, which means it hasn't
            //been processed yet.
            if (colors[position] == "white") {
                colors[position] = "gray";
                distance[position]+= count;
                pi[position] = head->getInformation();
                queue->enqueue(node->getInformation());
            }
        }

        //removes the first element from the Queue.
        queue->dequeue();
        traversal++;

        //this is for the distance array, making sure those values are correct
        if (traversal % 2 == 1) {
            count++;
        }

        //this is to make sure the distance doesn't exceed a point where it would be impossible
        if ((size / 3) < count) {
            count--;
        }

        //if the graph contains any vertice that doesn't connect to the head of the first linked list,
        //then this will make sure that the separate vertice(s) get processed.
        if (queue->isEmpty()) {
            for (int i = 0; i < size; i++) {
                if (colors[i] == "white") {
                    //Create a new queue, then point the old queue to the new queue's contents
                    Queue* queue2 = new Queue(size);
                    queue2->enqueue(graph[i].getHead()->getInformation());
                    queue = queue2;
                    colors[i] = "gray"; //it has been discovered, so it will be painted gray
                    count = 1; //resets count bc we have a new "starting point"
                    break;
                }
            }
        }

    }

    cout << endl;
    //printing out the pi array content
    cout << "The array pi content:" << endl << endl;
    for (int i = 0; i < size; i++) {
        cout << "pi[" + graph[i].getHead()->getInformation() + "]";
        cout << "= " + pi[i] << endl;
    }

    cout << endl;

    //printing out the distance array content
    cout << "The array distance content:" << endl << endl;
    for (int i = 0; i < size; i++) {
        cout << "distance[" + graph[i].getHead()->getInformation() + "]";
        cout << "=" + to_string(distance[i]) << endl;
    }

}

