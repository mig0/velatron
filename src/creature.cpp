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

#include "creature.h"
#include "map.h"

Boolean Creature::can_move_on_map() {
	Coord new_coord = coord + vel;
	return
		can_move &&
		map.is_cell_coord_valid(new_coord) &&
		map.get_cell(new_coord)->get_ground()->can_enter(*this, vel)
		? True : False;
}

Boolean Creature::move_on_map() {
	if (vel == DIR_NONE)
		return False;

	Coord new_coord = coord + vel;
	Cell &old_cell = *(map.get_cell(coord));
	old_cell.delete_creature(this);
	Cell &new_cell = *(map.get_cell(new_coord));
	new_cell.add_creature(this);

	if (DEBUG) error_stream << *this << " moved " << coord << " -> " << new_coord << endl;
	coord = new_coord;
	return True;
}

Boolean Man::do_move() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				vel.x = -1; break;
			case SDLK_RIGHT:
				vel.x = +1; break;
			case SDLK_UP:
				vel.y = -1; break;
			case SDLK_DOWN:
				vel.y = +1; break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_q:
			case '\e':
				event.type = SDL_QUIT;
				SDL_PushEvent(&event);
				goto CONT;
			case SDLK_LEFT:
				if (vel.x < 0) vel.x = 0; break;
			case SDLK_RIGHT:
				if (vel.x > 0) vel.x = 0; break;
			case SDLK_UP:
				if (vel.y < 0) vel.y = 0; break;
			case SDLK_DOWN:
				if (vel.y > 0) vel.y = 0; break;
			}
			break;

		default:
			SDL_PushEvent(&event);
			goto CONT;
		} // switch (event.type)
	} // while (SDL_PollEvent)

CONT:
	if (vel == prev_vel) duration++;
	else duration = 0;
	prev_vel = vel;

	if (vel != DIR_NONE && duration != 1) {
		if (can_move_on_map())
			return move_on_map();
	}

	return False;
}

const char *RoundEnemy::get_image_name() const {
	static char image_name[] = "scissors0xx\0";
	image_name[ 8] = clockwise ? '1' : '2';
	image_name[ 9] = vel == DIR_U || vel == (clockwise ? DIR_L : DIR_R) ? 'u' : 'd';
	image_name[10] = vel == DIR_L || vel == (clockwise ? DIR_D : DIR_U) ? 'l' : 'r';
	return (const char *)image_name;
}

void RoundEnemy::rotate_vel(Boolean backward = False) {
	int sign1 = backward ? -1 : +1;
	int sign2 = clockwise ? +1 : -1;
	int curr_y = vel.y;
	vel.y = sign1 * sign2 * -vel.x;
	vel.x = sign1 * sign2 * curr_y;
}

Boolean RoundEnemy::do_move() {
	rotate_vel(True);

	int tries = 4;
	do {
		if (can_move_on_map())
			return move_on_map();
		rotate_vel();
	} while (--tries);

	rotate_vel();
	return False;
}

Boolean LineEnemy::do_move() {
	int tries = 2;
	do {
		if (can_move_on_map())
			return move_on_map();
		vel = DIR_NONE - vel;
	} while (--tries);

	return False;
}

ostream &operator <<(ostream &out, const Creature &c) {
	c.dump(out);
	return out;
}
