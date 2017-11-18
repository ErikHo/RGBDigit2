/*  RGBDigit text example sketch
    Copyright (C) 2017 Erik Homburg

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

#include <RGBDigit2.h>

// some HTML color definitions
#define  rgb_Tomato                 0xFF6347
#define  rgb_Gold                   0xFFD700
#define  rgb_Violet                 0xEE82EE
#define  rgb_Indigo                 0x4B0082
#define  rgb_Blue                   0x0000FF  
#define  rgb_Green                  0x008000
#define  rgb_Yellow                 0xFFFF00
#define  rgb_Orange                 0xFFA500
#define  rgb_Red                    0xFF0000


#define NDIGITS 4
RGBDigit myDigits(NDIGITS, 12);   // use 4 digits and pin 12

// all characters, note that an "&"" is not valid
char allChars[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                   'A','B','C','D','E','F','G','H','I','J',
                   'K','L','K','M','N','O','P','Q','R','S',
                   'T','U','V','W','X','Y','Z','&',
                   '0','1','2','3','4','5','6','7','8','9',
                   '&','&',' ','.','-','_','(',')','*','&'};
int allCharSize = 64;

void setup() {
  //Serial.begin(9600);
  
  myDigits.begin();
  myDigits.clearAll();
  
  if (myDigits.getBrightness() < 255){
    myDigits.setBrightness(255);
  }
}

void loop() {

  // Show all characters, select color specification method 
  // r,g,b (color white) or uint_c (color rgb_Gold) randomly.
  
  for (int i = 0; i < allCharSize; i = i+4){
    for(int j = 0; j < 4; j++){
      if (random(2)){
        myDigits.setDigit(allChars[i+j],j,128,128,128);
      }
      else{
        myDigits.setDigit(allChars[i+j],j,rgb_Gold);
      }
    }
    delay(250);
  }
  delay(1000);

  // Show a dot using the two possible formats
  myDigits.clearAll();
  myDigits.showDot(0, 255, 0, 0);
  myDigits.showDot(1, 0xFF0000);
  myDigits.showDot(2, rgb_Red);
  delay(1000);
  // Clear the dots
  myDigits.clearDot(0);
  myDigits.clearDot(1);
  myDigits.clearDot(2);
  delay(1000);

  // Display a number
  char pi[4] = "3142";
  for(int i =0; i < 4; i++){
      myDigits.setDigit(pi[i],i, rgb_Violet);
  }
  myDigits.showDot(0, rgb_Violet);
  delay(1000);
  
  // Set first and last digit to red
  myDigits.setColor(0,128,0,0);
  myDigits.setColor(3,rgb_Red);
  delay(1000);
  
  // show the number again
  for(int i =0; i < 4; i++){
      myDigits.setDigit(pi[i],i, rgb_Violet);
  };
  myDigits.showDot(0, rgb_Violet);
  delay(1000);
  
  // Set all digits to red
  myDigits.setColor(rgb_Red);
  delay(1000);
  
  // show the number again
  for(int i = 0; i < 4; i++){
      myDigits.setDigit(pi[i],i, rgb_Violet);
  };
  myDigits.showDot(0, rgb_Violet);
  delay(1000);
  
  // If a segment is lit, change segment to blue, otherwise set to dark orange
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 8; j++){
      if(myDigits.isSegmentOn(i,j)){
        myDigits.segmentOn(i,j, rgb_Blue);
      }
      else{
        myDigits.segmentOn(i,j, 38, 18, 0);
      }
    }
  }
  delay(1000);
  
}
