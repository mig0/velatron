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

#include "cellfactory.h"
#include <stdlib.h>

Cell *CellFactory::create_cell(Map &map, GroundType gtype, ItemType itype, CreatureType ctype)
{
	/* ground in the cell */
	Ground *ground = NULL;
	if (gtype == GROUND_EMPTY)
		ground = new EmptyGround();
	else if (gtype == GROUND_WALL)
		ground = new WallGround();
	else if (gtype == GROUND_SAND)
		ground = new SandGround();
	else if (gtype == GROUND_HOUSE)
		ground = new HouseGround();

	if (!ground) {
		error_stream << "No valid ground in Cell creation" << endl;
		exit(1);
	}
	Cell *cell = new Cell(ground);

	/* items in the cell */
	LyingItem *item = NULL;

	switch (itype) {
	case ITEM_DIAMOND:
		item = new LyingDiamond;
		break;
	case ITEM_KEY:
		item = new LyingKey;
		break;
	}
	if (item)
		cell->add_item(item);

	/* creatures in the cell */
	Creature *creature = NULL;

	switch (ctype) {
	case CREATURE_MAN:
		creature = new Man(map);
		break;
	case CREATURE_ROUNDENEMY1:
		creature = new RoundEnemy1(map);
		break;
	case CREATURE_ROUNDENEMY2:
		creature = new RoundEnemy2(map);
		break;
	case CREATURE_ROUNDENEMY3:
		creature = new RoundEnemy3(map);
		break;
	case CREATURE_ROUNDENEMY4:
		creature = new RoundEnemy4(map);
		break;
	case CREATURE_ROUNDENEMY5:
		creature = new RoundEnemy5(map);
		break;
	case CREATURE_ROUNDENEMY6:
		creature = new RoundEnemy6(map);
		break;
	case CREATURE_ROUNDENEMY7:
		creature = new RoundEnemy7(map);
		break;
	case CREATURE_ROUNDENEMY8:
		creature = new RoundEnemy8(map);
		break;
	case CREATURE_LINEENEMY1:
		creature = new LineEnemy1(map);
		break;
	case CREATURE_LINEENEMY2:
		creature = new LineEnemy2(map);
		break;
	case CREATURE_LINEENEMY3:
		creature = new LineEnemy3(map);
		break;
	case CREATURE_LINEENEMY4:
		creature = new LineEnemy4(map);
		break;
	}
	if (creature)
		cell->add_creature(creature);

	return cell;
}
