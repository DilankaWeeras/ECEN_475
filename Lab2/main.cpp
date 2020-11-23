#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "Stockmeyer.h"

int main(int argc, const char *argv[])
{
    try
    {
        //Input file step--
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

        //File completed--

        Stockmeyer s;
        std::cout << "Input List..." << std::endl;
        s.inputList(input);
        std::cout << "Print Nodes..." << std::endl
                  << "-----------------" << std::endl;
        s.printNodesV();
        std::cout << std::endl;
        std::cout << "Calculate Dimensions..." << std::endl
                  << "-----------------" << std::endl;
        std::cout << "Initial Width:\t" << s.calculateHeight(s.head) << std::endl;
        std::cout << "Initial Height:\t" << s.calculateWidth(s.head) << std::endl;
        std::cout << std::endl;
        std::cout << "RotateNodes..." << std::endl
                  << "-----------------" << std::endl;
        s.RotateNodes(s.head);
        std::cout << "Print Best Area..." << std::endl
                  << "-----------------" << std::endl;
        s.printBestArea();

        //!!!UNCOMMENT IF YOU WANT TO SEE ALL THE AREAS CALCULATED!!!
        //s.printNodesTreeCalc();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
