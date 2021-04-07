#ifndef MAP_H
#define MAP_H

#include "mapNode.h"
#include "list.h"
#include <string>

class Map
{
	private:
		char **map_;
		std::size_t level_width;
		std::size_t level_height;
		mapNode start;
		mapNode goal;
		List<mapNode> neighbours;

		void alloc_map();
		void dealloc_map();

	public:
		explicit Map():map_(0), level_width(0), level_height(0) {}
		int getx() const { return level_width; }
		int gety() const { return level_height; }
		void loadmap(const std::string& mapfile);
		mapNode& getStart();
		mapNode& getGoal();
		List<mapNode>& getNeighbours(const mapNode& current);
		void markPath(const List<mapNode> &path);
		void print();
		~Map();
	
};

#endif
