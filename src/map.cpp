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

#include "globals.h"
#include "map.h"
#include "cellfactory.h"


enum MapCellType {
	MAPCELL_GROUND,
	MAPCELL_CREATURE,
	MAPCELL_ITEM,
	MAPCELL_COMPOSITIVE,
};


struct MapCharLegend {
	const char visual_char;
	MapCellType map_cell_type;
	union {
		int sunk;
		GroundType ground_type;
		ItemType item_type;
		CreatureType creature_type;
	};
};


const MapCharLegend map_char_legend[] = {
	{ ' ', MAPCELL_GROUND, GROUND_EMPTY },
	{ 'O', MAPCELL_GROUND, GROUND_WALL },
	{ 'S', MAPCELL_GROUND, GROUND_SAND },
	{ 'H', MAPCELL_GROUND, GROUND_HOUSE },
	{ '&', MAPCELL_ITEM, ITEM_DIAMOND },
	{ 'K', MAPCELL_ITEM, ITEM_KEY },
	{ 'X', MAPCELL_CREATURE, CREATURE_MAN },
	{ '<', MAPCELL_CREATURE, CREATURE_ROUNDENEMY1 },
	{ '>', MAPCELL_CREATURE, CREATURE_ROUNDENEMY2 },
	{ '^', MAPCELL_CREATURE, CREATURE_ROUNDENEMY3 },
	{ 'v', MAPCELL_CREATURE, CREATURE_ROUNDENEMY4 },
	{ '{', MAPCELL_CREATURE, CREATURE_ROUNDENEMY5 },
	{ '}', MAPCELL_CREATURE, CREATURE_ROUNDENEMY6 },
	{ '~', MAPCELL_CREATURE, CREATURE_ROUNDENEMY7 },
	{ 'V', MAPCELL_CREATURE, CREATURE_ROUNDENEMY8 },
	{ '[', MAPCELL_CREATURE, CREATURE_LINEENEMY1 },
	{ ']', MAPCELL_CREATURE, CREATURE_LINEENEMY2 },
	{ '|', MAPCELL_CREATURE, CREATURE_LINEENEMY3 },
	{ '!', MAPCELL_CREATURE, CREATURE_LINEENEMY4 },
	{ '*', MAPCELL_COMPOSITIVE, 0 },
	{ '\0', MAPCELL_GROUND, 0 },
};


Map::Map(const char *visual_cell_chars, int _num_y, int _num_x) {
	num_x = _num_x;
	num_y = _num_y;
	num_creatures = 0;

	cell_table = new Cell **[num_y];
	for (int y = 0; y < num_y; y++) {
		cell_table[y] = new Cell *[num_x];
		for (int x = 0; x < num_x; x++) {
			char ch = visual_cell_chars[y * num_x + x];
			int t;
			for (t = 0; map_char_legend[t].visual_char != '\0'; t++) {
				if (map_char_legend[t].visual_char == ch) break;
			}
			if (t == sizeof(map_char_legend)) {
				error_stream << "Incorrect visual map, x = " << x <<
					", y = " << y << ", char '" << ch << "'" << endl;
				exit(-1);
			}

			GroundType ground_type = GROUND_EMPTY;
			ItemType item_type = ITEM_NONE;
			CreatureType creature_type = CREATURE_NONE;

			MapCellType map_cell_type = map_char_legend[t].map_cell_type;
			if (map_cell_type == MAPCELL_GROUND) {
				ground_type = map_char_legend[t].ground_type;
			}
			if (map_cell_type == MAPCELL_ITEM) {
				item_type = map_char_legend[t].item_type;
			}
			if (map_cell_type == MAPCELL_CREATURE) {
				creature_type = map_char_legend[t].creature_type;
			}

			Cell *cell = CellFactory::create_cell(*this, ground_type, item_type, creature_type);
			cell_table[y][x] = cell;

			if (creature_type != CREATURE_NONE) {
				if (num_creatures >= MAX_CREATURE_NUM) {
					error_stream << "Sorry, maximal number of creature cells "
						"in the map exceeded" << endl;
					exit(1);
				}
				creature_places[num_creatures].coord.x = x;
				creature_places[num_creatures].coord.y = y;
				creature_places[num_creatures].creature = cell->get_creature(0);
				num_creatures++;
			}
		}
	}
}


int Map::is_cell_coord_valid(const Coord &coord) const {
	return coord.y >= 0 && coord.x >= 0 && coord.x < num_x && coord.y < num_y;
}


Cell *Map::get_cell(const Coord &coord) const {
	if (!is_cell_coord_valid(coord))
	{
		//return NULL;
		error_stream << "Map::get_cell: requested cell with invalid coord " << coord << endl;
		exit(1);
	}
	return cell_table[coord.y][coord.x];
}

