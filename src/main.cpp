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
#include <signal.h>

// ---------------------------------------------------------------------------

SDL_Surface *screen;
SDL_Surface *view_win[2];
SDL_Rect view_rect[2] = {
	{  16, 16, 448, 448 },
	{ 480, 16, 144, 144 },
};
static SDL_Rect screen_rect = { 0, 0, 640, 480 };

int is_full_screen = 0;

void set_video_mode() {
	int video_flags = SDL_HWSURFACE | SDL_HWACCEL;
	if (is_full_screen) video_flags |= SDL_FULLSCREEN;
	screen = SDL_SetVideoMode(screen_rect.w, screen_rect.h, 0, video_flags);
	if (screen == NULL) {
		error_stream << "Unable to set hardware video mode: "
			<< SDL_GetError() << endl;
		exit(-1);
	}

	const char *frame_file_name = IMAGES_DIR "/frame/full.jpg";
	SDL_Surface *frame = IMG_Load(frame_file_name);
	if (frame == NULL) {
		error_stream << "Can't load the frame image " << frame_file_name << endl;
		exit(-1);
	}
	SDL_BlitSurface(frame, NULL, screen, &screen_rect);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int toggle_full_screen() {
	is_full_screen = !is_full_screen;
	set_video_mode();
}

int filter_events(const SDL_Event *event)
{
#if 0
	static int ignore_quit = 1;

	// This quit event signals the closing of the window
	if (event->type == SDL_QUIT) {
		if (ignore_quit) {
			//printf("Quit event filtered out -- try again.\n");
			ignore_quit = 0;
			return 0;
		}
	} else {
		ignore_quit = 1;
	}
	if (event->type == SDL_MOUSEMOTION) {
		//printf("Mouse moved to (%d,%d)\n",
		//	event->motion.x, event->motion.y);
		return 0;  // drop it, we've handled it
	}
#endif
	return 1;
}

int main(int argc, char **argv)
{
	// Processing arguments
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			cout
				<< PACKAGE " - supaplex-like game" << endl
				<< "" << endl;
			exit(0);
		}
		if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--full-screen")) {
			is_full_screen = 1;
		}
	}

	// Initializing screen
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	//signal(SIGSEGV, SIG_DFL);  // to get core dump
	atexit(SDL_Quit);
	SDL_WM_SetCaption(PACKAGE, PACKAGE);
//	SDL_WM_SetIcon(SDL_LoadXPM(IMAGES_DIR "/icon.xpm"), 0);

	set_video_mode();

	for (int n = 0; n < 2; n++) {
		view_win[n] = SDL_AllocSurface(screen->flags,
			view_rect[n].w, view_rect[n].h,
			screen->format->BitsPerPixel,
			screen->format->Rmask, screen->format->Gmask, screen->format->Bmask,
			0);
		if (view_win[n] == NULL) {
			error_stream << "Unable to allocate a view surface: "
				<< SDL_GetError() << endl;
			exit(-1);
		}
	}

	SDL_ShowCursor(SDL_ENABLE);
	srand(SDL_GetTicks());

	// Currently ignore mouse
//	SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
//	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_SetEventFilter(filter_events);

	Game game;
	game.run();
	return 0;
}

ostream &operator <<(ostream &out, const SDL_Rect &rect) {
	return out << "("
		<< rect.x << ", "
		<< rect.y << ", "
		<< rect.w << ", "
		<< rect.h << ")";
}
