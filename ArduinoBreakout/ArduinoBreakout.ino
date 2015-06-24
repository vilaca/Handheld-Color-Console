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
#include <SPI.h>

#include "beeping.cpp"
#include "breakout.cpp"
#include "TFTv2_extended.h"

void setup() {
  
  TFT_BL_ON;      // turn on the background light
  tft.init();  // init TFT library

  Joystick::init();

  Beeping::turnOn();
}

void loop() {
  
  drawWallTiles();

  char* bo ="BREAKOUT";
  const int len = strlen (bo) * FONT_SPACE * 6;
  const int left = (MAX_X - len ) / 2;

  tft.drawStringWithShadow(bo, left, 78, 6, WHITE, BLACK);

  boolean go = false;
  do
  {
    animateScreen();

    tft.drawCenteredString("Press fire to play!", 136, 2, CYAN);

    unsigned long last = millis();
    do
    {
      go = Joystick::fire();
      
      if ( millis() - last > 8000 ) break;
      
    } while (!go);

  } while (!go);

  Breakout game;
  game.run();
}

void drawWallTiles()
{
  for ( int c = 0; c <  320; c+=40)
  {
    
    tft.fillRectangle(c+0, 0, 39, 240, RED);

    for ( int i = 20; i < 240; i+= 20)
    {
      tft.drawHorizontalLine(c+0, i, 40, GRAY2);
      tft.drawHorizontalLine(c+0, i+1, 40, GRAY2);
    }

    for ( int i = 0; i < 240; i+= 40)
    {
      tft.drawVerticalLine(c+20, i, 20, GRAY2 );
      tft.drawVerticalLine(c+21, i, 20, GRAY2 );
      tft.drawVerticalLine(c+39, i+20, 20, GRAY2 );
      tft.drawVerticalLine(c+38, i+20, 20, GRAY2 );
    }
  }
}

void animateScreen()
{
  int addr = 320;
  while(addr >= 0 && !Joystick::fire())
  {
    tft.scroll(addr);
    addr-=2;
    
    delay(10);
  }
  tft.scroll(0);
}
