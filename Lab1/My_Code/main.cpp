#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "Graph.h"


int main(int argc, const char *argv[])
{
    try
    {
        ////   INPUT FILE STEP  ////
        if (argc != 2)
        {
            std::cout << "Usage: " << argv[0] << "input filename\n";
            exit(1);
        }
        std::string input_name = argv[1];
        std::ifstream input(input_name);
        std::cout << "Reading input file: " << input_name << std::endl
                  << std::endl;
        if (!input)
        {
            std::cout << "Wrong or nonexisting input file\n";
            exit(1);
        }

        ////    STEP 0          ////
        Graph g1;
        g1.buildGraph(input);
        //g1.printNodes();

        ////    STEP 1          ////
        g1.calculateDAll();
        //g1.toString_Partition_NodesCut();
        //std::cout << g1.carryFinalPartition << std::endl;

        ////    STEP 2          ////
        g1.swappingFunction();

        ////    STEP 3          ////
        while (g1.allFixed() == false)
        {
            g1.calculateDAll();
            g1.iteration++;
            if (g1.allFixed() == true)
            {
                break;
            }
            g1.swappingFunction();
        }
        ////    STEP 4          ////
        
        ////    STEP 5          ////
        std::cout << g1.carryFinalPartition << std::endl;
        std::cout << "END" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}