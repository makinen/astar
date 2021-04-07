#include <iostream>
#include <memory>
#include "list.h"
#include "map.h"
#include "mapNode.h"
#include "astar.h"

int main(int argc, char **argv)
{
	List<mapNode> shortest_path;
	Map *mappi;

	if (argc < 2)
	{
		std::cerr << "Please give the name of map file" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	mappi = new Map;

	if (mappi == 0)
	{
		std::cerr << "memory allocation error" << std::endl;
		exit(EXIT_FAILURE);
	}

	mappi->loadmap(std::string(argv[1]));
	
	shortest_path = find_path(mappi);

	mappi->markPath(shortest_path);
	
	mappi->print();

	delete mappi;

	exit(EXIT_SUCCESS);
}
