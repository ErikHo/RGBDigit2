/*  RGBDigit2 class cpp file
    Copyright (C) 2017 Erik Homburg
    Copyright (C) 2015 Ralph Cr�tzen

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

#include "RGBDigit2.h"  

RGBDigit::RGBDigit(int nDigits, int pin)
  : Adafruit_NeoPixel(8 * nDigits, pin, NEO_GRB + NEO_KHZ800){
}

void RGBDigit::begin(){
  Adafruit_NeoPixel::begin();
}

void RGBDigit::clearAll(){
  clear();
  show();
}

void RGBDigit::setDigit(char x, int digit, uint32_t c){
  setDigit( x, digit, byte(c >> 16), byte(c >>8 ), byte(c));
}

void RGBDigit::setDigit(char x, int digit, byte red, byte green, byte blue){
  x = tolower(x);                     // convert to lower case
  byte pattern;
  if((x >= 'a') && (x <='z')){        // get bit pattern for a letter
    pattern = alphaNum[x-int('a')+10];
  }
  else if((x >= '0') && (x <='9')){   // get bit pattern for a digit
    pattern = alphaNum[x-int('0')];
  }
  else if((x >= 0) && (x <=0x0F)){    // direct selection of pattern for 
    pattern = alphaNum[x];            // a (hex) number
  }
  else{                               // special characters        
    switch(x){
    case '.': 
      pattern= B10000000;  //space, '.'
    break;
    case ' ':
      pattern = B00000000;  //space,' '
    break;
    case '-':
      pattern = B01000000;  //minus,'-'
    break;
    case '_':
      pattern = B00001000;  //underscore,'_' 
    break;
    case '{':
    case '[':
    case '(':
      pattern = B00111001;  //leftbracket, '('
    break;
    case '}':
    case ']':
    case ')':
      pattern = B00001111;   //rightbracket,')'
    break;
    case '*':
      pattern = B01100011;   //asterisk,'*', used as degree symbol
    break;
    default:
      pattern = B01001001;   //undefined character = 3 horizontal bars
    break;
    }
  }
  byte bitMask = 1;
  for (int i = 0; i < 8; i++){
    if (pattern & bitMask){
      setPixelColor((digit <<3)+i, red, green, blue);
    }
    else{
      setPixelColor((digit <<3)+i, 0, 0, 0);
    }
    bitMask <<= 1;
  }
  show();
}


void RGBDigit::clearDigit(int digit){
  for (int i = 0; i < 8; i++) {
    setPixelColor((digit << 3) +i, 0, 0, 0);
  }
  show();
}

void RGBDigit::showDot(int digit, byte red, byte green, byte blue){
  setPixelColor((digit << 3) + 7, red, green, blue);
  show();
}

void RGBDigit::showDot(int digit, uint32_t c){
  setPixelColor((digit << 3) + 7, c);
  show();
}

void RGBDigit::clearDot(int digit){
  setPixelColor((digit << 3) + 7, 0, 0, 0);
  show();
}

void RGBDigit::segmentOn(int digit, byte segment, byte red, byte green, byte blue){
  setPixelColor((digit << 3) + segment, red, green, blue);
  show();
}

void RGBDigit::segmentOn(int digit, byte segment, uint32_t c){
  setPixelColor((digit << 3) + segment, c);
  show();
}

void RGBDigit::segmentOff(int digit, byte segment){
  setPixelColor((digit << 3) + segment, 0, 0, 0);
  show();
}

bool RGBDigit::isSegmentOn(int digit, byte segment){
  return (getPixelColor((digit << 3) + segment) != 0);
}

void RGBDigit::setColor(byte red, byte green, byte blue){
  int nDigits = numPixels() << 3;
  for(int digit=0; digit < nDigits; digit++){
    setColor(digit, red, green, blue);
  }
}

void RGBDigit::setColor(uint32_t c){
  int nDigits = numPixels() << 3;
  for(int digit=0; digit < nDigits; digit++){
    setColor(digit, c);
  }
}

void RGBDigit::setColor(int digit, byte red, byte green, byte blue){
  for (int i = 0; i < 7; i++){
    if (getPixelColor(((digit  << 3) + i)) != 0) {
        setPixelColor(((digit  << 3) + i), red, green, blue);
    }
  }
  show();
}

void RGBDigit::setColor(int digit, uint32_t c){
  for (int i = 0; i < 7; i++) {
    if (getPixelColor(((digit  << 3) + i)) != 0) {
        setPixelColor(((digit  << 3) + i), c);
    }
  }
  show();
}

