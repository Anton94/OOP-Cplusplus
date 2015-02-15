/*



Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/SD%20semester%20projects%20mostly




*/



#include <iostream>
#include <fstream>
#include "../Vector/Vector.h"
#include "Board.h"
#include "Graph.h"
#include "String.h"
#include "CompressString.h"
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
			for (int fileNameIndex = 1; fileNameIndex < argc - 1; ++fileNameIndex)
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
			

			std::cout << "Path for whole leves:\n" << path << std::endl;

			std::cout << "\n\n";
			std::cout << "COMPRESED path for whole leves:\n" << CompressString::basicCompress(path) << std::endl;
			
			
		}
		catch (const char * str)
		{
			std::cerr << "Error: " << str << "\n";
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "Memory allocation rrror: " << e.what() << "\n";
		}
		catch (const std::out_of_range& oor) {
			std::cerr << "Out of Range error: " << oor.what() << '\n';
		}
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}





// TEST for basic compression.
//String str = "aaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcddeefggerfddff";
//
//std::cout << "String: " << str << std::endl;
//
//std::cout << "Compressed one: " << CompressString::basicCompress(str) << std::endl;
// END TEST


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