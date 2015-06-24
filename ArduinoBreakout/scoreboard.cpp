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
#ifndef SCOREBOARDCPP
#define SCOREBOARDCPP

#include "config.h"

class Scoreboard {
  
  int level, lives;
  unsigned long score;
  
  public:
  
    Scoreboard()
    {
      level = 1;
      lives = 4;
      score = 0;
    }
  
    void init()
    {
      // draw back wall and sidewalls

      tft.drawString("     000000000    0",       0, 4, 2, BLACK);
      tft.drawString("   S            L    B",   6, 4, 2, BLUE);
      tft.drawString("              0    1   4",  0, 4, 2, RED);
    }
  
    void update( int scored ){
      score+= scored;
      int digits = nDigits(score);
      tft.drawNumber(score, (15-digits)*12, 4, 2, RED, SCOREBOARD_COLOR);
    }
  
    void nextLevel()
    {
      level++;
      int digits = nDigits(level);
      tft.drawNumber(level,(20-digits)*12, 4, 2, RED, SCOREBOARD_COLOR);
    }
  
    void died()
    {
      lives--;
      if ( lives < 0) return;
      int digits = nDigits(lives);
      tft.drawNumber(lives,(24-digits)*12, 4, 2, RED, SCOREBOARD_COLOR);
    }

    boolean hasLivesLeft()
    {
      return lives > 0;
    }
  
  private:
  
    int nDigits(int value)
    {
      int digits = 1;
      long compare = 10;
      while (compare <= value)
      {
        compare *= 10;
        digits++;
      }
      return digits;
    }
};

#endif