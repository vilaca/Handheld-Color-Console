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

#ifndef SEQUENCERCPP
#define SEQUENCERCPP

#include "Arduino.h"
#include "beeping.cpp"

static const int song[] = {

  NOTE_E5, 4,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 2,
  NOTE_E5, 1,
  NOTE_D5, 1,
  NOTE_C5, 2,
  NOTE_B4, 2,

  NOTE_A4, 4,
  NOTE_A4, 2,
  NOTE_C5, 2,

  NOTE_E5, 4,
  NOTE_D5, 2,
  NOTE_C5, 2,

  NOTE_B4, 2,
  NOTE_E4, 2,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 4,
  NOTE_E5, 4,

  NOTE_C5, 4,
  NOTE_A4, 4,

  NOTE_A4, 2,
  NOTE_A3, 2,
  NOTE_B3, 2,
  NOTE_C4, 2,

  NOTE_D4, 2,
  NOTE_D5, 4,
  NOTE_F5, 2,

  NOTE_A5, 2,
  NOTE_A5, 1,
  NOTE_A5, 1,
  NOTE_G5, 2,
  NOTE_F5, 2,

  NOTE_E5, 6,
  NOTE_C5, 2,

  NOTE_E5, 2,
  NOTE_F5, 1,
  NOTE_E5, 1,
  NOTE_D5, 2,
  NOTE_C5, 2,

  NOTE_B4, 4,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 4,
  NOTE_E5, 4,

  NOTE_C5, 4,
  NOTE_A4, 4,

  NOTE_A4, 8,

  // repeat

  NOTE_E5, 4,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 2,
  NOTE_E5, 1,
  NOTE_D5, 1,
  NOTE_C5, 2,
  NOTE_B4, 2,

  NOTE_A4, 4,
  NOTE_A4, 2,
  NOTE_C5, 2,

  NOTE_E5, 4,
  NOTE_D5, 2,
  NOTE_C5, 2,

  NOTE_B4, 2,
  NOTE_E4, 2,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 4,
  NOTE_E5, 4,

  NOTE_C5, 4,
  NOTE_A4, 4,

  NOTE_A4, 2,
  NOTE_A3, 2,
  NOTE_B3, 2,
  NOTE_C4, 2,

  NOTE_D4, 2,
  NOTE_D5, 4,
  NOTE_F5, 2,

  NOTE_A5, 2,
  NOTE_A5, 1,
  NOTE_A5, 1,
  NOTE_G5, 2,
  NOTE_F5, 2,

  NOTE_E5, 6,
  NOTE_C5, 2,

  NOTE_E5, 2,
  NOTE_F5, 1,
  NOTE_E5, 1,
  NOTE_D5, 2,
  NOTE_C5, 2,

  NOTE_B4, 4,
  NOTE_B4, 2,
  NOTE_C5, 2,

  NOTE_D5, 4,
  NOTE_E5, 4,

  NOTE_C5, 4,
  NOTE_A4, 4,

  NOTE_A4, 8,
  -1
};

static volatile unsigned long last;
static volatile int c;
static volatile int w;
static volatile boolean songOn;


class Sequencer {
  public:

    static void init() {
      
      // enable timer, used to play music sequencer async
      TCCR1A = 0; // No options in control register A
      TCCR1B = (1 << CS10); // Set prescaler to divide by 8
      TIMSK1 = (1 << OCIE1A); // Call ISR when TCNT2 = OCRA2
      OCR1A = 0;// Set frequency of generated wave
      sei(); // Enable interrupts to generate waveform!

      last = c = w = 0;
      songOn = false;
    }

    static void start() {
      init();
      songOn = true;
    }

    static void stop() {
      songOn = false;
      Beeping::mute();
    }

    static void play()
    {
      if (!songOn)
      {
        return;
      }

      unsigned long m = millis();
      if ( m - last > w)
      {
        last = m;

        int fr = song[c++];
        int d = song[c++];

        Beeping::beep (fr, d * 100 );
        w = d * 105;

        if ( song[c] == -1 ) {
          c = 0;
          w = 10000;
          Beeping::mute();
        }
      }
    }
};


#endif

