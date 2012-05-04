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

#include "cell.h"

Cell::Cell(Ground *_ground) {
	ground = _ground;
	item_list = new UnitList<LyingItem>;
	creature_list = new UnitList<Creature>;
}

int Cell::add_item(LyingItem const *item) {
	return item_list->add(item);
}

LyingItem *Cell::get_item(int n) const {
	return item_list->get(n);
}

Boolean Cell::delete_item(int n) {
	return item_list->remove(n);
}

int Cell::get_item_index(LyingItem *i) const {
	return item_list->get_index(i);
}

int Cell::get_item_count() const {
	return item_list->count;
}

int Cell::add_creature(Creature const *creature) {
	return creature_list->add(creature);
}

Creature *Cell::get_creature(int n) const {
	return creature_list->get(n);
}

Boolean Cell::delete_creature(int n) {
	return creature_list->remove(n);
}

int Cell::get_creature_index(Creature *c) const {
	return creature_list->get_index(c);
}

int Cell::get_creature_count() const {
	return creature_list->count;
}

