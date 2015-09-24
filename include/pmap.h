#pragma once

void pmapInit(int w, int h);
void pmapKill();

int pmapWidth();
int pmapHeight();

void pmapClear();
void pmapCommit();

void pmapSet(int x, int y, 
             unsigned char r, 
             unsigned char g, 
             unsigned char b);
             
void pmapFastSet(int x, int y, 
                 unsigned char r, 
                 unsigned char g, 
                 unsigned char b);
             
void pmapGet(int x, int y,
             unsigned char* r,
             unsigned char* g,
             unsigned char* b);
             
void pmapFastGet(int x, int y,
                 unsigned char* r,
                 unsigned char* g,
                 unsigned char* b);
