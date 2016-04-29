#include "pmap/pmap.h"
#include <SDL.h>
#include <SDL_opengl.h>


static int g_quit;
static size_t g_width;
static size_t g_height;
static unsigned char* g_pixels;
static SDL_Window* g_sdlWindow;
static SDL_GLContext g_glContext;


void pmap_init( const char* title, size_t width, size_t height )
{
	// Start the window
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	g_sdlWindow = SDL_CreateWindow(title,
	                               SDL_WINDOWPOS_CENTERED,
	                               SDL_WINDOWPOS_CENTERED,
	                               width, height,
	                               SDL_WINDOW_OPENGL);
	g_glContext = SDL_GL_CreateContext(g_sdlWindow);

	// Setup the pixel data
	g_width = width;
	g_height = height;
	g_pixels = malloc(width * height * 4 * sizeof(unsigned char));
	
	// Disable any GL modifiers that are on by default
	glDisable(GL_DITHER);
	glDisable(GL_MULTISAMPLE);
}


void pmap_kill()
{
	SDL_GL_DeleteContext( g_glContext );
	SDL_DestroyWindow( g_sdlWindow );
	SDL_Quit();
	g_sdlWindow = 0;
	
	free( g_pixels );
	g_width  = 0;
	g_height = 0;
	g_pixels = 0;
}


void pmap_update()
{
	SDL_Event event;

	glDrawPixels(g_width, 
	             g_height, 
	             GL_RGBA, 
	             GL_UNSIGNED_BYTE, 
	             g_pixels);

	SDL_GL_SwapWindow(g_sdlWindow);

	while ( SDL_PollEvent( &event ) ) {
		if ( event.type == SDL_QUIT ) {
			g_quit = 1;
		}
	}
}


int pmap_shouldQuit()
{
	return g_quit;
}


void pmap_set( size_t x, size_t y, unsigned char* rgb )
{
	g_pixels[(y * g_width + x) * 4 + 0] = rgb[0];
	g_pixels[(y * g_width + x) * 4 + 1] = rgb[1];
	g_pixels[(y * g_width + x) * 4 + 2] = rgb[2];
	g_pixels[(y * g_width + x) * 4 + 3] = 255;
}


unsigned char* pmap_get( size_t x, size_t y )
{
	return &g_pixels[(y * g_width + x) * 4];
}
