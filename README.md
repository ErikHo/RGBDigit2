# RGBDigit2
Arduino library for http://rgbdigit.com/

This library is a drop-in replacement for the original RGBDigit library ( Crützen 2015 ). The memory footprint is reduced significantly and colors can also specified with a single 32bit word as defined in the underlying Adafruit_NeoPixel Class. 

## Installation instructions
* Download the zip file
* Extract it to your Arduino library folder
* If needed rename the RGBDigit2-master folder to RGBDigit2
 
You also have to download and install the following libraries:
* Adafruit NeoPixel https://github.com/adafruit/Adafruit_NeoPixel
* Time https://github.com/PaulStoffregen/Time (for the `RGBDigit_example_display.ino` example)

Use the sketches in the examples directory to test the library!

## Class methods
Note that for all *digit* parameters, the first digit has index 0, the second digit has index 1, etc.
The *segment* parameters can be values from 0 to 7, every number corresponding to the following position:

       0
    5     1
       6
    4     2
       3      7

#####```RGBDigit(int nDigits, int pin = 12);```

The constructor of the RGBDigit class. *nDigits* is the number of digits. *pin* is the pin number, which defaults to pin 12 if this parameter is omitted.

#####```void begin();```

Initialises the RGBDigit.

#####```void clearAll();```

Clear all digits.

#####```void setDigit(char character, int digit, byte red, byte green, byte blue);```

#####```void setDigit(char character, int digit, uint32_c);```  
Show *character* on *digit* in color rgb(*red*,*green*,*blue*). Valid characters are letters (case insensitive) from *a* to *z*, the dot (*.*), dash (*-*), underscore (*_*), brackets ( *( ) { } [ ]* ) and space . Use an asterisk (*) for the degree sign. Character values 0..15 are shown as (hexa) decimal characters 0..9; A..F.

#####```void clearDigit(int digit);```
Clear *digit*.

#####```void showDot(int digit, byte red, byte green, byte blue```

#####```void showDot(int digit, uint32_t c)```
Show dot on *digit* in color rgb(*red*,*green*,*blue*). 

#####```void clearDot(int digit);```
Clear dot on *digit*. .

#####```void segmentOn(int digit, byte segment, byte red, byte green, byte blue);```

#####```void segmentOn(int digit, byte segment, uint32_t c);```
Show *segment* on *digit* in color rgb(*red*,*green*,*blue*). 

#####```void segmentOff(int digit, byte segment);```
Clear *segment* on *digit*.

#####```bool isSegmentOn(int digit, byte segment);```
Returns True if *segment* on *digit* is on. Otherwise, returns False.

#####```void setColor(byte red, byte green, byte blue);```

#####```void setColor(uint32_t c);```
Set the color of all digits to color rgb(*red*,*green*,*blue*), digital points are not affected.

#####```void setColor(int digit, byte red, byte green, byte blue);```

#####```void setColor(int digit, uint32_t c);```
Set the color of *digit* to color rgb(*red*,*green*,*blue*), digital points are not affected.

