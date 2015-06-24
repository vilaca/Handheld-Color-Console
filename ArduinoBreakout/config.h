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
#include "TFTv2_extended.h"

#define ROWS                6
#define COLS                14

#define TILE_W              (int)((MAX_X + 1) / COLS)
#define TILE_H              (int)(TILE_W / 2.2)

#define BALL_R              1
#define BALL_SPEED_H        1
#define BALL_SPEED_V        1
#define BALL_COLOR          CYAN
#define BALL_MOVE_WAIT      4

#define PADDLE_W            16
#define PADDLE_H            5
#define PADDLE_TOLERANCE    4
#define PADDLE_COLOR        LIGHTGREEN
#define PADDLE_MOVE_WAIT    5

#define BOARD_LEFT          (int)(2)
#define BOARD_RIGHT         (int)(MAX_X - 2)
#define BOARD_TOP           23

#define TILES_LEFT          (int)(((MAX_X + 1) - ( COLS * TILE_W ) )/ 2)
#define TILES_TOP           (BOARD_TOP + 2.8 * TILE_H)

#define TILE_IS_DRAWN       1
#define TILE_IS_NOT_DRAWN   0

#define SCOREBOARD_COLOR  WHITE
#define BACKGROUND_COLOR  BLACK
