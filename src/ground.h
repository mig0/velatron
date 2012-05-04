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

#ifndef _GROUND_H
#define _GROUND_H


#include "globals.h"
#include "celltypes.h"
#include "creature.h"
#include "coord.h"


class Creature;


enum GroundEnterAction {
	GEA_NONE,
	GEA_TRANSFORM,
	GEA_LOSE_GAME,
	GEA_FINISH_GAME,
};


class Ground {
public:
	virtual Boolean can_enter(const Creature &creature, const Coord &direction)
		= 0;
	virtual Boolean can_leave(const Creature &creature, const Coord &direction)
		= 0;
	virtual GroundEnterAction enter(const Creature &creature, const Coord &direction)
		= 0;
	virtual GroundType get_transform_ground_type()
		{ return GROUND_NONE; }
	virtual const char *get_image_name() const
		= 0;
};


class EmptyGround: public Ground {
public:
	virtual Boolean can_enter(const Creature &creature, const Coord &direction)
		{ return True; }
	virtual Boolean can_leave(const Creature &creature, const Coord &direction)
		{ return True; }
	virtual GroundEnterAction enter(const Creature &creature, const Coord &direction)
		{ return GEA_NONE; }
	virtual const char *get_image_name() const
		{ return "empty"; }
};


class WallGround: public Ground {
public:
	virtual Boolean can_enter(const Creature &creature, const Coord &direction)
		{ return False; }
	virtual Boolean can_leave(const Creature &creature, const Coord &direction)
		{ return False; }
	virtual GroundEnterAction enter(const Creature &creature, const Coord &direction)
		{ return GEA_NONE; }
	virtual const char *get_image_name() const
		{ return "wall"; }
};


class SandGround: public Ground {
public:
	virtual Boolean can_enter(const Creature &creature, const Coord &direction)
		{ return True; }
	virtual Boolean can_leave(const Creature &creature, const Coord &direction)
		{ return False; }
	virtual GroundEnterAction enter(const Creature &creature, const Coord &direction)
		{ return GEA_TRANSFORM; }
	virtual GroundType get_transform_ground_type()
		{ return GROUND_EMPTY; }
	virtual const char *get_image_name() const
		{ return "sand"; }
};


class HouseGround: public Ground {
public:
	virtual Boolean can_enter(const Creature &creature, const Coord &direction)
		{ return creature.is_man()? True: False; }
	virtual Boolean can_leave(const Creature &creature, const Coord &direction)
		{ return False; }
	virtual GroundEnterAction enter(const Creature &creature, const Coord &direction)
		{ return GEA_NONE; }
	virtual const char *get_image_name() const
		{ return "house"; }
};


#endif
