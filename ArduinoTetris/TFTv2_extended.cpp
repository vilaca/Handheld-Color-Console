/*

  Edited by João Vilaça.
  
  Currently an work in progress, a few changes were done: 
  - LED pin moved to pin 9 on Atmega 328;
  - Screen orientation rotated 90/270º on initialization;
  - Added a few new methods;
  - fixed spelling errors on method names
  - removed dead code
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
 Foundation, Inc.,51 Franklin St,Fifth Floor, Boston, MA 02110-1301 USA

*/

#include "TFTv2_extended.h"
#include <SPI.h>
#define FONT_SPACE 6
#define FONT_X 8

void TFT::sendCMD(INT8U index)
{
    TFT_DC_LOW;
    TFT_CS_LOW;
    SPI.transfer(index);
    TFT_CS_HIGH;
}

void TFT::sendDATA(INT8U data)
{
    TFT_DC_HIGH;
    TFT_CS_LOW;
    SPI.transfer(data);
    TFT_CS_HIGH;
}

void TFT::sendData(INT16U data)
{
    INT8U data1 = data>>8;
    INT8U data2 = data&0xff;
    TFT_DC_HIGH;
    TFT_CS_LOW;
    SPI.transfer(data1);
    SPI.transfer(data2);
    TFT_CS_HIGH;
}

/*
void TFT::sendPackage(INT16U *data, INT8U howmany)
{
    INT16U    data1 = 0;
    INT8U   data2 = 0;

    TFT_DC_HIGH;
    TFT_CS_LOW;
    INT8U count=0;
    for(count=0;count<howmany;count++)
    {
        data1 = data[count]>>8;
        data2 = data[count]&0xff;
        SPI.transfer(data1);
        SPI.transfer(data2);
    }
    TFT_CS_HIGH;
}
*/

INT8U TFT::readRegister(INT8U Addr, INT8U xParameter)
{
    INT8U data=0;
    sendCMD(0xd9);                                                      /* ext command                  */
    sendDATA(0x10+xParameter);                                        /* 0x11 is the first Parameter  */
    TFT_DC_LOW;
    TFT_CS_LOW;
    SPI.transfer(Addr);
    TFT_DC_HIGH;
    data = SPI.transfer(0);
    TFT_CS_HIGH;
    return data;
}

void TFT::init (void)
{
    SPI.begin();
    TFT_CS_HIGH;
    TFT_DC_HIGH;
    INT8U i=0, TFTDriver=0;

	TFT_RST_ON;
	delay(10);
	TFT_RST_OFF;

    for(i=0;i<3;i++)
    {
        TFTDriver = readID();
    }

	sendCMD(0xCB);  
	sendDATA(0x39); 
	sendDATA(0x2C); 
	sendDATA(0x00); 
	sendDATA(0x34); 
	sendDATA(0x02); 

	sendCMD(0xCF);  
	sendDATA(0x00); 
	sendDATA(0XC1); 
	sendDATA(0X30); 

	sendCMD(0xE8);  
	sendDATA(0x85); 
	sendDATA(0x00); 
	sendDATA(0x78); 

	sendCMD(0xEA);  
	sendDATA(0x00); 
	sendDATA(0x00); 

	sendCMD(0xED);  
	sendDATA(0x64); 
	sendDATA(0x03); 
	sendDATA(0X12); 
	sendDATA(0X81); 

	sendCMD(0xF7);  
	sendDATA(0x20); 

	sendCMD(0xC0);    	//Power control 
	sendDATA(0x23);   	//VRH[5:0] 

	sendCMD(0xC1);    	//Power control 
	sendDATA(0x10);   	//SAP[2:0];BT[3:0] 

	sendCMD(0xC5);    	//VCM control 
	sendDATA(0x3e);   	//Contrast
	sendDATA(0x28); 

	sendCMD(0xC7);    	//VCM control2 
	sendDATA(0x86);  	 //--

	sendCMD(0x36);    	// Memory Access Control 
    
    //orientation
	sendDATA(0xE8);  	//C8	   //48 68绔栧睆//28 E8 妯睆

	sendCMD(0x3A);    
	sendDATA(0x55); // 16 bit pixel

	sendCMD(0xB1);    
	sendDATA(0x00);  
	sendDATA(0x18); 

	sendCMD(0xB6);    	// Display Function Control 
	sendDATA(0x08); 
	sendDATA(0x82);
	sendDATA(0x27);  
 
	sendCMD(0xF2);    	// 3Gamma Function Disable 
	sendDATA(0x00); 

	sendCMD(0x26);    	//Gamma curve selected 
	sendDATA(0x01); 

	sendCMD(0xE0);    	//Set Gamma 
	sendDATA(0x0F); 
	sendDATA(0x31); 
	sendDATA(0x2B); 
	sendDATA(0x0C); 
	sendDATA(0x0E); 
	sendDATA(0x08); 
	sendDATA(0x4E); 
	sendDATA(0xF1); 
	sendDATA(0x37); 
	sendDATA(0x07); 
	sendDATA(0x10); 
	sendDATA(0x03); 
	sendDATA(0x0E); 
	sendDATA(0x09); 
	sendDATA(0x00); 

	sendCMD(0XE1);    	//Set Gamma 
	sendDATA(0x00); 
	sendDATA(0x0E); 
	sendDATA(0x14); 
	sendDATA(0x03); 
	sendDATA(0x11); 
	sendDATA(0x07); 
	sendDATA(0x31); 
	sendDATA(0xC1); 
	sendDATA(0x48); 
	sendDATA(0x08); 
	sendDATA(0x0F); 
	sendDATA(0x0C); 
	sendDATA(0x31); 
	sendDATA(0x36); 
	sendDATA(0x0F); 

	sendCMD(0x11);    	//Exit Sleep 
	delay(120); 

	sendCMD(0x29);    //Display on 
	sendCMD(0x2c);   
}

