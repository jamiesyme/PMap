#pragma once

#include <stdlib.h>


void pmap_init( const char* title, size_t width, size_t height );
void pmap_kill();

size_t pmap_getWidth();
size_t pmap_getHeight();

void pmap_update();
int pmap_shouldQuit();

void pmap_set( size_t x, size_t y, unsigned char* rgb );
unsigned char* pmap_get( size_t x, size_t y );

