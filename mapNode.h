#ifndef MAPNODE_H
#define MAPNODE_H

#include "parentNode.h"

struct mapNode
{
	parent_t *plink;
	int f;
	int g;
	int h;
	int x;
	int y;

	mapNode(): plink(0), f(0), g(0), h(0), x(0), y(0) {}
	mapNode(parent_t *pr, int f, int g, int h, int x, int y): 
		plink(pr), f(f), g(g), h(h), x(x), y(y) {}

	mapNode& operator=(const mapNode& L)
	{
		plink = L.plink;
		f = L.f;
		g = L.g;
		h = L.h;
		x = L.x;
		y = L.y;

		return *this;
	}

	bool operator!=(const mapNode &n)
	{
		if ( (n.x != x) || (n.y != y) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(const mapNode &foox)
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
