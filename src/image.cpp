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
#include <SDL/SDL_rotozoom.h>

extern Size NORM_CELL_SIZE;
extern Size MINI_CELL_SIZE;

struct ImageCache {
	char *name;
	SDL_Surface *surface;
	SDL_Surface *surface2;
	Size norm_cell_size;
	Size mini_cell_size;
};
const int MAX_IMAGE_CACHE_SIZE = 100;
static ImageCache image_cache[MAX_IMAGE_CACHE_SIZE];
static int image_cache_count = 0;

ImageCache *try_from_cache(const char *image_name, Boolean is_mini = False) {
	for (int i = 0; i < image_cache_count; i++)
		if (strcmp(image_cache[i].name, image_name) == 0)
			return &image_cache[i];
	return NULL;
}

static void add_to_cache(
	const char *image_name, SDL_Surface *surface, SDL_Surface *surface2)
{
	ImageCache &cache_entry = image_cache[image_cache_count];
	if (cache_entry.name) free(cache_entry.name);
	cache_entry.name = (char *)malloc(strlen(image_name) + 1);
	strcpy(cache_entry.name, image_name);
	cache_entry.surface = surface;
	cache_entry.surface2 = surface2;
	cache_entry.norm_cell_size = NORM_CELL_SIZE;
	cache_entry.mini_cell_size = MINI_CELL_SIZE;
	if (image_cache_count < MAX_IMAGE_CACHE_SIZE - 1) {
		image_cache_count++;
	}
}

SDL_Surface *create_mini_cell_image(SDL_Surface *surface) {
	return zoomSurface(surface,
		(double)MINI_CELL_SIZE.x / NORM_CELL_SIZE.x,
		(double)MINI_CELL_SIZE.y / NORM_CELL_SIZE.y,
		SMOOTHING_ON);
}

SDL_Surface *load_image_file(const char *filename) {
	SDL_Surface *pcx, *surface;

	pcx = IMG_Load(filename);
	if (!pcx) {
		error_stream << "Could not load image '" << filename << "'" << endl;
		exit(-1);
	}

	surface = SDL_DisplayFormatAlpha(pcx);
	SDL_FreeSurface(pcx);

	return surface;
}

SDL_Surface *load_cell_image(const char *image_name, Boolean is_mini = False) {
	static char filename[500];
	if (!image_name) {
		error_stream << "No image name to load" << endl;
		exit(-1);
	}
	ImageCache *cache_entry = try_from_cache(image_name, is_mini);
	if (cache_entry) {
		if (is_mini && MINI_CELL_SIZE != cache_entry->mini_cell_size) {
			cache_entry->mini_cell_size = MINI_CELL_SIZE;
			free(cache_entry->surface2);
			cache_entry->surface2 = create_mini_cell_image(cache_entry->surface);
		}
		return is_mini ? cache_entry->surface2 : cache_entry->surface;
	}

	sprintf(filename, "%s/cell/%s.png", IMAGES_DIR, image_name);
	SDL_Surface *surface = load_image_file(filename);
	SDL_Surface *surface2 = create_mini_cell_image(surface);

	add_to_cache(image_name, surface, surface2);
	return surface;
}
