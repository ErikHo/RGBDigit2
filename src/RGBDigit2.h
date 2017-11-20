/*  RGBDigitLean class header file
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

#ifndef RGBDigit2_h
#define RGBDigit2_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel


/*
The RGBdigit class is an interface to RGBDigits, a 7 segment display based on NeoPixel
leds (Adafruiit NeoPixel). Multiple RGBDigits can form a display line. Each RGBdigit
contains a string of 8 NeoPixels arranged in the classical 7 segment configuration.
The segments are adressed with a segment parameter 0..7 indicating the segments A..G
and the decimal point P:

         AAA         AAA         AAA         AAA
       F     B     F     B     F     B     F     B
       F     B     F     B     F     B     F     B
         GGG         GGG         GGG         GGG
       E     C     E     C     E     C     E     C
       E     C     E     C     E     C     E     C
         DDD   P     DDD   P     DDD   P     DDD   P

       digit 0     digit 1     digit 2     digit 3

Multiple RGBDigits are adressed with a parameter digit that is zero-based: the first RGBDigit
is 0, second is 1, etc.

This software is a fine tuning of the work of Ralph Cr�tzen 2015 (www.rgbdigit.com). The header
is adapted only slightly. Most software should run on this new class without any modification.
The main reason for thes changes is the reduction of the RAM memory footprint of the class.

Mayor changes with respect to the original version:

- The encoding matrices for alphanumeric characters are changed into a more packed format: 8 bits
  are moved into one byte giving 8 fould smaller memory footprint. Both matrices are also combined
  into a single array. The encoding of special characters is moved into the class code, yielding
  some more free bytes of RAM.

- The array containing the color values for the pixel string has been removed. The underlying
  Adafruit_NeoPixel class already has such an array. The Adafruit implementation is somewhat lossy:
  at lower brightness levels the color values in the array get changed due to truncation effects.
  For the functions in this class this effect is not important. Otherwise one has to refrain from
  changing the display brightness with the setBrightness function.

- Both setDigit methods with char and int parameters are merged into a single method.

- Pixel colors can be specified with red,green,blue triplets and with the packed uint32_t type.
  The latter is handy if you want to use color names.

- The setBrightness and getBrightness are removed because they are already present in the underlying
  NeoPixel class.

*/


class RGBDigit : public Adafruit_NeoPixel {
  public:
    // The constructor of the RGBDigit class.
    // nDigits is the number of digits. pin is the pin number,
    // which defaults to pin 12 if this parameter is omitted.
    RGBDigit(int nDigits, int pin = 12);

    // Initialises RGBDigit:
    void begin();

    // Clear all digits:
    void clearAll();

    // Show a character on digit in color rgb(red,green,blue)
    // If the ascii value of char is between 0 and 15 a hexadecimal
    // symbol 0..F is shown. This of course include 0..9 in decimal.
    // otherwise how character on digit. Valid characters are letters
    // (case insensitive) from a to z, the dot (.), dash (-),
    // underscore (_), brackets ( ( ) { } [ ] ) and space . A special
    // character (3 bars) is used for ascii values not supported.
    // Use an asterisk (*) for the degree sign:
    void setDigit(char x, int digit,  byte red, byte green, byte blue );

    // Show dot on digit in color rgb(red,green,blue):
    void showDot(int digit, byte red, byte green, byte blue);

    // Show segment on digit in color rgb(red,green,blue):
    void segmentOn(int digit, byte segment, byte red, byte green, byte blue);

    //Set the color of all digits to color rgb(red,green,blue),
    // do not change decimal points:
    void setColor(byte red, byte green, byte blue);
    // Set the color of digit to color rgb(red,green,blue),
    // do not change the decimal point:
    void setColor(int digit, byte red, byte green, byte blue);

    // uint32_t versions:
    void setDigit(char x, int digit,  uint32_t c);
    void showDot(int digit, uint32_t c);
    void segmentOn(int digit, byte segment, uint32_t c);
    void setColor(uint32_t c);
    void setColor(int digit, uint32_t c);

    // Clear digit, dot, segment:
    void clearDigit(int digit);
    void clearDot(int digit);
    void segmentOff(int digit, byte segment);

    //Returns true if segment on digit is on. Otherwise, returns false:
    bool isSegmentOn(int digit, byte segment);

  private:
};

#endif
