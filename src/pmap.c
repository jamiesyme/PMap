#include "pmap.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdlib.h>


int            _pmapWidth;
int            _pmapHeight;
int            _pmapLength;
unsigned char* _pmapPixels;
SDL_Window*    _pmapSdlWindow;
SDL_GLContext  _pmapGlContext;


void pmapInit(int w, int h)
{
	// Start the window
	SDL_Init(SDL_INIT_VIDEO | 
	         SDL_INIT_TIMER);
	_pmapSdlWindow = SDL_CreateWindow("PMap",
	                                  SDL_WINDOWPOS_CENTERED,
	                                  SDL_WINDOWPOS_CENTERED,
	                                  w, h,
	                                  SDL_WINDOW_OPENGL);
	_pmapGlContext = SDL_GL_CreateContext(_pmapSdlWindow);

	// Setup the pixel data
	_pmapWidth  = w;
	_pmapHeight = h;
	_pmapLength = w * h;
	_pmapPixels = malloc(_pmapLength * 4);
	
	// Clear the screen
	pmapClear();
	
	// Disable any GL modifiers that are on by default
	glDisable(GL_DITHER);
	glDisable(GL_MULTISAMPLE);
}


void pmapKill()
{
	// Close the window
	SDL_GL_DeleteContext(_pmapGlContext);
	SDL_DestroyWindow(_pmapSdlWindow);
	SDL_Quit();
	_pmapSdlWindow = 0;
	
	// Release the pixels
	_pmapWidth  = 0;
	_pmapHeight = 0;
	_pmapLength = 0;
	free(_pmapPixels);
	_pmapPixels = 0;
}


void pmapClear()
{
	// Set the screen to white
	memset(_pmapPixels, 255, _pmapLength * 4);
}


void pmapCommit()
{
	// Draw
	glDrawPixels(_pmapWidth, 
	             _pmapHeight, 
	             GL_RGBA, 
	             GL_UNSIGNED_BYTE, 
	             _pmapPixels);
	
	// Present the screen
	SDL_GL_SwapWindow(_pmapSdlWindow);
}


void pmapSet(int x, int y,
             unsigned char r,
             unsigned char g,
             unsigned char b)
{
	if (x < 0 || x >= _pmapWidth ||
	    y < 0 || y >= _pmapHeight)
		return;
	_pmapPixels[(y * _pmapWidth + x) * 4 + 0] = r;
	_pmapPixels[(y * _pmapWidth + x) * 4 + 1] = g;
	_pmapPixels[(y * _pmapWidth + x) * 4 + 2] = b;
}


void pmapFastSet(int x, int y,
                 unsigned char r,
                 unsigned char g,
                 unsigned char b)
{
	_pmapPixels[(y * _pmapWidth + x) * 4 + 0] = r;
	_pmapPixels[(y * _pmapWidth + x) * 4 + 1] = g;
	_pmapPixels[(y * _pmapWidth + x) * 4 + 2] = b;
}


void pmapGet(int x, int y,
             unsigned char* r,
             unsigned char* g,
             unsigned char* b)
{
	if (x < 0 || x >= _pmapWidth ||
	    y < 0 || y >= _pmapHeight)
		return;
	if (r) *r = _pmapPixels[(y * _pmapWidth + x) * 4 + 0];
	if (g) *g = _pmapPixels[(y * _pmapWidth + x) * 4 + 1];
	if (b) *b = _pmapPixels[(y * _pmapWidth + x) * 4 + 2];
}


void pmapFastGet(int x, int y,
                 unsigned char* r,
                 unsigned char* g,
                 unsigned char* b)
{
	*r = _pmapPixels[(y * _pmapWidth + x) * 4 + 0];
	*g = _pmapPixels[(y * _pmapWidth + x) * 4 + 1];
	*b = _pmapPixels[(y * _pmapWidth + x) * 4 + 2];
}
