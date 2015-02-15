/*



Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/SD%20semester%20projects%20mostly




*/



#include <iostream>
#include <fstream>
#include "../Vector/Vector.h"
#include "Board.h"
#include "Graph.h"
#include "String.h"
#include "Utility.h"

int main(int argc, char* argv[])
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{		
		try
		{
			Board board;
			// Goes through every file, given by the console.
			for (int fileNameIndex = 1; fileNameIndex < argc; ++fileNameIndex)
			{
				std::ifstream in(argv[fileNameIndex]);
				if (!in)
					throw "Can`t open the file for the level!";
				
				board.deserialize(in);
				board.printBoard(std::cout);
				board.printDoorKeyPairs(std::cout);

				board.findPathFromStartToEnd();

				std::cout << "\n\n";
			}

			String path = board.generateTheWholePath();
			

			std::cout << "Path for whole leves: " << path << std::endl;


			



		}
		catch (const char * str)
		{
			std::cerr << "Error: " << str << "\n";
		}
		catch (std::bad_alloc e)
		{
			std::cerr << "Error: " << e.what() << "\n";
		}
		// catch outside of the bounds array...
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}




/// TESTS THE GRAPH WITH 2 PATCHS TO THE END CELL

/*Cell cell1, cell2, cell3, cell4, cell5;
cell1.setSymbol('*');
cell2.setSymbol('!');
cell3.setSymbol('1');
cell4.setSymbol('2');
cell5.setSymbol('3');

Graph graph;
graph.insertEdge(&cell1, &cell5, DLList<Cell*>());

graph.insertEdge(&cell2, &cell1, DLList<Cell*>());
graph.insertEdge(&cell2, &cell4, DLList<Cell*>());

graph.insertEdge(&cell4, &cell5, DLList<Cell*>());

graph.insertEdge(&cell5, &cell3, DLList<Cell*>());

graph.print(std::cout);

DLList<DLList<Cell*>> allPaths = graph.AllPathsBetweenCells(&cell2, &cell3);

allPaths.getSize();

for (DLList<DLList<Cell*>>::Iterator iter = allPaths.begin(); iter != allPaths.end(); ++iter)
{
std::cout << (*iter).peek_front()->getSymbol() << " to " << (*iter).peek_back()->getSymbol() << " :";

for (DLList<Cell*>::Iterator path = (*iter).begin(); path != (*iter).end(); ++path)
{
std::cout << (*path)->getSymbol() << " ";
}

std::cout << "\n";
}*/