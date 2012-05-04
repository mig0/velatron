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
#include "game.h"
#include "image.h"
#include "fullscreen.h"
#include <SDL/SDL_gfxPrimitives.h>  // for rectangle

Size NORM_CELL_SIZE;
Size MINI_CELL_SIZE;

static int tick_interval = DEF_TICK_INTERVAL;

static const char *visual_maps[] = {
	"                                                "
	"S  OOOOOO|OOOO!OOOOOO] [OOOOOOOOOO][OOOOOOOOO[]O"
	"   OOOOOOOOOOO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
	"                                                "
	"  > >                                           "
	"   O                                            "
	"  > >                                           "
	"       &&&&&&&&&&&&&&&&&&&&&&&&&&&&      >      "
	"  < <                                    O      "
	"   O         SSSSSSSSSSSSSSSSS                  "
	"  < <        SSSSSSSSSSSSSSSSS                  "
	"             SSSSSSSSSSSSSSSSS                  "
	"  } }                                        O  "
	"   O                                         <  "
	"  } }   OOOOOOOOOOOOOOOOOOOOOOOOOO              "
	"                                                "
	"  { {        SSSSSSSSSSSSSSSSS           Ov     "
	"   O         SSSSSSSSSSSSSSSSS                  "
	"  { {        SSSSSSSSSSSSSSSSS         X        "
	"                                    >           "
	"    O   O OOOOO OOOOO OOOOO OOOOO OOOOO    ^O   "
	"    OOOOO OOOOO O   O O   O O         O         "
	"    OOOOO OOOOO O   O OOOOO OOOOO OOOOO         "
	"    OOOOO O   O O   O O   O O         O         "
	"    O   O O   O OOOOO OOOOO OOOOO OOOOO  O      "
	"                                         }      "
	"                                                "
	"                                            {   "
	"      &&&&&&&&&&&&&&& &&&&&&&&&&&&&         O   "
	"      &&&&&&&&&&&&&&& &&&&&&&&&&&&&             "
	"      &&&&&&&K&&&&&&& &&&&&&H&&&&&&             "
	"      &&&&&&&&&&&&&&& &&&&&&&&&&&&&             "
	"      &&&&&&&&&&&&&&& &&&&&&&&&&&&&     VO      "
	"                                                "
	"                                                "
	"                                                "
	"                      K                     O~  "
	"   OOOOOOOOOOOOO OOOOOOOOOOOOOOOOOOOOOOOOOO     "
	"          O{     KO                             "
	"          O       O     >                       "
	"   OOOOOOOOOOOOOOOOOOO OOOOOOOOOOO OOOOOOOOOO   "
	"   O                 O OOOOOOOOOOO OOOOOOOOOO   "
	"   O  K      ~       O O                        "
	"   O    OO       SS  O O        H               "
	"   O    OO    [  SS  O OOOOOO      OOOOOOOOOO   "
	"     |  OO  H    SS  O O                        "
	"   O                 O O[       O   ]           "
	"   OOOOOOOOOOOOOOOOOOO OOOOOOOOOOO OOOOOOOOOO   "
	,
	"                                                "
	"S  OOOOOO OOOO OOOOOO] [OOOOOOOOOO  OOOOOOOOO  O"
	"   OOOOOOOOOOO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
	"                                                "
	"                  X                             "
	"                >                               "
	"                O                               "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
	"                                                "
};

// ---------------------------------------------------------------------------

static Uint32 next_time;

Uint32 time_left(void) {
	Uint32 now = SDL_GetTicks();
	if (next_time <= now) {
		next_time = now;
		return 0;
	} else {
		return next_time - now;
	}
}


Game::Game(): map(visual_maps[0], NUM_CELLS_Y, NUM_CELLS_X) {
	man = NULL;
	num_enemies = 0;

	for (int i = 0; i < map.num_creatures; i++) {
		CreaturePlace &creature_place = map.creature_places[i];
		Coord &coord = creature_place.coord;
		if (creature_place.creature->is_man()) {
			if (man) {
				error_stream << "Incorrect map: more than one man cell" << endl;
				exit(1);
			} else {
				man = (Man *)creature_place.creature;
				man->coord = coord;
			}
		} else {
			(enemies[num_enemies++] = (Enemy *)creature_place.creature)->coord = coord;
		}
	}
	if (!man) {
		error_stream << "Incorrect map: no mandatory man cell" << endl;
		exit(1);
	}
	//bg_image = load_cell_image("background");
	bg_image_name = (char *)"background";

	NORM_CELL_SIZE = *new Size(32, 32);
	MINI_CELL_SIZE = *new Size( 3,  3);

	view_info[0].init(0, 0, 448 / NORM_CELL_SIZE.x, 448 / NORM_CELL_SIZE.y,
		NUM_CELLS_X, NUM_CELLS_Y, NORM_CELL_SIZE.x, NORM_CELL_SIZE.y);
	view_info[1].init(0, 0, 144 / MINI_CELL_SIZE.x, 144 / MINI_CELL_SIZE.y,
		NUM_CELLS_X, NUM_CELLS_Y, MINI_CELL_SIZE.x, MINI_CELL_SIZE.y);
}


void Game::add_image(SDL_Rect &rect, const char *image_name, int n) {
	SDL_Surface *win = view_win[n];
	SDL_Surface *image = load_cell_image(image_name, (Boolean)n);
	SDL_BlitSurface(image, NULL, win, &rect);
}


