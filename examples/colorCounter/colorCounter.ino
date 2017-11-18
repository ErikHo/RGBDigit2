#include <RGBDigit2.h>

//myDigits contains 4 digits and uses data pin 12
#define NUMDIGITS 4
RGBDigit myDigits(NUMDIGITS,12);


// define a 16 color colormap
uint32_t rainbowColors[]{
  0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
  0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
  0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
  0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B
};

// define a 2 color colormap
#define Red 0xFF0000
#define Yellow 0xFFFF00
uint32_t Autumn[]{
  Red,
  Yellow
};


void setup() {
  myDigits.begin();
  myDigits.setBrightness(200);
}


int minCount = -20;
int maxCount =100;
int minVal = -10;
int maxVal = 90;

int t=minCount;


void loop() {
  
  uint32_t colorValue = interpColor(t, minVal, maxVal, rainbowColors, 16);
  // uint32_t colorValue = interpColor(t, minVal, maxVal, Autumn, 2);
  
  char countVal[5];
  
  if (t < minVal){
    strcpy(countVal,"____");  // set te char array to underscores
    writeText(countVal, 0, NUMDIGITS, colorValue); // write to digits
  }
  else if(t > maxVal) {      // write top segments
    myDigits.clearAll();
    for(int i = 0; i < NUMDIGITS; i++){
      myDigits.segmentOn(i, 0, colorValue);
    }
  }
  else{
    char countVal[5];
    sprintf(countVal,"%4d",t);   // print count value to char array
    writeText(countVal, 0, NUMDIGITS, colorValue); // write char array to display
  }
  
  delay(200);
  
  t++;
  if (t>maxCount)
    t = minCount;
    
}


uint32_t interpColor(int x, int xMin, int xMax, uint32_t colorMap[], int colorMapSize){
  
// if x between xMin and xMax a color value is interpolated from the specified colormap
// if x < xMin the first color from the map is returned
// if x > xMax the last value is returned
// colorMapSize is the # of colors in the map

  if(colorMapSize == 1)               // trivial case
    return colorMap[0];
  
  const int N = 255;                  // range scale value
  x = (x - xMin) * N / (xMax - xMin); // rescale x into 0..N
  x = max(0, min(N, x));              // limit x
  
  int colorMapMax = colorMapSize - 1; // max array index
  int xDiv = N / colorMapMax;         // division size in x
  int i = (x / xDiv);                 // division number
    
  if (i > colorMapMax){               // do high values of x
    return colorMap[colorMapMax];
  }
  else{
    long dx = x - i * xDiv;           // interpolate each color separately
    uint32_t r = byte(colorMap[i] >> 16) + 
          dx * (byte(colorMap[i+1] >> 16) - byte(colorMap[i] >> 16)) / xDiv;
    uint32_t g = byte(colorMap[i] >> 8) + 
          dx * (byte(colorMap[i+1] >> 8) - byte(colorMap[i] >> 8)) / xDiv;
    uint32_t b = byte(colorMap[i]) +
          dx * (byte(colorMap[i+1]) - byte(colorMap[i])) / xDiv;
    return (r << 16 | g << 8 | b);     // assemble color value
  };
}

// write a character string to the display
void writeText(char t[], int start, int length, uint32_t c){
  for(int i =0; i < length; i++){
    myDigits.setDigit(t[start + i], i, c);
  }
}


