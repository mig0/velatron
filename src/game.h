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

#ifndef _GAME_H
#define _GAME_H

#include "map.h"
#include "creature.h"


class ViewInfo {
public:
	ViewInfo() {}
	void init(int ox, int oy, int nx, int ny, int tx, int ty, int cx, int cy) {
		offset.x    = ox; offset.y    = oy;
		num.x       = nx; num.y       = ny;
		total_num.x  = tx; total_num.y  = ty;
		cell_size.x  = cx; cell_size.y  = cy;
		size.x = cx * nx; size.y = cy * ny;
		end = offset + num;
		max = total_num - num;
	}
	Boolean zoom(Boolean grow) {
		Boolean was_zoomed = False;
		int step = grow? -1: 1;
		Size new_num = num;
		for (new_num.x = num.x + step; ; new_num.x += step) {
			if (new_num.x < 1 || new_num.x > total_num.x) break;
			if (total_num.x / new_num.x * new_num.x == total_num.x) {
				was_zoomed = True;
				break;
			}
		}
		if (!was_zoomed) return False;
		was_zoomed = False;
		for (new_num.y = num.y + step; ; new_num.y += step) {
			if (new_num.y < 1 || new_num.y > total_num.y) break;
			if (total_num.y / new_num.y * new_num.y == total_num.y) {
				was_zoomed = True;
				break;
			}
		}
		if (!was_zoomed) return False;

		num = new_num;
		offset = COORD_ZERO;
		end = offset + num;
		max = total_num - num;
		cell_size.x = size.x / num.x;
		cell_size.y = size.y / num.y;
		return True;
	}
	Coord offset;   // coordinates of the first cell in the view
	Size total_num;  // total number of cells this view works over
	Size num;       // number of cells visible in the view
	Size cell_size;  // size of a single cell in the view (pixels)
	Size size;      // size of the view (pixels)
	Coord end;      // coordinates after the last cell in the view
	Coord max;      // coordinates of the last possible view offset
};


class Game {
public:
	Game();
	virtual ~Game() {}
	int run();

protected:
	void update_screen();
	void normalize_view();
	Boolean move_creatures();
	void add_image(SDL_Rect &rect, const char *image_name, int n);

	Man *man;
	Enemy *enemies[MAX_CREATURE_NUM - 1];
	int num_enemies;
	ViewInfo view_info[2];
	Map map;
	//SDL_Surface *bg_image;
	char *bg_image_name;
};


#endif
