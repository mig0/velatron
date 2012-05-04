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
#include "coord.h"
#include <stdlib.h>

const Direction DIR_L(-1,  0);
const Direction DIR_R(+1,  0);
const Direction DIR_U( 0, -1);
const Direction DIR_D( 0, +1);
const Direction DIR_NONE(0, 0);
const Size SIZE_ZERO(0, 0);
const Coord COORD_ZERO(0, 0);

ostream &operator <<(ostream &out, const Coord &coord) {
	return out << "(" << coord.x << ", " << coord.y << ")";
}

Direction::Direction(int _x, int _y): Coord(_x, _y) {
	if (_x * _x + _y * _y > 1) {
		cerr << "Fatal: invalid direction " << *this << endl;
		exit(-1);
	}
}

Size::Size(int _x, int _y): Coord(_x, _y) {
	if (_x < 0 || _y < 0) {
		cerr << "Fatal: invalid size " << *this << endl;
		exit(-1);
	}
}

