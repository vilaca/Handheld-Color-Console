/*

  Edited by João Vilaça.
  
  Currently an work in progress, a few changes were done: 
  - LED pin moved to pin 9 on Atmega 328;
  - Screen orientation rotated 90/270º on initialization;
  - Added a few new methods;
  - ...

*/
/*
 2012 Copyright (c) Seeed Technology Inc.

 Authors: Albert.Miao & Loovee, 
 Visweswara R (with initializtion code from TFT vendor)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
#ifndef TFTv2_h
#define TFTv2_h

#if defined(ARDUINO) && ARDUINO >= 100
#define SEEEDUINO
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <avr/pgmspace.h>

#include <SPI.h>

//Basic Colors
#define BLACK       0x0000
#define BLUE	    0x001f
#define CYAN		0x07ff	
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define DARKGREEN	0x03E0
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define GRAY1		0x8410  
#define GRAY2		0x4208  
#define GRAY3		0x2104  
#define GREEN       0x07e0
#define LIGHTGREEN  0xAFE5      /* 173, 255,  47 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define RED         0xf800
#define WHITE       0xffff
#define YELLOW      0xffe0

//TFT resolution 240*320
#define MIN_X	0
#define MIN_Y	0
#define MAX_X	319
#define MAX_Y	239

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

#define TFT_CS_LOW  {DDRE |= 0x08;PORTE &=~ 0x08;}
#define TFT_CS_HIGH {DDRE |= 0x08;PORTE |=  0x08;}

#define TFT_DC_LOW  {DDRH |= 0x08;PORTH &=~ 0x08;}
#define TFT_DC_HIGH {DDRH |= 0x08;PORTH |=  0x08;}

#define TFT_BL_OFF  {DDRH |= 0x10;PORTH &=~ 0x10;}
#define TFT_BL_ON   {DDRH |= 0x10;PORTH |=  0x10;}

#define TFT_RST_OFF {DDRD |= 0x10;PORTD |=  0x10;}
#define TFT_RST_ON  {DDRD |= 0x10;PORTD &=~ 0x10;}

#elif defined(__AVR_ATmega32U4__)

#define TFT_CS_LOW  {DDRC |= 0x40;PORTC &=~ 0x40;}
#define TFT_CS_HIGH {DDRC |= 0x40;PORTC |=  0x40;}
#define TFT_DC_LOW  {DDRD |= 0x80;PORTD &=~ 0x80;}
#define TFT_DC_HIGH {DDRD |= 0x80;PORTD |=  0x80;}
#define TFT_BL_OFF  {DDRE |= 0x40;PORTE &=~ 0x40;}
#define TFT_BL_ON   {DDRE |= 0x40;PORTE |=  0x40;}
#define TFT_RST_OFF {DDRD |= 0x10;PORTD |=  0x10;}
#define TFT_RST_ON  {DDRD |= 0x10;PORTD &=~ 0x10;}

#else

// pin 5
#define TFT_CS_LOW  {DDRD |= 0x20;PORTD &=~ 0x20;}
#define TFT_CS_HIGH {DDRD |= 0x20;PORTD |=  0x20;}

// pin 6
#define TFT_DC_LOW  {DDRD |= 0x40;PORTD &=~ 0x40;}
#define TFT_DC_HIGH {DDRD |= 0x40;PORTD |=  0x40;}

// pin 9
#define TFT_BL_OFF  {DDRB |= 0x02;PORTB &=~ 0x02;}
#define TFT_BL_ON   {DDRB |= 0x02;PORTB |=  0x02;}

// pin 4
#define TFT_RST_OFF {DDRD |= 0x10;PORTD |=  0x10;}
#define TFT_RST_ON  {DDRD |= 0x10;PORTD &=~ 0x10;}

#endif

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2

#ifndef INT8U
#define INT8U unsigned char
#endif
#ifndef INT16U
#define INT16U unsigned int
#endif

extern INT8U simpleFont[][8];

class TFT
{
public:
	void init (void);
	void setCol(INT16U StartCol,INT16U EndCol);
	void setPage(INT16U StartPage,INT16U EndPage);
	void setXY(INT16U poX, INT16U poY);
	void setPixel(INT16U poX, INT16U poY,INT16U color);
	void sendCMD(INT8U index);
	//void sendPackage(INT16U *data,INT8U howmany);
	void sendDATA(INT8U data);
	void sendData(INT16U data);
	INT8U readRegister(INT8U Addr,INT8U xParameter);
	void fillScreen(INT16U color);
	INT8U readID(void);

	void drawChar(INT8U ascii,INT16U poX, INT16U poY,INT16U size, INT16U fgcolor);
	void drawString(char *string,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	void drawStringWithShadow(char *string,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor, INT16U shcolor );
	void drawCenteredString(char *string, INT16U poY,INT16U size,INT16U fgcolor );
	void fillRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);
	void fillRectangleUseBevel(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);

	void drawLine(INT16U x0,INT16U y0,INT16U x1,INT16U y1,INT16U color);
	void drawVerticalLine(INT16U poX, INT16U poY,INT16U length,INT16U color);
	void drawHorizontalLine(INT16U poX, INT16U poY,INT16U length,INT16U color);
	void drawRectangle(INT16U poX, INT16U poY, INT16U length,INT16U width,INT16U color);
	void drawRectangle(INT16U poX, INT16U poY, INT16U length,INT16U width,INT16U color, byte thickness);

	void drawCircle(int poX, int poY, int r,INT16U color);
	void fillCircle(int poX, int poY, int r,INT16U color);

	void drawTriangle(int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color);
	INT8U drawNumber(long long_num,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	INT8U drawFloat(float floatNumber,INT8U decimal,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	INT8U drawFloat(float floatNumber,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
};

extern TFT Tft;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
