#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <bits/stdc++.h>
#include "Node.h"

class Stockmeyer
{
private:
    std::vector<Node *> node_list;
    int total_width;
    int total_height;

public:
    Stockmeyer() : head(nullptr), total_width(0), total_height(0){}; // constructor
    ~Stockmeyer(){};                                                 // destructor

    Node *head;

    void inputList(std::ifstream &input);
    int calculateHeight(Node *root);
    int calculateWidth(Node *root);

    void RotateNodes(Node *root);
    void printBestArea();

    int getTotalHeight() { return total_height; }
    int getTotalWidth() { return total_width; }

    void printNodesV();
    void printNodesTreeCalc();
};