INT8U TFT::readID(void)
{
    INT8U i=0;
    INT8U data[3] ;
    INT8U ID[3] = {0x00, 0x93, 0x41};
    INT8U ToF=1;
    for(i=0;i<3;i++)
    {
        data[i]=readRegister(0xd3,i+1);
        if(data[i] != ID[i])
        {
            ToF=0;
        }
    }
    /*
    if(!ToF)
    {
        Serial.print("Read TFT ID failed, ID should be 0x09341, but read ID = 0x");
        for(i=0;i<3;i++)
        {
            Serial.print(data[i],HEX);
        }
        Serial.println();
    }
    */
    return ToF;
}

void TFT::setCol(INT16U StartCol,INT16U EndCol)
{
    sendCMD(0x2A);                                                      /* Column Command address       */
    sendData(StartCol);
    sendData(EndCol);
}

void TFT::setPage(INT16U StartPage,INT16U EndPage)
{
    sendCMD(0x2B);                                                      /* Column Command address       */
    sendData(StartPage);
    sendData(EndPage);
}

void TFT::fillScreen(INT16U color)
{
    Tft.setCol(0, MAX_X);
    Tft.setPage(0, MAX_Y);
    Tft.sendCMD(0x2c);                                                  /* start to write to display ra */
                                                                        /* m                            */
    TFT_DC_HIGH;
    TFT_CS_LOW;

    INT8U Hcolor = color>>8;
    INT8U Lcolor = color&0xff;
    for(INT16U i=0; i<(MAX_X+1)/2*(MAX_Y+1); i++)
    {
        SPI.transfer(Hcolor);
        SPI.transfer(Lcolor);
        SPI.transfer(Hcolor);
        SPI.transfer(Lcolor);
    }
    TFT_CS_HIGH;
}


void TFT::setXY(INT16U poX, INT16U poY)
{
    setCol(poX, poX);
    setPage(poY, poY);
    sendCMD(0x2c);
}

void TFT::setPixel(INT16U poX, INT16U poY,INT16U color)
{
    setXY(poX, poY);
    sendData(color);
}

void TFT::drawChar( INT8U ascii, INT16U poX, INT16U poY,INT16U size, INT16U fgcolor)
{
    if((ascii>=32)&&(ascii<=127))
    {
        ;
    }
    else
    {
        ascii = '?'-32;
    }
    for (int i =0; i<FONT_X; i++ ) {
        INT8U temp = pgm_read_byte(&simpleFont[ascii-0x20][i]);
        for(INT8U f=0;f<8;f++)
        {
            if((temp>>f)&0x01)
            {
                fillRectangle(poX+i*size, poY+f*size, size, size, fgcolor);
            }

        }

    }
}

void TFT::drawString(char *string,INT16U poX, INT16U poY, INT16U size,INT16U fgcolor)
{
    while(*string)
    {
        drawChar(*string, poX, poY, size, fgcolor);
        *string++;

        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     /* Move cursor right            */
        }
    }
}

void TFT::drawCenteredString(char *string,INT16U poy, INT16U size,INT16U fgcolor)
{
    int len = strlen (string)* FONT_SPACE * size;
    int left = (MAX_X - len ) / 2;
    
    drawString( string, left, poy, size, fgcolor);
}

