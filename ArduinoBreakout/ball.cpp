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
#ifndef BALLCPP
#define BALLCPP

#include "tiles.cpp"
#include "config.h"
#include "beeping.cpp"
#include "paddle.cpp"

class Ball
{
  const int SCORE[9] = {0, 1, 1, 3, 3, 5, 5, 7, 7};
  
  int left, right, top, bottom;
  
  float x, y, xi, yi;

  public:
  
    Ball(int left_, int right_, int top_, int bottom_)
    {
      left = left_;
      right = right_;
      top = top_;
      bottom = bottom_;
    }

    void clear()
    {
      tft.fillRectangle(x, y, BALL_R * 2, BALL_R * 2, BLACK);
    }
  
    void draw()
    {
      tft.fillRectangle(x, y, BALL_R * 2, BALL_R * 2, BALL_COLOR);
    }

    void setXY(int x_, int y_)
    {
      x = x_;
      y = y_;
    }

    void setX(int x_)
    {
      x = x_;
    }

    void setXiYi(int xi_, int yi_)
    {
      xi = xi_;
      yi = yi_;
    }

    bool escaped(Paddle &paddle)
    {
      return y >= paddle.getY();
    }
  
    void move()
    {
      if((xi < 0 && x + xi < left)||(xi > 0 && x +xi >= right))
      {
        xi *= -1;
      }

      if(yi < 0 && y+yi-BALL_R*2 < top)
      {
        yi *= -1;
      }

      x+= xi;
      y+= yi;
    }

    int getX()
    {
      return x;
    }

    int getY()
    {
      return y;
    }

    int getXi()
    {
      return xi;
    }

    // check for collision with paddle
    // calculate score and bounce

    int collision(Tiles &tiles)
    {
      int x = this->x+xi;
      int y = this->y+yi;
    
      int hit = hitTile( tiles, x,              y  )               ||
                hitTile( tiles, x + BALL_R * 2, y + BALL_R * 2  )  ||
                hitTile( tiles, x + BALL_R * 2, y  )               ||
                hitTile( tiles, x,              y + BALL_R * 2  );

      return SCORE[hit];
    }

    // check for collision with paddle
    // and bounce
    bool collision(Paddle &paddle)
    {
      // only interested if ball is moving down
      if ( yi < 0 ) return false;

      int ny = y+yi+BALL_R*2;

      if ( ny < paddle.getY() ) return false;
    
      // ball center
      const int bc = x + BALL_R;

      const int diff = bc - paddle.getX();

      if ( diff < -PADDLE_W-PADDLE_TOLERANCE || diff > PADDLE_W + PADDLE_TOLERANCE)
      {
        return false;
      }
      else if (diff > 0)
      {
        const int hit = diff / ((PADDLE_W + PADDLE_TOLERANCE)/2);
        xi = (float)hit * .5f + .5f; 
        yi = - 2 + xi;
      }
      else if (diff < 0)
      {
        const int hit = diff / ((PADDLE_W + PADDLE_TOLERANCE)/2);
        xi = (float)hit * .5f - .5f;
        yi = - 2 - xi;
      }
      else
      {
        yi *= -1;
      }
    
      return true;
    }

private:

    int hitTile(Tiles &tiles, int x, int y)
    {
      int ty =(y - TILES_TOP)/ TILE_H;
      int tx =(x - TILES_LEFT)/ TILE_W;
      
      boolean hit = ty >= 0 && ty < ROWS && tx >= 0 && tx < COLS && tiles.exists(tx,ty);
      
      if (!hit) return 0;
      
      tiles.clearTile( tx, ty );
      
      tft.fillRectangle(TILES_LEFT + tx * TILE_W, TILES_TOP + ty * TILE_H, TILE_W - 2, TILE_H - 2, BLACK);
      


      ty*= TILE_H;
      
      int ty2= ty + TILE_H;

      if ( (yi > 0 && y > ty) || (yi < 0 && y < ty2))
      {
        xi *=-1;
      }
      else
      {
        yi *=-1;
      }      

      return ROWS - ty;
    }
  
};

#endif
