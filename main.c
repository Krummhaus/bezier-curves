#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define BACKGROUN_COLOR 0x200000FF
/*
The macro `HEX_COLOR(hex)` expands a hexadecimal color value (in the form `0xRRGGBBAA`,
where RR is red, GG is green, BB is blue, and AA is alpha) into its RGBA components.
Here's how it works:
- **Right Shift (>>)**: The `>>` operator shifts the bits of the hexadecimal value to the
right by a specified number of bits. Each color component in the hexadecimal representation occupies 8 bits.
  
  - `((hex) >> (3 * 8)) & 0xFF`: Extracts the alpha value by shifting 24 bits to the right.
  - `((hex) >> (2 * 8)) & 0xFF`: Extracts the red value by shifting 16 bits to the right.
  - `((hex) >> (1 * 8)) & 0xFF`: Extracts the green value by shifting 8 bits to the right.
  - `((hex) >> (0 * 8)) & 0xFF`: Extracts the blue value without shifting.

- **Bitwise AND (&)**: The expression `& 0xFF` masks the result to keep only the lowest 8 bits, which correspond to the color channel being extracted.

By using this macro, an input like `0x000000FF` (which represents black with full opacity) would expand to `0, 0, 0, 255` for RGBA.
*/
#define HEX_COLOR(hex) \
    ((hex) >> (3 * 8)) & 0xFF, \
    ((hex) >> (2 * 8)) & 0xFF, \
    ((hex) >> (1 * 8)) & 0xFF, \
    ((hex) >> (0 * 8)) & 0xFF 



int check_sdl_code(int code)
{
    if (code < 0) {
	fprintf(stderr, "SDL error: %s\n", SDL_GetError());
	exit(1);
    }
    return code;
}

void *check_sdl_ptr(void *ptr)
{
    if (ptr == NULL) {
	fprintf(stderr, "SDL error: %s\n", SDL_GetError());
	exit(1);
    }
    return ptr;
}


int main(void)
{
    check_sdl_code(
	SDL_Init(SDL_INIT_VIDEO));

    SDL_Window * const window =
	check_sdl_ptr(
	    SDL_CreateWindow(
		"SDL Window Bezier",
		0, 0,
		SCREEN_W,
		SCREEN_H,
		SDL_WINDOW_RESIZABLE));

    SDL_Renderer * const renderer =
	check_sdl_ptr(
	    SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED));

    // Event loop
    int quit = 0;
    while (!quit) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	    switch (event.type) {
	    case SDL_QUIT:
	      quit = 1;
	      break;
	    }
	}

	check_sdl_code(
	    SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUN_COLOR)));

	check_sdl_code(
	    SDL_RenderClear(renderer));

	// Swap buffers
	SDL_RenderPresent(renderer);
    }

SDL_Quit();

  return 0;
}
