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

#ifndef _CELLTYPES_H
#define _CELLTYPES_H

enum GroundType {
	GROUND_NONE,
	GROUND_EMPTY,
	GROUND_WALL,
	GROUND_SAND,
	GROUND_HOUSE,
};


enum ItemType {
	ITEM_NONE,
	ITEM_DIAMOND,
	ITEM_KEY,
};


enum CreatureType {
	CREATURE_NONE,
	CREATURE_MAN,
	CREATURE_ROUNDENEMY1,
	CREATURE_ROUNDENEMY2,
	CREATURE_ROUNDENEMY3,
	CREATURE_ROUNDENEMY4,
	CREATURE_ROUNDENEMY5,
	CREATURE_ROUNDENEMY6,
	CREATURE_ROUNDENEMY7,
	CREATURE_ROUNDENEMY8,
	CREATURE_LINEENEMY1,
	CREATURE_LINEENEMY2,
	CREATURE_LINEENEMY3,
	CREATURE_LINEENEMY4,
};

#endif /* _CELLTYPES_H */
