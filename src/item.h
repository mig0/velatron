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

#ifndef _ITEM_H
#define _ITEM_H


#include "globals.h"
#include "celltypes.h"
#include "coord.h"


class LyingItem {
public:
	LyingItem() {}
	virtual Boolean can_be_crossed_by(CreatureType ctype) const
		{ return False; }
	virtual Boolean can_be_taken_by(CreatureType ctype) const
		{ return False; }
	virtual const char *get_image_name() const = 0;
	ostream &dump(ostream &out) const
		{ out << "(Item '" << get_image_name() << "')"; }
};


class LyingKey: public LyingItem {
public:
	LyingKey() {}
	virtual Boolean can_be_crossed_by(CreatureType ctype) const
		{ return True; }
	virtual Boolean can_be_taken_by(CreatureType ctype) const
		{ return ctype == CREATURE_MAN? True: False; }
	virtual const char *get_image_name() const { return "key"; }
};


class LyingDiamond: public LyingItem {
public:
	LyingDiamond() {}
	virtual Boolean can_be_crossed_by(CreatureType ctype) const
		{ return ctype == CREATURE_MAN? True: False; }
	virtual Boolean can_be_taken_by(CreatureType ctype) const
		{ return True; }
	virtual const char *get_image_name() const { return "diamond"; }
};


ostream &operator <<(ostream &out, const LyingItem &i);


#endif
