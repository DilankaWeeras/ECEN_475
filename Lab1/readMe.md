# Kernigan-Lin Algoritym

This is Dilanka's Kernigan Lin Algoritym.

## Usage

```c++
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
```
## Output

This is what the output looks like...
The first line displays the amount of nodes and edges.

The second section shows a graph of the partitions and numbers the amount of cuts remaining.

The third section shows all cut variables and uncut variables.

```html
<pre>Reading input file: case2.txt

Nodes: 12 Edges: 23

Partition 1:	||	Partition 2:
1
			2
3
4
			5
6
			7
			8
			9
10
			11
12

Total Cut Connections: 6

(1) --|-- (5)	(1) ----- (12)	(1) ----- (10)	
(2) ----- (5)	(2) ----- (9)	(2) ----- (11)	
(3) ----- (6)	
(4) ----- (6)	(4) --|-- (11)	(4) ----- (10)	
(5) --|-- (1)	(5) ----- (2)	(5) ----- (7)	(5) --|-- (12)	(5) ----- (9)	
(6) ----- (3)	(6) ----- (4)	(6) --|-- (7)	(6) ----- (10)	
(7) ----- (5)	(7) --|-- (6)	(7) ----- (8)	(7) ----- (11)	(7) --|-- (12)	(7) ----- (8)	
(8) ----- (7)	(8) ----- (7)	(8) ----- (9)	
(9) ----- (2)	(9) ----- (5)	(9) ----- (8)	(9) ----- (11)	(9) --|-- (10)	
(10) ----- (1)	(10) ----- (4)	(10) ----- (6)	(10) --|-- (9)	(10) ----- (12)	
(11) ----- (2)	(11) --|-- (4)	(11) ----- (7)	(11) ----- (9)	
(12) ----- (1)	(12) --|-- (5)	(12) --|-- (7)	(12) ----- (10)	

END
</pre>
```

## To Run
In linux terminal use the shell file run.sh to compile then use the ./run with the input text.

Exp. -- (In Terminal)

bash run.sh
./run input.txt

## Author
Dilanka Weerasinghe - Programming assignment for Texas A&M
ECEN - 475

Please do not copy this program. However it may be used for reference.
