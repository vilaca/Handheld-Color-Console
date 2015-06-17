/*
    Arduino Tetris
    Copyright (C) 2015  João André Esteves Vilaça

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

#include "TFTv2_extended.h"
#include <SPI.h>

#include "joystick.cpp"
#include "beeping.cpp"
#include "tetris.cpp"
#include "sequencer.cpp"

void setup() {

  Sequencer::init();

  TFT_BL_ON;      // turn on the background light

  Tft.init();  // init TFT library

  // play turnon sound	
  Beeping::turnOn();

  // initialize joystick
  Joystick::init();
}

void loop() {

  // title screen
  drawPreGameScreen();

  // wait a bit before playing sounds
  delay(700);

  // start playing tetris theme
  Sequencer::start();

  // wait for click
  while (!Joystick::fire());

  // stop playing tetris theme
  Sequencer::stop();

  // load game
  Tetris t;
  t.run();

  // game ended
  gameOver();
}

void drawPreGameScreen()
{
  Tft.fillScreen(WHITE);
  Tft.drawCenteredString("Tetris", 40, 8, BLUE);
  Tft.drawCenteredString("Click to play", 110, 2, BLACK);
  Tft.drawCenteredString("http://vilaca.eu", 220, 2, PURPLE);
}


void gameOver()
{
  Tft.fillRectangle(32, 84, 256, 52, BLACK);
  Tft.drawString("Game Over", 48, 94, 4, 0x3ffff);
  Tft.drawRectangle(32, 84, 256, 52, RED);

  Beeping::beep(600, 200);
  delay(300);
  Beeping::beep(600, 200);
  delay(300);
  Beeping::beep(200, 600);
  delay(1500);
  Joystick::waitForClick();
}


ISR(TIMER1_COMPA_vect) {

  // sequencer plays tetris theme
  Sequencer::play();
}
