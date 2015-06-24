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
#ifndef PADDLECPP
#define PADDLECPP

#include "config.h"

class Paddle
{
  int x, y;
  
  public:

  // draws paddle on screen when it moves
  // to avoid spending too much time clearing the screen and drawing
  // only the same amount of pixels that the paddle moves are cleared and drawn
  
    void draw(int m)
    {
      if ( m < 0 && x > PADDLE_W )
      {
        // cant move beyond the screen border
        if ( m < -(x - PADDLE_W)) m = -(x - PADDLE_W);

        // remove part of the old paddle on the left
        tft.fillRectangle( x + PADDLE_W + m, y, -m, PADDLE_H, BACKGROUND_COLOR);
      
        // add a bit more to the left of the existing paddle
        tft.fillRectangle( x - PADDLE_W + m, y, -m, PADDLE_H, PADDLE_COLOR);
      
        // remember m < 0
        x+=m;
      }
      else if ( m > 0 && x < MAX_X - PADDLE_W )
      {
        // cant move beyond the screen border
        if ( m > MAX_X - x - PADDLE_W ) m = MAX_X - x - PADDLE_W;
      
        // remove a part of the old paddle on the right
        tft.fillRectangle( x - PADDLE_W, y, m, PADDLE_H, BACKGROUND_COLOR);
      
        // add a bit more  of paddle to the left of the existing paddle
        tft.fillRectangle( x + PADDLE_W, y, m, PADDLE_H, PADDLE_COLOR );
      
        x+=m;
      }
    }
  
    // draws paddle the first time
    // all paddle must be drawn
  
    void draw()
    {
      tft.fillRectangle(x- PADDLE_W, y, PADDLE_W * 2, PADDLE_H, PADDLE_COLOR);
    }
  
    void setXY(int x_, int y_)
    {
      x = x_;
      y = y_;
    }

    int getX()
    {
      return x;
    }

    int getY()
    {
      return y;
    }
};

#endif

