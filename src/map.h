/*
** VelaTron, Copyright (C) 2001-2012 Mikhael Goikhman, migo@freeshell.org
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MAP_H
#define _MAP_H


#include "coord.h"
#include "cell.h"


struct CreaturePlace {
	Coord coord;
	Creature *creature;
};


#define MAX_CREATURE_NUM 200


class Map {
public:
//	Map() { num_x = num_y = 0; cell_table = new (CellType *)[0]; }
	Map(const char *visual_cells, int num_y, int num_x);
	Map(const char *filename);
	int is_cell_coord_valid(const Coord &coord) const;
	Cell *get_cell(const Coord &coord) const;

	CreaturePlace creature_places[MAX_CREATURE_NUM];
	int num_creatures;

protected:
	int num_x;
	int num_y;
	Cell ***cell_table;
};


#endif
