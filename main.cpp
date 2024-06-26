#include "stdafx.h"
#include "Game.h"

int main() {
	Game game;
	game.runGame();

	/*
	int t1, t2, quit, frames, rc;
	double dt, worldTime, fpsTimer, fps, distance;

	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
	SDL_SetWindowTitle(window, "King Donkey");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;

	while (!quit) {
		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna� od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		dt = (t2 - t1) * 0.001;
		t1 = t2;

		worldTime += dt;

		SDL_FillRect(screen, NULL, czarny);

		fpsTimer += dt;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};

		//// tekst informacyjny / info text
		//DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		////            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		//sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		//DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		////	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

		charset = SDL_LoadBMP("Sprites/Characters/Player/reimuidle.bmp");
		if (charset == NULL) {
			printf("SDL_LoadBMP(reimuidle.bmp) error: %s\n", SDL_GetError());
			SDL_FreeSurface(screen);
			SDL_DestroyTexture(scrtex);
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			return 1;
		};
		SDL_SetColorKey(charset, true, 0x000000);

		//SDL_BlitSurface();
		
		//eti = SDL_LoadBMP("./eti.bmp");
		//if (eti == NULL) {
		//	printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		//	SDL_FreeSurface(charset);
		//	SDL_FreeSurface(screen);
		//	SDL_DestroyTexture(scrtex);
		//	SDL_DestroyWindow(window);
		//	SDL_DestroyRenderer(renderer);
		//	SDL_Quit();
		//	return 1;
		//};




		SDL_Surface* surface = SDL_LoadBMP("Sprites/Characters/Player/reimuidle.bmp");
		SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		surface = NULL;


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		renderTexture(renderer, image, 50, 80);
		SDL_RenderPresent(renderer);


		// obs�uga zdarze� (o ile jakie� zasz�y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				//else if (event.key.keysym.sym == SDLK_UP) etiSpeed = 2.0;
				//else if (event.key.keysym.sym == SDLK_DOWN) etiSpeed = 0.3;
				break;
			case SDL_KEYUP:

				break;
			case SDL_QUIT:
				quit = 1;
				SDL_DestroyTexture(image);
				break;
			};
		};
		frames++;
	};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	*/

	return 0;
}
