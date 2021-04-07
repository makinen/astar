#ifndef ASTAR_H
#define ASTAR_H

#include "mapNode.h"
#include "parentNode.h"
#include "list.h"
#include "map.h"

// astar k‰ytt‰‰ t‰t‰ struktia kaksiulotteisessa taulukossa kirjanpitoon
// solmun olemassaolosta suljetulla ja avoimella listalla.
struct anode
{
	int g;
	parent_t *plink;
};

List<mapNode> find_path(Map* map);

#endif