void TFT::drawStringWithShadow(char *string,INT16U poX, INT16U poY, INT16U size,INT16U fgcolor, INT16U shcolor)
{
    while(*string)
    {
        drawChar(*string, poX-1, poY+1, size, shcolor);
        drawChar(*string, poX, poY, size, fgcolor);
        *string++;

        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     /* Move cursor right            */
        }
    }
}

void TFT::fillRectangle(INT16U poX, INT16U poY, INT16U width, INT16U height, INT16U color)
{

    INT16U XL = poX;
    INT16U XR = poX+width;
    INT16U YU = poY;
    INT16U YD = poY+height;

    unsigned long  XY=0;
    unsigned long i=0;

    if(XL > XR)
    {
        XL = XL^XR;
        XR = XL^XR;
        XL = XL^XR;
    }
    if(YU > YD)
    {
        YU = YU^YD;
        YD = YU^YD;
        YU = YU^YD;
    }
    XL = constrain(XL, MIN_X,MAX_X);
    XR = constrain(XR, MIN_X,MAX_X);
    YU = constrain(YU, MIN_Y,MAX_Y);
    YD = constrain(YD, MIN_Y,MAX_Y);

    XY = (XR-XL+1);
    XY = XY*(YD-YU+1);

    Tft.setCol(XL,XR);
    Tft.setPage(YU, YD);
    Tft.sendCMD(0x2c);                                                  /* start to write to display ra */
                                                                        /* m                            */

    TFT_DC_HIGH;
    TFT_CS_LOW;

    INT8U Hcolor = color>>8;
    INT8U Lcolor = color&0xff;
    for(i=0; i < XY; i++)
    {
        SPI.transfer(Hcolor);
        SPI.transfer(Lcolor);
    }

    TFT_CS_HIGH;
}

void TFT::fillRectangleUseBevel(INT16U x, INT16U y, INT16U w, INT16U h, INT16U color)
{
    INT16U x2 = x + w;
    INT16U y2 = y + h;

    if ( x2 > MAX_X ) x2 = MAX_X;
    if ( y2 > MAX_Y ) y2 = MAX_Y;

    Tft.setCol(x,x2);
    Tft.setPage(y, y2);
    Tft.sendCMD(0x2c);                                                 

    TFT_DC_HIGH;
    TFT_CS_LOW;

    INT8U Hcolor = color>>8;
    INT8U Lcolor = color&0xff;

    int t = ( x2 - x ) * (y2-y);
    
    for(int j=0; j < t; j++)
    {
        SPI.transfer(Hcolor);
        SPI.transfer(Lcolor);
    }

    TFT_CS_HIGH;
}

void  TFT::drawHorizontalLine( INT16U poX, INT16U poY, INT16U length,INT16U color)
{
    setCol(poX,poX + length);
    setPage(poY,poY);
    sendCMD(0x2c);
    for(int i=0; i<length; i++)
    sendData(color);
}

void TFT::drawLine( INT16U x0,INT16U y0,INT16U x1, INT16U y1,INT16U color)
{

    int x = x1-x0;
    int y = y1-y0;
    int dx = abs(x), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;                                                /* error value e_xy             */
    for (;;){                                                           /* loop                         */
        setPixel(x0,y0,color);
        e2 = 2*err;
        if (e2 >= dy) {                                                 /* e_xy+e_x > 0                 */
            if (x0 == x1) break;
            err += dy; x0 += sx;
        }
        if (e2 <= dx) {                                                 /* e_xy+e_y < 0                 */
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }

}

void TFT::drawVerticalLine( INT16U poX, INT16U poY, INT16U length,INT16U color)
{
    setCol(poX,poX);
    setPage(poY,poY+length);
    sendCMD(0x2c);
    for(int i=0; i<length; i++)
    sendData(color);
}

void TFT::drawRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width,INT16U color)
{
    drawHorizontalLine(poX, poY, length, color);
    drawHorizontalLine(poX, poY+width, length, color);
    drawVerticalLine(poX, poY, width,color);
    drawVerticalLine(poX + length, poY, width,color);
}

void TFT::drawRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width,INT16U color, byte thickness)
{
    for (int i = 0; i < thickness - 1; i++)
    {
        drawHorizontalLine(poX + i, poY + i, length - i * 2, color);
        drawHorizontalLine(poX + i, poY + width - i, length -i * 2, color);
        drawVerticalLine(poX + i, poY + i, width -i * 2,color);
        drawVerticalLine(poX + length - i, poY + i, width -i * 2,color);
    }
}

