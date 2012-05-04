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

#ifndef _COORD_H
#define _COORD_H


class Coord;
#define define_operators(Class) \
	int operator ==(const Coord &c2) const          	\
		{ return x == c2.x && y == c2.y; }              \
	int operator !=(const Coord &c2) const          	\
		{ return x != c2.x || y != c2.y; }              \
	Class &operator =(const Coord &c2)                      \
		{ x = c2.x; y = c2.y; }                         \
	Class &operator +(const Coord &c2) const        	\
		{ return *(new Class(x + c2.x, y + c2.y)); }    \
	Class &operator -(const Coord &c2) const        	\
		{ return *(new Class(x - c2.x, y - c2.y)); }    \
	Class &operator +=(const Coord &c2)             	\
		{ x += c2.x; y += c2.y; return *this; }         \
	Class &operator -=(const Coord &c2)             	\
		{ x -= c2.x; y -= c2.y; return *this; }         \


class Coord {
public:
	Coord() { x = y = 0; }
	Coord(const Coord &c) { x = c.x; y = c.y; }
	Coord(int _x, int _y) { x = _x; y = _y; }

	define_operators(Coord)

	int x;
	int y;
};

/*
#define Direction Coord
#define Size Coord
*/

extern ostream &operator <<(ostream &out, const Coord &coord);

class Direction: public Coord {
public:
	Direction(): Coord() {}
	Direction(int _x, int _y);

	define_operators(Direction)
};

class Size: public Coord {
public:
	Size(): Coord() {}
	Size(int _x, int _y);

	define_operators(Size)
};

extern const Direction DIR_U;
extern const Direction DIR_D;
extern const Direction DIR_L;
extern const Direction DIR_R;
extern const Direction DIR_NONE;
extern const Size SIZE_ZERO;
extern const Coord COORD_ZERO;


#endif
