#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include <string>

class Node
{
private:
    int label; // the name of the Node
    bool partition; // This is a boolean variable because only 2 partitions exist
    int D; // D is the value for Ec - Enc
    int Enc; // Enc are the not cut edges
    int Ec; // Ec are the cut edges

public:
    std::vector<Node *> adj_node_list; // the adjacency list holds all the nodes that are connected to this node
    bool locked; // boolean for locked Node

    Node() : label(0), partition(0), D(0), Enc(0), Ec(0), locked(false) {} // Default constructor

    //Getter Functions
    int getLabel() { return label; }
    int getPartition() { return partition; }
    int getD() { return D; }
    int getENotCut() { return Enc; }
    int getECut() { return Ec; }

    //Set Functions
    void setLabel(int l) { label = l; }
    void setPartition(bool p) { partition = p; }

    //Calculate Functions;
    void calculateD();
    std::string calculateE();

    bool connected(Node *n);
    
    //Print Functions
    void printNode();
};
#endif