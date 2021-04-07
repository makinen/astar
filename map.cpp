#include "map.h"
#include "list.h"
#include "mapNode.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

void Map::alloc_map()
{
	map_ = (char **) malloc(level_height * sizeof *map_);

	if (map_ == 0)
	{
		std::cerr << "Not enough memory" << std::endl;
		exit(EXIT_FAILURE);
	}


	// allocate memory for each row
	for (unsigned int i = 0; i < level_height; i++)
	{
		map_[i] = (char *) malloc(level_width);

		if (map_[i] == 0)
		{
			std::cerr << "Not enough memory" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Map::dealloc_map()
{
	for (unsigned int i = 0; i < level_height; i++)
	{
		free(map_[i]);
	}

	free(map_);
}

void Map::loadmap(const string& mapfile)
{
	std::string line;
	std::string keyword;
	bool end = false;
	unsigned int linecount = 0;
	
	std::fstream infile(mapfile.c_str());

	if (!infile)
	{
		std::cerr << "Map file was not found" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (getline(infile, line, '\n'))
	{
		if (end == false)
		{
			std::istringstream sstr(line);
			sstr >> keyword;

			if (keyword == "level_size")
			{
				sstr >> level_width;
				sstr >> level_height; 
				// now we should know the size of map and we can alloc memory for it
				alloc_map();
			}

			else if (keyword == "end")
			{
				end = true;
			}

		}
		else
		{
			if ( line.size() != level_width)
			{
				std::cerr << "The length of the line conflicts with the given level_size" << std::endl;
				exit(EXIT_FAILURE);
			}

			for (unsigned int j = 0; j < level_width; j++)
			{
				// the start node
				if (line[j] == 'A')
				{
					start.x = j;
					start.y = linecount;
					start.plink = new parent_t(0, start.x, start.y);

				}

				// the goal node
				if (line[j] == 'B')
				{
					goal.x = j;
					goal.y = linecount;
				}

				map_[linecount][j] = line[j];
			}

			linecount++;
		}
	}

	infile.close();

	if (end == false)
	{
		std::cerr << "Map file error" << std::endl;
		exit(EXIT_FAILURE);
	}
}

mapNode& Map::getStart()
{
	return start;
}

mapNode& Map::getGoal()
{
	return goal;
}


// the function returns a list of adjacent non-block cells
List<mapNode>& Map::getNeighbours(const mapNode& current)
{
	neighbours.clear();
	
	if (map_[current.y][current.x-1] != '#')
	{
		neighbours.push_back(mapNode( 0, 0, 0, 0, current.x-1, current.y));	
	}
	if (map_[current.y][current.x+1] != '#')
	{
		neighbours.push_back(mapNode( 0, 0, 0, 0, current.x+1, current.y));	
	}
	if (map_[current.y-1][current.x] != '#')
	{
		neighbours.push_back(mapNode( 0, 0, 0, 0, current.x, current.y-1));	
	}
	if (map_[current.y+1][current.x] != '#')
	{
		neighbours.push_back(mapNode( 0, 0, 0, 0, current.x, current.y+1));	
	}

	return neighbours;

}

void Map::print()
{
	for (unsigned int i = 0; i < level_height; i++)
	{
		for (unsigned int j = 0; j < level_width; j++)
			{
				std::cout << map_[i][j];
			}
		std::cout << std::endl;
	}
}

void Map::markPath(const List<mapNode>& path)
{
	List<mapNode>::const_iterator it1 = path.begin();
	List<mapNode>::const_iterator it2 = path.end();

	for (;it1 != it2; it1++)
	{
		map_[(*it1).y][(*it1).x] = '*';
	}
}

Map::~Map()
{
	dealloc_map();
}
