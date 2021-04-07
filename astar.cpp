// This function finds a shortest path from the start node to the goal node.
// The function returns a linked list of every node on the shortest path.

#include <cmath>
#include <iostream>
#include "mapNode.h"
#include "parentNode.h"
#include "astar.h"
#include "map.h"
#include "heap.h"
#include "list.h"

// taulukko suljettua ja avointa listaa varten
anode **map_;

static void alloc_map(int level_height, int level_width)
{
	map_ = (anode **) malloc(level_height * sizeof *map_);

	if (map_ == 0)
	{
		std::cerr << "Memory allocation error" << std::endl;
		exit(EXIT_FAILURE);
	}


	// allocate memory for each row
	for (int i = 0; i < level_height; i++)
	{
		map_[i] = (anode *) malloc(level_width * sizeof(anode));

		if (map_[i] == 0)
		{
			std::cerr << "Memory allocation error" << std::endl;
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < level_width; j++)
		{
			// g > 0: solmu on avoimella listalla
			// -1 solmu _ei_ ole avoimella listalla
			// -2 solmu on suljetulla listalla
			map_[i][j].g = -1; 
			map_[i][j].plink = 0;
		}

	}
}

static void dealloc_map(int level_height)
{
	for (int i = 0; i < level_height; i++)
	{
		free(map_[i]);
	}

	free(map_);
}


List<mapNode> find_path(Map* m)
{
	mapNode start = m->getStart();
	mapNode goal = m->getGoal();
	mapNode current;

	Heap<mapNode> open;
	List<mapNode> closed;

	List<mapNode> neighbours;
	List<mapNode>::iterator nbiter;

	alloc_map(m->gety(), m->getx());

	// Manhattan distance
	start.h = abs(start.x-goal.x) + abs(start.y-goal.y);
	start.f = start.g + start.h;

	open.push(start, start.f);

	// Continue until we find the goal node or the open list is empty
	while ( (open.size() != 0) && ( current != goal) )
	{
		current = open.delMin();

		map_[current.y][current.x].g = -2;

		closed.push_back(current);

		neighbours = m->getNeighbours(current);

		for (nbiter = neighbours.begin(); nbiter != neighbours.end(); nbiter++)
		{
			anode nodeg = map_[(*nbiter).y][(*nbiter).x];

			// Naapuri ei ole vielä avoimella listalla
			if (nodeg.g == -1)
			{
				//std::cout << "naapuri ei ole avoimella listalla. Lisätään" << std::endl;
				mapNode neighbour = *nbiter;

				// Manhattan distance
				neighbour.h = abs(neighbour.x-goal.x) + abs(neighbour.y-goal.y);

				neighbour.g = (current.g + 1); 
				neighbour.f = neighbour.g + neighbour.h;

				// Update the linked list of parents 
				if (current != start)
				{
					neighbour.plink= new parent_t(current.plink, neighbour.x, neighbour.y);
				}
				else
				{
					neighbour.plink= new parent_t(0, neighbour.x, neighbour.y);
				}
				open.push(neighbour, neighbour.f);
				map_[neighbour.y][neighbour.x].g = neighbour.g;
				map_[neighbour.y][neighbour.x].plink = neighbour.plink;


			}
			// The neighbour is already on the open list. Check if this a better path
			// and if necessary, update the parent and the path cost.
			else if ( nodeg.g > (current.g + 1) )
			{
				//std::cout<<"naapuri on avoimella listalla, päivitetään g"<<std::endl;

				mapNode newnode = *nbiter;

				newnode.g = current.g  + 1;
				newnode.h = abs(newnode.x-goal.x) + abs(newnode.y-goal.y);
				newnode.f = newnode.g + newnode.h;
				newnode.plink= map_[newnode.y][newnode.x].plink;
				newnode.plink->parent = current.plink;

				open.delNodeX(*nbiter);
				open.push(newnode, newnode.f);
				map_[newnode.y][newnode.x].g = newnode.g;
			}
			else
			{
				//std::cout << "naapuri oli suljetulla listalla" << std::endl;
			}
		}
	}


	List<mapNode> shortest_path;

	for (parent_t *pnode = current.plink->parent; pnode != 0; pnode = pnode->parent)
	{
		shortest_path.push_back(mapNode(0, 0, 0, 0, pnode->x, pnode->y));
	}

	// Clean up
	while (open.size() != 0)
	{
		mapNode foox = open.delMin();
		delete foox.plink;
	}

	for (List<mapNode>::const_iterator it = closed.begin(); it != closed.end(); it++)
	{
		delete (*it).plink;
	}

	dealloc_map(m->gety());

	return shortest_path;
}
