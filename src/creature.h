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

#ifndef _CREATURE_H
#define _CREATURE_H


#include "globals.h"
#include "coord.h"


class Map;


class Creature {
public:
	Coord coord;

	Creature(Map &_map): map(_map), vel(0, 0) { can_move = True; }
	virtual Boolean do_move() = 0;
	virtual Boolean is_man() const { return False; }
	virtual const char *get_image_name() const = 0;
	ostream &dump(ostream &out) const
		{ out << "(Creature '" << get_image_name() << "')"; }

protected:
	Boolean can_move;
	Direction vel;  // the current movement velocity (L, R, U, D)
	Map &map;

	Boolean can_move_on_map();
	Boolean move_on_map();
};


class Man: public Creature {
public:
	Man(Map &_map): Creature(_map), prev_vel(0, 0) { duration = 0; }
	virtual Boolean do_move();
	virtual Boolean is_man() const { return True; }
	virtual const char *get_image_name() const { return "man"; }

private:
	int duration;
	Direction prev_vel;
};


class Enemy: public Creature {
public:
	Enemy(Map &_map): Creature(_map) {}
	virtual Boolean do_move() = 0;
};


class RoundEnemy: public Enemy {
public:
	RoundEnemy(Map &_map, const Direction &_vel, const int _clockwise):
		Enemy(_map)
		{ vel = _vel; clockwise = _clockwise; }
	virtual Boolean do_move();
	virtual const char *get_image_name() const;

protected:
	int clockwise;

	void rotate_vel(Boolean backward);
};


class RoundEnemy1: public RoundEnemy {
public:
	RoundEnemy1(Map &_map): RoundEnemy(_map, DIR_L, True) {}
};


class RoundEnemy2: public RoundEnemy {
public:
	RoundEnemy2(Map &_map): RoundEnemy(_map, DIR_R, True) {}
};


class RoundEnemy3: public RoundEnemy {
public:
	RoundEnemy3(Map &_map): RoundEnemy(_map, DIR_U, True) {}
};


class RoundEnemy4: public RoundEnemy {
public:
	RoundEnemy4(Map &_map): RoundEnemy(_map, DIR_D, True) {}
};


class RoundEnemy5: public RoundEnemy {
public:
	RoundEnemy5(Map &_map): RoundEnemy(_map, DIR_L, False) {}
};


class RoundEnemy6: public RoundEnemy {
public:
	RoundEnemy6(Map &_map): RoundEnemy(_map, DIR_R, False) {}
};


class RoundEnemy7: public RoundEnemy {
public:
	RoundEnemy7(Map &_map): RoundEnemy(_map, DIR_U, False) {}
};


class RoundEnemy8: public RoundEnemy {
public:
	RoundEnemy8(Map &_map): RoundEnemy(_map, DIR_D, False) {}
};


class LineEnemy: public Enemy {
public:
	LineEnemy(Map &_map, const Direction &_vel): Enemy(_map)
		{ vel = _vel; }
	virtual Boolean do_move();
	virtual const char *get_image_name() const { return "enemy2"; }
};


class LineEnemy1: public LineEnemy {
public:
	LineEnemy1(Map &_map): LineEnemy(_map, DIR_L) {}
};


class LineEnemy2: public LineEnemy {
public:
	LineEnemy2(Map &_map): LineEnemy(_map, DIR_R) {}
};


class LineEnemy3: public LineEnemy {
public:
	LineEnemy3(Map &_map): LineEnemy(_map, DIR_U) {}
};


class LineEnemy4: public LineEnemy {
public:
	LineEnemy4(Map &_map): LineEnemy(_map, DIR_D) {}
};


ostream &operator <<(ostream &out, const Creature &c);


#endif
