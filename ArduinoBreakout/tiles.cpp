/*
    Arduino Breakout
    Copyright (C) 2015 João André Esteves Vilaça

    https://github.com/vilaca/Handheld-Color-Console

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef TILESCPP
#define TILESCPP

#include "beeping.cpp"
#include "config.h"

class Tiles {

  const int COLORS[ROWS] = { RED, MAGENTA, OLIVE, YELLOW, GREEN, NAVY };
  
  byte tiles[ROWS][COLS];
  
  int tilesLeft;
  
  public:

    boolean allGone()
    {
      return tilesLeft == 0;
    }
  
    void drawAll()
    {
      for(int i = 0; i < ROWS; i++)
      {
        for(int j = 0; j < COLS; j++)
        {
          tiles[i][j] = TILE_IS_NOT_DRAWN;
        }
      }

      int tilesLeftToDraw = ROWS * COLS;
    
      while ( tilesLeftToDraw > 0)
      {
        int c = random(COLS);
        int r = random(ROWS);
        if (tiles[r][c] == TILE_IS_DRAWN)
        {
          continue;
        }

        tft.fillRectangle(TILES_LEFT + c * TILE_W, TILES_TOP + r * TILE_H, TILE_W - 2, TILE_H - 2, COLORS[r]);
        tiles[r][c]= TILE_IS_DRAWN;
        tilesLeftToDraw--;

        Beeping::beep( 400 + r* 35 + c * 2, 5 );
        delay(5);
      }
    
      tilesLeft = ROWS * COLS;
    }
    
    void clearTile( int x, int y )
    {
      tiles[y][x] = TILE_IS_NOT_DRAWN;
      tilesLeft--;
    }
    
    boolean exists(int x, int y)
    {
      return tiles[y][x] == TILE_IS_DRAWN;
    }
};

#endif