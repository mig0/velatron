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

#ifndef _CELLFACTORY_H
#define _CELLFACTORY_H


#include "globals.h"
#include "image.h"
#include "celltypes.h"
#include "cell.h"


class CellImage {
public:
	CellImage(const char *image_name) {
		image = load_cell_image(image_name);
	}
	SDL_Surface *get_image() { return image; }

private:
	SDL_Surface *image;
};


class Cell;


class CellFactory {
public:
	static Cell *create_cell(Map &map, GroundType gtype, ItemType itype, CreatureType ctype);
};


#endif
