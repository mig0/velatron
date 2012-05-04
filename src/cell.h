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

#ifndef _CELL_H
#define _CELL_H


#include "ground.h"
#include "item.h"
#include "creature.h"


enum CellUnitType {
	CELL_INCORRECT = -1,

	/* ground */
	CELL_EMPTY,
	CELL_WALL,
	CELL_HOUSE,

	/* item */
	CELL_DIAMOND,
	CELL_KEY,

	/* creature */
	CELL_MAN,
	CELL_ROUNDENEMY1,
	CELL_ROUNDENEMY2,
	CELL_ROUNDENEMY3,
	CELL_ROUNDENEMY4,
	CELL_ROUNDENEMY5,
	CELL_ROUNDENEMY6,
	CELL_ROUNDENEMY7,
	CELL_ROUNDENEMY8,
	CELL_LINEENEMY1,
	CELL_LINEENEMY2,
	CELL_LINEENEMY3,
	CELL_LINEENEMY4,
	NUM_CELL_TYPES,
};


template <class Unit>
class UnitList {
public:
	UnitList() { head = tail = NULL; count = 0; }

	int add(Unit const *unit) {
		int index = tail? tail->index + 1: 0;
		LinkedUnit *new_linked_unit = new LinkedUnit(unit, index);
		if (head == NULL) {
			head = new_linked_unit;
		} else {
			tail->next = new_linked_unit;
			new_linked_unit->prev = tail;
		}
		tail = new_linked_unit;
if (DEBUG) {
cerr << "added: " << *unit << " " << unit << " to ( ";
for (LinkedUnit *c = head; c; c = c->next) {
cerr << c->unit << " ";
}
cerr << ")" << endl;
}
		count++;
	}

	Unit *get(int n) const {
		validate_index("get", n);
		LinkedUnit *curr = head;
		for (int i = 0; i < n; i++) {
			curr = curr->next;
		}
		return (Unit *)curr->unit;
	}

	Boolean remove(int n) {
		validate_index("remove", n);
		LinkedUnit *curr = head;
		for (int i = 0; i < n; i++) {
			curr = curr->next;
		}
if (DEBUG) {
cerr << "removed: " << *(curr->unit) << " " << curr->unit << " from ( ";
for (LinkedUnit *c = head; c; c = c->next) {
cerr << c->unit << " ";
}
cerr << ")" << endl;
}

		if (curr->prev) curr->prev->next = curr->next;
		else head = curr->next;

		if (curr->next) curr->next->prev = curr->prev;
		else tail = curr->prev;

		delete curr;
		count--;
		// update all index's?
		return True;
	}

	int get_index(Unit *unit) const {
		LinkedUnit *curr = head;
		for (int i = 0; i < count; i++) {
			if (curr->unit == unit)
				return i;
			curr = curr->next;
		}
		error_stream << "LinkedUnit::get_index returned -1 for " << *unit << endl;
		if (head->unit)
			error_stream << "LinkedUnit::get_index #0 is " << *(head->unit) << endl;

		return -1;
	}

	int count;

protected:
	class LinkedUnit {
	public:
		LinkedUnit(Unit const *_unit, int _index)
			{ unit = _unit; index = _index; prev = next = NULL; }
		LinkedUnit *next;
		LinkedUnit *prev;
		Unit const *unit;
		int index;
	};

	void validate_index(const char *id, int n) const {
		if (n < 0 || n >= count) {
			error_stream << "LinkedUnit::" << id << ": Requested unit index " << n << " of total " << count << endl;
			exit(1);
		}
	}

	LinkedUnit *head;
	LinkedUnit *tail;
};


class Cell {
public:
	Cell(Ground *_ground);

	Ground *get_ground() { return ground; }

	int add_item(LyingItem const *item);
	LyingItem *get_item(int n) const;
	Boolean delete_item(int n);
	Boolean delete_item(LyingItem *i)
		{ return delete_item(get_item_index(i)); }
	int get_item_index(LyingItem *i) const;
	int get_item_count() const;

	int add_creature(Creature const *creature);
	Creature *get_creature(int n) const;
	Boolean delete_creature(int n);
	Boolean delete_creature(Creature *c)
		{ return delete_creature(get_creature_index(c)); }
	int get_creature_index(Creature *c) const;
	int get_creature_count() const;

protected:
	Ground *ground;
	UnitList<LyingItem> *item_list;
	UnitList<Creature> *creature_list;
};


#endif
