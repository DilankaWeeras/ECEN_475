#include "Graph.h"

/*
Build Graph:
Takes an instream for an input text file and will create a data structure Graph
out of the nodes in the text file.
*/
void Graph::buildGraph(std::ifstream &input)
{
    int nodes;
    int edges;

    std::string str;
    getline(input, str);
    std::stringstream ss(str);
    int num;
    ss >> nodes;
    ss >> edges;
    std::cout << "Nodes: " << nodes << " Edges: " << edges << std::endl
              << std::endl;

    node_list = std::vector<Node *>();

    for (int i = 0; i < nodes; i++)
    {
        Node *tempNode = new Node();
        tempNode->setLabel(i + 1);
        if (i < nodes / 2)
        {
            tempNode->setPartition(true);
        }
        else
        {
            tempNode->setPartition(false);
        }

        node_list.push_back(tempNode);
    }

    int node1;
    int node2;

    for (int i = 0; i < edges; i++)
    {
        getline(input, str);
        std::stringstream ss(str);

        ss >> node1;
        ss >> node2;

        node_list.at(node1 - 1)->adj_node_list.push_back(node_list.at(node2 - 1));
        node_list.at(node2 - 1)->adj_node_list.push_back(node_list.at(node1 - 1));
    }
}

/*
Calculate D:
This is a funciton that goes back through the nodes in the graph and will
calculate the D value for all Nodes.
*/
void Graph::calculateDAll()
{
    for (int i = 0; i < node_list.size(); i++)
    {
        node_list.at(i)->calculateD();
    }
}

/*
Swapping Funciton:
The swapping function will take all the nodes in the graph and iterate through Nodes
on the left side of the Partition and the Right side of the Partition. Using the D values that
repesent the effectivness of swapping 2 nodes it will use this formula --

deltaG = Dvalue(a) + Dvalue(b) - 2 * c(a,b)

--where c is whether or not the nodes a and b are connected

It will then swap the nodes and calculate the total gain.

This program does not compute the m value in the Kernigan-Lin algoritym. Instead it will hold
the values it gathered at the point of greatest gain and send that to the user at the end if those
values remain the greatest gain. This way the program will not need to recalculate all the way back
to the point of best gain.
*/
void Graph::swappingFunction()
{
    int deltaG = -1000000000; //Terrible CODING practice but with the first run boolean I would hit an infinite loop.
    Node *swapNode1;
    Node *swapNode2;

    for (int i = 0; i < node_list.size(); i++)
    {
        if (node_list.at(i)->locked == false)
        {
            for (int j = i + 1; j < node_list.size(); j++)
            {
                if ((node_list.at(j)->locked == false) && (node_list.at(i)->getPartition() != node_list.at(j)->getPartition()))
                {
                    int sub = 0;
                    if (node_list.at(i)->connected(node_list.at(j)))
                    {
                        sub = 2;
                    }
                    int tempG = node_list.at(i)->getD() + node_list.at(j)->getD() - sub;

                    /*std::cout << node_list.at(i)->getD() << " + " << node_list.at(j)->getD() << " - " << (node_list.at(i)->connected(node_list.at(j)) ? 2 : 0) << std::endl;
                    std::cout << "Label1: (" << node_list.at(i)->getLabel() << 
                                 ")\tLabel2: (" << node_list.at(j)->getLabel() << 
                                 ")\tDelta Gain at Nodes: (" << tempG << ")" << std::endl;
                    */
                    if (tempG > deltaG)
                    {
                        deltaG = tempG;
                        swapNode1 = node_list.at(i);
                        swapNode2 = node_list.at(j);
                    }
                }
            }
        }
    }

    //std::cout << "Swapping: (" << swapNode1->getLabel() << ") and (" << swapNode2->getLabel() << ") " << std::endl;

    totalGain += deltaG;
    bool tempBool = swapNode1->getPartition();
    swapNode1->setPartition(swapNode2->getPartition());
    swapNode2->setPartition(tempBool);
    swapNode1->locked = true;
    swapNode2->locked = true;
    if (totalGain > bestTotalGain)
    {
        /*
        std::cout << "Iterations: "<< iteration << std::endl;
        std::cout << "Total Gain: "<< totalGain << std::endl;
        std::cout << "Best Total Gain: "<< bestTotalGain << std::endl;
        std::cout << "Delta Gain: "<< deltaG << std::endl;
        */
        toString_Partition_NodesCut();
        //std::cout << carryFinalPartition << std::endl;

        bestTotalGain = totalGain;
    }
    //totalGain = temp_totalGain;
    //printNodes();
}

/*
All Fixed:
This function goes through all the nodes and determines if all nodes are locked or not.
If all nodes are fixed/locked then the swappingFunction will no longer iterate. The Iterations
occor in the main.cpp.
*/
bool Graph::allFixed()
{
    for (int i = 0; i < node_list.size(); i++)
    {
        if (node_list.at(i)->locked == false)
        {
            return false;
        }
    }
    return true;
}

/*
Print Nodes:
This funciton prints all the nodes and all adjacent nodes.
*/
void Graph::printNodes()
{
    for (int i = 0; i < node_list.size(); i++)
    {
        node_list.at(i)->printNode();
    }
    std::cout << "------------------------------------------" << std::endl;
}

/*
String Partition & Nodes Cut:
This function will Seperate the Nodes into partitions and also calculate all
the edges that are still cut.
*/
void Graph::toString_Partition_NodesCut()
{
    int totalCut = 0;
    std::stringstream send;
    std::string cut = "";
    send.clear();

    send << "Partition 1:\t||\tPartition 2:" << std::endl;
    for (int i = 0; i < node_list.size(); i++)
    {
        cut += node_list.at(i)->calculateE() + "\n";
        if (node_list.at(i)->getPartition())
        {
            send << node_list.at(i)->getLabel() << std::endl;
        }
        else
        {
            send << "\t\t\t" << node_list.at(i)->getLabel() << std::endl;
        }
        totalCut += node_list.at(i)->getECut();
    }
    send << std::endl
         << "Total Cut Connections: " << totalCut / 2 << std::endl;
    carryFinalPartition = send.str();
    carryFinalPartition += "\n" + cut;
}