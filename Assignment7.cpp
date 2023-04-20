/*
 Name: Rohaan Kamaraj
 Email: rkamara1@asu.edu
 Description: This file contains all the user input and user interfacing. I create a graph data
 structure and after the user inputs the nodes for the graph, a Breadth First Search is performed.
 */

#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

    //gets the number of edges for the Graph
    int edges;
    cin >> edges;

    Graph* graph = new Graph(edges);


    //populates the adjacency list by inserting each edge as the head of each linked list
    for (int i = 0; i < edges; i++) {
        string edgeName;
        getline(cin >> ws, edgeName);
        graph->insertEdge(edgeName, i);
    }

    //gets the number of pairs for the graph
    int pairs;
    cin >> pairs;

    //inserts the pairs bi-directionally inside the adjacency list
    for (int i = 0; i < pairs; i++) {
        string pairName;
        getline(cin >> ws, pairName);
        string originalInformation, newInformation, divider;
        int count = 0;
        //i use the count variable to differentiate which is the originalInfo (which LinkedList
        //the newInfo (the paired element) should be entered in).
        while (count < 2) {
            divider = pairName.substr(0, pairName.find_first_of(","));
            pairName = pairName.substr(pairName.find_first_of(",") + 1);
            if (count == 0) {
                originalInformation = divider;
            } else {
                newInformation = divider;
            }
            count++;
        }
        graph->insertNode(originalInformation, newInformation);
    }


    //Prints out the adjacency list
    graph->printGraph();

    //Performs the Breadth First Search on the graph
    graph->breadthFirstSearch();

}

