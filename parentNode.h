// Tällaisista solmuista astar-algoritmi muodostaa linkitetyn
// listan, jota läpikäymällä takaperin saadaan lopullinen lyhin reitti
#ifndef PARENT_H
#define PARENT_H

#include "mapNode.h"

struct parent_t 
{
	parent_t *parent;
	int x;
	int y;

	parent_t(): parent(0), x(0), y(0) {}
	parent_t(parent_t *pr, int xx, int yy): parent(pr), x(xx), y(yy) {}

	parent_t& operator=(const parent_t& L)
	{
		parent = L.parent;
		x = L.x;
		y = L.y;

		return *this;
	}

	bool operator!=(const parent_t &n)
	{
		if ( (n.x != x) && (n.y != y) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(const parent_t &foox)
	{
		if ( (foox.x == x) && (foox.y == y) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
			
};

#endif
