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

#ifndef _GLOBALS_H
#define _GLOBALS_H

// Globals

#ifndef PACKAGE
#define PACKAGE "VelaTron"
#endif

#define NUM_CELLS_X 48
#define NUM_CELLS_Y 48

#define MIN_TICK_INTERVAL 6
#define DEF_TICK_INTERVAL 96
#define MAX_TICK_INTERVAL 768
#define IMAGES_DIR "./images"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

extern SDL_Surface *screen;
extern SDL_Surface *view_win[2];
extern SDL_Rect view_rect[2];

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define error_stream cerr

extern ostream &operator <<(ostream &out, const SDL_Rect &rect);

enum Boolean {
	False = 0,
	True = 1,
	Err = 0,
	Ok = 1,
};

#define DEBUG 0

#endif
