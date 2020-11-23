#ifndef NODE_H
#define NODE_H

#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <bits/stdc++.h>

//  enum class cut {None = 0, Verticle = 1, Horizontal = 2};

class Node
{
public:
    int cut_type; // None = 0, Verticle = 1, Horizontal = 2
    int width;
    int height;

    Node *left;
    Node *right;

    std::vector<std::pair<int, int>> calc_pairs;

    Node(int type)
    {
        cut_type = type;
        width = 0;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(int w, int h)
    {
        cut_type = 0;
        width = w;
        height = h;
        calc_pairs.push_back(std::make_pair(width, height));
        if (width != height)
        {
            calc_pairs.push_back(std::make_pair(height, width));
        }
        left = nullptr;
        right = nullptr;
    }
    ~Node() {}

    //Print Functions
    void printNode()
    {
        switch (cut_type)
        {
        case 0:
            std::cout << "W: " << width
                      << "\tH: " << height;
            break;
        case 1:
            std::cout << "(V)";
            break;
        case 2:
            std::cout << "(H)";
            break;
        default:
            std::cout << "NO TYPE";
            break;
        }
    }
    void printNodeCalc()
    {
        std::cout << "D = {";
        for (int i = 0; i < calc_pairs.size(); i++)
        {
            std::cout << "(" << calc_pairs.at(i).first << "," << calc_pairs.at(i).second << ")";
        }
        std::cout << "}" << std::endl;
    }
};
#endif
