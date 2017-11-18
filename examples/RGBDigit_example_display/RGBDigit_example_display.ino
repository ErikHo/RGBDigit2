/*  RGBDigit display example sketch
    Copyright (C) 2015 Ralph Crützen

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

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h> // https://github.com/adafruit/Adafruit_NeoPixel
#include <TimeLib.h> // https://github.com/PaulStoffregen/Time

#include <RGBDigit2.h>

// If necessary, change the number of digits in the next line
#define nDigits 4
RGBDigit rgbDigit(nDigits);       // uses default pin 12
//RGBDigit rgbDigit(nDigits, 6);  // uses another pin; 6 in this example

void setup() {
  setTime(15, 3, 0, 11, 9, 15);
  rgbDigit.begin();
  rgbDigit.clearAll();
}

void loop() {
  showTimeDate();
  wooosh();
}

void showTimeDate() {
  int h = hour();
  int h1 = h/10;                      // left digit
  int h2 = h - (h/10)*10;             // right digit
  rgbDigit.setDigit(h1, 0, 64, 0, 0); // show on digit 0 (=first). Color is rgb(64,0,0).
  rgbDigit.setDigit(h2, 1, 64, 0, 0);
  int m = minute();
  int m1 = m/10;
  int m2 = m - (m/10)*10;
  rgbDigit.setDigit(m1, 2, 0, 0, 64);
  rgbDigit.setDigit(m2, 3, 0, 0, 64);
  rgbDigit.showDot(1, 64, 64, 64);    // show dot on digit 1 (=second). Color is rgb(64,0,0).
  rgbDigit.clearDot(3);               // clear dot on digit 3 (=fourth)
  delay(5000);

  int d = day();
  int d1 = d/10;
  int d2 = d - (d/10)*10;
  rgbDigit.setDigit(d1, 0, 64, 64, 0);
  rgbDigit.setDigit(d2, 1, 64, 64, 0);
  m = month();
  m1 = m/10;
  m2 = m - (m/10)*10;
  rgbDigit.setDigit(m1, 2, 0, 64, 64);
  rgbDigit.setDigit(m2, 3, 0, 64, 64);
  rgbDigit.showDot(1, 64, 64, 64);
  rgbDigit.showDot(3, 64, 64, 64);
  delay(2500);

  int y = year() - 2000;
  int y1 = y/10;
  int y2 = y - (y/10)*10;
  rgbDigit.setDigit(2, 0, 1, 1, 1);
  rgbDigit.setDigit(0, 1, 1, 1, 1);
  rgbDigit.setDigit(y1, 2, 1, 1, 1);
  rgbDigit.setDigit(y2, 3, 1, 1, 1);
  rgbDigit.clearDot(1);
  rgbDigit.clearDot(3);
  fade();
}

void wooosh() {
  for (int d = 0; d < nDigits; d++) {
      rgbDigit.segmentOn(d, 4, 255 - 64*d, 64*d, 0);
      rgbDigit.segmentOn(d, 5, 255 - 64*d, 64*d, 0);
      delay(100);
      rgbDigit.clearDigit(d);
      rgbDigit.segmentOn(d, 0, 255 -64*d, 64*d, 0);
      rgbDigit.segmentOn(d, 3, 255 -64*d, 64*d, 0);
      rgbDigit.segmentOn(d, 6, 255 -64*d, 64*d, 0);
      delay(100);
      rgbDigit.clearDigit(d);
      rgbDigit.segmentOn(d, 1, 255 - 64*d, 64*d, 0);
      rgbDigit.segmentOn(d, 2, 255 - 64*d, 64*d, 0);
      delay(100);
      rgbDigit.clearDigit(d);
    }
}

void fade()
{
  for (int c = 2; c < 32; c++) {
    rgbDigit.setColor(c, 1, 1);
    delay(10);
  }
  for (int c = 2; c < 32; c++) {
    rgbDigit.setColor(31, c, 1);
    delay(10);
  }
  for (int c = 2; c < 32; c++) {
    rgbDigit.setColor(31, 31, c);
    delay(10);
  }
  for (int c = 31; c >= 1; c--) {
    rgbDigit.setColor(31, c, 31);
    delay(10);
  }
  for (int c = 31; c >= 1; c--) {
    rgbDigit.setColor(c, 1, 31);
    delay(10);
  }
  for (int c = 31; c >= 1; c--) {
    rgbDigit.setColor(1, 1, c);
    delay(10);
  }
}