void TFT::drawCircle(int poX, int poY, int r,INT16U color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        setPixel(poX-x, poY+y,color);
        setPixel(poX+x, poY+y,color);
        setPixel(poX+x, poY-y,color);
        setPixel(poX-x, poY-y,color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}

void TFT::fillCircle(int poX, int poY, int r,INT16U color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {

        drawVerticalLine(poX-x, poY-y, 2*y, color);
        drawVerticalLine(poX+x, poY-y, 2*y, color);

        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);

}

void TFT::drawTriangle( int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color)
{
    drawLine(poX1, poY1, poX2, poY2,color);
    drawLine(poX1, poY1, poX3, poY3,color);
    drawLine(poX2, poY2, poX3, poY3,color);
}

INT8U TFT::drawNumber(long long_num,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor)
{
    INT8U char_buffer[10] = "";
    INT8U i = 0;
    INT8U f = 0;

    if (long_num < 0)
    {
        f=1;
        drawChar('-',poX, poY, size, fgcolor);
        long_num = -long_num;
        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     /* Move cursor right            */
        }
    }
    else if (long_num == 0)
    {
        f=1;
        drawChar('0',poX, poY, size, fgcolor);
        return f;
    }

    while (long_num > 0)
    {
        char_buffer[i++] = long_num % 10;
        long_num /= 10;
    }

    f = f+i;
    for(; i > 0; i--)
    {
        drawChar('0'+ char_buffer[i - 1],poX, poY, size, fgcolor);
        if(poX < MAX_X)
        {
            poX+=FONT_SPACE*size;                                       /* Move cursor right            */
        }
    }
    return f;
}

INT8U TFT::drawFloat(float floatNumber,INT8U decimal,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor)
{
    INT16U temp=0;
    float decy=0.0;
    float rounding = 0.5;
    INT8U f=0;
    if(floatNumber<0.0)
    {
        drawChar('-',poX, poY, size, fgcolor);
        floatNumber = -floatNumber;
        if(poX < MAX_X)
        {
            poX+=FONT_SPACE*size;                                       /* Move cursor right            */
        }
        f =1;
    }
    for (INT8U i=0; i<decimal; ++i)
    {
        rounding /= 10.0;
    }
    floatNumber += rounding;

    temp = (INT16U)floatNumber;
    INT8U howlong=drawNumber(temp,poX, poY, size, fgcolor);
    f += howlong;
    if((poX+8*size*howlong) < MAX_X)
    {
        poX+=FONT_SPACE*size*howlong;                                   /* Move cursor right            */
    }

    if(decimal>0)
    {
        drawChar('.',poX, poY, size, fgcolor);
        if(poX < MAX_X)
        {
            poX+=FONT_SPACE*size;                                       /* Move cursor right            */
        }
        f +=1;
    }
    decy = floatNumber-temp;                                            /* decimal part,  4             */
    for(INT8U i=0;i<decimal;i++)                                      
    {
        decy *=10;                                                      /* for the next decimal         */
        temp = decy;                                                    /* get the decimal              */
        drawNumber(temp,poX, poY, size, fgcolor);
        floatNumber = -floatNumber;
        if(poX < MAX_X)
        {
            poX+=FONT_SPACE*size;                                       /* Move cursor right            */
        }
        decy -= temp;
    }
    f +=decimal;
    return f;
}

INT8U TFT::drawFloat(float floatNumber,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor)
{
    INT8U decimal=2;
    INT16U temp=0;
    float decy=0.0;
    float rounding = 0.5;
    INT8U f=0;
    if(floatNumber<0.0)                                                 /* floatNumber < 0              */
    {
        drawChar('-',poX, poY, size, fgcolor);                          /* add a '-'                    */
        floatNumber = -floatNumber;
        if(poX < MAX_X)
        {
            poX+=FONT_SPACE*size;                                       /* Move cursor right            */
        }
        f =1;
    }
    for (INT8U i=0; i<decimal; ++i)
    {
        rounding /= 10.0;
    }
    floatNumber += rounding;

    temp = (INT16U)floatNumber;
    INT8U howlong=drawNumber(temp,poX, poY, size, fgcolor);
    f += howlong;
    if((poX+8*size*howlong) < MAX_X)
    {
        poX+=FONT_SPACE*size*howlong;                                   /* Move cursor right            */
    }


    if(decimal>0)
    {
        drawChar('.',poX, poY, size, fgcolor);
        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     /* Move cursor right            */
        }
        f +=1;
    }
    decy = floatNumber-temp;                                            /* decimal part,                */
    for(INT8U i=0;i<decimal;i++)
    {
        decy *=10;                                                      /* for the next decimal         */
        temp = decy;                                                    /* get the decimal              */
        drawNumber(temp,poX, poY, size, fgcolor);
        floatNumber = -floatNumber;
        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     /* Move cursor right            */
        }
        decy -= temp;
    }
    f += decimal;
    return f;
}

TFT Tft=TFT();
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