void Game::update_screen() {
	for (int n = 0; n < 2; n++) {
		ViewInfo &view = view_info[n];
		SDL_Rect rect = { 0, 0, view.cell_size.x, view.cell_size.y };
		Coord c;

		for (c.y = 0; c.y < NUM_CELLS_Y; c.y++) {
			for (c.x = 0; c.x < NUM_CELLS_X; c.x++) {
				if (c.x < view.offset.x || c.y < view.offset.y
					|| c.x >= view.end.x || c.y >= view.end.y)
					continue;
//error_stream << "[" << n << "] view.offset=" << view.offset << ", view.end=" << view.end << ", c=" << c << endl;
				Coord &c0 = c - view.offset;
				rect.x = c0.x * view.cell_size.x;
				rect.y = c0.y * view.cell_size.y;

				add_image(rect, bg_image_name, n);

				Cell *cell = map.get_cell(c);
				add_image(rect, cell->get_ground()->get_image_name(), n);
				int i;
				for (i = 0; i < cell->get_item_count(); i++) {
					add_image(rect, cell->get_item(i)->get_image_name(), n);
				}
				for (i = 0; i < cell->get_creature_count(); i++) {
					add_image(rect, cell->get_creature(i)->get_image_name(), n);
				}
			}
		}
		// draw main area border in the mini view
		if (n == 1) {
			ViewInfo &view0 = view_info[0];
			Coord &mainarea_beg = view0.offset - view.offset;
			Coord &mainarea_end = mainarea_beg + view0.num;
			rectangleRGBA(view_win[1],
				mainarea_beg.x * view.cell_size.x - 1,
				mainarea_beg.y * view.cell_size.y - 1,
				mainarea_end.x * view.cell_size.x + 1,
				mainarea_end.y * view.cell_size.y + 1,
				0xff, 0xff, 0xff, 0xff
			);
		}
		SDL_UpdateRect(view_win[n], 0, 0, 0, 0);
		SDL_BlitSurface(view_win[n], NULL, screen, &view_rect[n]);
	}
	SDL_UpdateRects(screen, 2, view_rect);
}


void Game::normalize_view() {
	if (
		man->coord.y < 0 || man->coord.y >= NUM_CELLS_Y ||
		man->coord.x < 0 || man->coord.x >= NUM_CELLS_X)
	{
		error_stream << "Internal error, man coordinates are out of range: "
			<< man->coord << endl;
		exit(1);
	}

	for (int n = 0; n < 2; n++) {
		ViewInfo &view = view_info[n];
		const Coord half1_view(view.num.y / 2, view.num.x / 2);
		const Coord &half2_view = view.num - half1_view;

		Coord &test1_coord = man->coord - half1_view;
		if (test1_coord.y < 0) test1_coord.y = 0;
		if (test1_coord.x < 0) test1_coord.x = 0;

		Coord &test2_coord = man->coord + half2_view;
		if (test2_coord.y > NUM_CELLS_Y) test1_coord.y = view.max.y;
		if (test2_coord.x > NUM_CELLS_X) test1_coord.x = view.max.x;

		if (view.offset == test1_coord)
			continue;
		view.offset = test1_coord;
		view.end = view.offset + view.num;
//error_stream << "[" << n << "] offset=" << view_info[n].offset << ", num=" << view_info[n].num << ", max=" << view_info[n].max << ", total_num=" << view_info[n].total_num << endl;
	}
}


Boolean Game::move_creatures() {
	if (man->do_move())
		normalize_view();

	for (int i = 0; i < num_enemies; i++) {
		enemies[i]->do_move();
	}
	return False;
}


int Game::run() {
	normalize_view();

	int finished = 0;
	SDL_Event event;
	next_time = SDL_GetTicks() + tick_interval;

	while (!finished) {
		update_screen();

		// Wait for the next tick
		SDL_Delay(time_left());
		next_time += tick_interval;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_ACTIVEEVENT:
				if (event.active.state & SDL_APPACTIVE) {
					if (event.active.gain) {
						cout << "App activated" << endl;
					} else {
						cout << "App iconified" << endl;
					}
				}
				break;

			case SDL_QUIT:
				exit(0);

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				char sym = event.key.keysym.sym;
				if (sym == SDLK_KP_MINUS || sym == SDLK_KP_PLUS)
				{
					if (event.type == SDL_KEYUP) break;
					Boolean zoom_in = sym == SDLK_KP_PLUS
						? True : False;
					view_info[1].zoom(zoom_in);
					MINI_CELL_SIZE = view_info[1].cell_size;
					normalize_view();
					update_screen();
				} else
				if (sym == '[' || sym == ']')
				{
					if (event.type == SDL_KEYUP) break;
					int new_tick_interval = sym == ']'
						? tick_interval / 2
						: tick_interval * 2;
					if (new_tick_interval >= MIN_TICK_INTERVAL &&
						new_tick_interval <= MAX_TICK_INTERVAL)
						tick_interval = new_tick_interval;
				} else
				if (sym == SDLK_RETURN &&
					(event.key.keysym.mod & KMOD_ALT))
				{
					if (event.type == SDL_KEYUP) break;
					toggle_full_screen();
					update_screen();
				} else {
					SDL_PushEvent(&event);
					goto CONT;
				}
			}
		}

CONT:
		move_creatures();
	}
	return 0;
}
