#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Graph
{
public:
    std::vector<Node *> node_list; // node list for the graph
    int iteration; // shows the user how many iterations have occored
    int totalGain; // totalGain during each iteration
    int bestTotalGain; // holds the value of the best total gain
    std::string carryFinalPartition; // A string to hold the values of the best iteration

    Graph() : iteration(1), totalGain(0), bestTotalGain(0){}; // constructor
    ~Graph(){}; // destructor

    void buildGraph(std::ifstream &input);

    void calculateDAll();

    void swappingFunction();
    bool allFixed();

    void printNodes();
    void toString_Partition_NodesCut();
};
#endif