#include "Node.h"

/*
Print Node:
Funciton that will print the nodes member variables
*/
void Node::printNode()
{
    std::cout << "Label: " << label << std::endl;
    std::cout << "Partition: " << partition << std::endl;
    std::cout << "Fixed: " << locked << std::endl;
    std::cout << "Adjacent Nodes: " << std::endl; 
    for (int i = 0; i < adj_node_list.size(); i++)
    {
        std::cout << adj_node_list.at(i)->label << std::endl;
    }
    std::cout << std::endl;
}

/*
Calcuate E:
This funciton calculates the amount of Edges that are cut (Ec) 
and not cut (Enc) by iterating through the Adjacent nodes and counting
whether or not they exist in the same partition.
*/
std::string Node::calculateE()
{
    std::string cuts = "";
    Enc = 0;
    Ec = 0;

    for (int i = 0; i < adj_node_list.size(); i++)
    {
        if (this->getPartition() == adj_node_list.at(i)->getPartition())
        {
            Enc++;
            cuts += "(" + std::to_string(label) + ") ----- (" + std::to_string(adj_node_list.at(i)->getLabel()) + ")\t";
        }
        else
        {
            Ec++;
            cuts += "(" + std::to_string(label) + ") --|-- (" + std::to_string(adj_node_list.at(i)->getLabel()) + ")\t";
        }
    }
    return cuts;
}

/*
Calcuate D:
If the Node is unlocked it will calculate the D value
D = Edges Cut - Edges not cut
*/
void Node::calculateD()
{
    calculateE();
    if (!locked)
    {
        D = Ec - Enc;
    }
}

/*
Boolean connected:
returns true if this node is connected to Node n
*/
bool Node::connected(Node *n)
{
    for (int i = 0; i < adj_node_list.size(); i++)
    {
        if (n == adj_node_list.at(i))
        {
            return true;
        }
    }
    return false;
}
