//
// This sketch uses Rob Tillaart's MATRIX7219 library to drive the
//  MAX7219 IC's used to control the 8x8 dot matrix displays.
//
//  https://github.com/RobTillaart/MATRIX7219
//
// The library is published under the following license:
//
// MIT License
//
// Copyright (c) 2023-2023 Rob Tillaart
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


// This sketch was written by Roy van der Kraan
// It is released under the same license as the library/libraries it is using.

#include "MATRIX7219.h"

#define dataPin  4
#define latchPin 9
#define clockPin 8

#define minusPin A0

#define dotMatrixCSPin    7
#define dotMatrixDataPin  6
#define dotMatrixClockPin 5
#define dotMatrixCount    3

MATRIX7219 dotMatrix(dotMatrixDataPin, dotMatrixCSPin, dotMatrixClockPin, dotMatrixCount);

const uint8_t sevenSeg[] = {
  B00010100, // 0
  B00111111, // 1
  B10011000, // 2
  B00011010, // 3
  B00110011, // 4
  B01010010, // 5
  B01010000, // 6
  B00011111, // 7
  B00010000, // 8
  B00010010, // 9
  B11111011, // -
  B11111111  // space
};

const uint8_t decPoint[3][3] = {
  {239, 255, 255},
  {255, 239, 255},
  {255, 255, 239}
};

const uint8_t letter1[][8] = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // space
  { B00000000, B00000000, B01110000, B01001000, B01001000, B01110000, B01000000, B01000000 }, // p
  { B00000000, B00000000, B01110000, B01001000, B01001000, B01001000, B01001000, B00000000 }, // n
  { B00000000, B00000000, B10010000, B10010000, B10010000, B11101000, B10000000, B10000000 }, // µ
  { B00000000, B00000000, B11010000, B10101000, B10101000, B10101000, B10101000, B00000000 }, // m
  { B01000000, B01000000, B01001000, B01010000, B01100000, B01010000, B01001000, B00000000 }, // k
  { B10001000, B11011000, B10101000, B10001000, B10001000, B10001000, B10001000, B00000000 }, // M
  { B01110000, B10001000, B10000000, B10111000, B10001000, B10001000, B01110000, B00000000 }  // G  
};

const uint8_t letter2a[][8] = {
  { B00000010, B00000010, B00000010, B00000010, B00000010, B00000001, B00000000, B00000000 }, // V
  { B00000000, B00000001, B00000010, B00000010, B00000011, B00000010, B00000010, B00000000 }, // A
  { B00000000, B00000000, B00000001, B00000010, B00000001, B00000000, B00000011, B00000000 }, // s
  { B00000010, B00000010, B00000010, B00000011, B00000010, B00000010, B00000010, B00000000 }, // Hz
  { B00000001, B00000010, B00000010, B00000010, B00000010, B00000001, B00000011, B00000000 }, // Ω
  { B00000011, B00000010, B00000010, B00000011, B00000010, B00000010, B00000010, B00000000 }, // F
  { B00000000, B01000000, B11110011, B01000100, B01000111, B01000100, B00110011, B00000000 }, // temp
  { B00000000, B00000000, B00111000, B01000100, B01111000, B01000000, B00111100, B00000000 }  // error
};

const uint8_t letter2b[][8] = {
  { B00100000, B00100000, B00100000, B00100000, B00100000, B01000000, B10000000, B00000000 }, // V
  { B10000000, B01000000, B00100000, B00100000, B11100000, B00100000, B00100000, B00000000 }, // A
  { B00000000, B00000000, B10000000, B00000000, B10000000, B01000000, B10000000, B00000000 }, // s
  { B00100000, B00100000, B00101111, B11100001, B00100010, B00100100, B00101111, B00000000 }, // Hz
  { B11000000, B00100000, B00100000, B00100000, B00100000, B01000000, B01100000, B00000000 }, // Ω
  { B11100000, B00000000, B00000000, B11000000, B00000000, B00000000, B00000000, B00000000 }, // F
  { B00000000, B00000000, B10011101, B01010010, B10010010, B00010010, B11010010, B00000000 }, // temp
  { B00000000, B00000000, B01110001, B10000010, B10000010, B10000010, B10000010, B00000000 }  // error
};

const uint8_t letter2c[][8] = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // V
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // A
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // s
  { B00000000, B00000000, B10000000, B00000000, B00000000, B00000000, B10000000, B00000000 }, // Hz
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // Ω
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // F
  { B00000000, B00000000, B10011110, B01010001, B01010001, B01011110, B01010000, B00010000 }, // temp
  { B00000000, B00000000, B11000000, B00000000, B00000000, B00000000, B00010101, B00000000 }  // error
};

const uint8_t acdca[][8] = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // space
  { B00000000, B00000000, B00000000, B00000000, B00000001, B00000001, B00000001, B00000001 }, // AC
  { B00000000, B00000000, B00000000, B00000001, B00000001, B00000001, B00000001, B00000001 }  // DC
};

const uint8_t acdcb[][8] = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }, // space
  { B00000000, B00000000, B00000000, B11000111, B00101000, B11101000, B00101000, B00100111 }, // AC
  { B00000000, B00000000, B00000000, B11000111, B00101000, B00101000, B00101000, B11000111 }  // DC
};

const String Unit[] = { "V", "A", "s", "Hz", "Ω", "F", "temp", "error" };

uint8_t multiplier = 0;


void setup() {
  // Serial.begin(115200);     // Setup main UART (on USB)
  Serial1.begin(115200);       // Setup UART to device
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(minusPin,OUTPUT);
  digitalWrite(latchPin, LOW);
  show_dashes();
  dotMatrix.begin();
  dotMatrix.clear();
  dotMatrix.setBrightness(1);
  delay(500);
}


void loop() {
  String func=readSetting();
  // Serial.print("Function  : ");
  // Serial.println(func);
  String meas=get_value();
  // Serial.print("Value     : ");
  // Serial.println(meas);
  display(meas,func);
  delay(500);
}


void display(String _val, String _func) {
  uint8_t acdc = 0;
  uint8_t unit = 0;
  if      ( _func == "\"VOLT\"")    { unit = 0; acdc = 2; }
  else if ( _func == "\"VOLT AC\"") { unit = 0; acdc = 1; }
  else if ( _func == "\"CURR\"")    { unit = 1; acdc = 2; }
  else if ( _func == "\"CURR AC\"") { unit = 1; acdc = 1; }
  else if ( _func == "\"RES\"")       unit = 4;
  else if ( _func == "\"FRES\"")      unit = 4;
  else if ( _func == "\"DIOD\"")      unit = 4;             // Owon Bug: response shoud be "CONT"
  else if ( _func == "\"CONT\"")      unit = 0;             // Owon Bug: response shoud be "DIOD"
  else if ( _func == "\"CAP\"")       unit = 5;
  else if ( _func == "\"FREQ\"")      unit = 3;
  else if ( _func == "\"PER\"")       unit = 2;
  else if ( _func == "\"TEMP\"")      unit = 6;             // "temp"
  else                                unit = 7;             // "error"

  // Check if value is negative or not and remove "-" from string if so:
  bool _neg = false;
  if (_val.startsWith("-")) {
    _neg = true;
    _val = _val.substring(1);
  }

  // Determine the exponent and remove exponent from string:
  int _EPos = _val.indexOf('E');
  String _exponent = _val.substring(_EPos+1);
  _val = _val.substring(0,_EPos);

  // Determine the location of the decimal point/comma:
  byte _dec = 0;
  
  if      ( _exponent == "+00" ) { multiplier = 0; _dec = 0; }
  else if ( _exponent == "+01" ) { multiplier = 0; _dec = 1; }
  else if ( _exponent == "+02" ) { multiplier = 0; _dec = 2; }

  else if ( _exponent == "-10" ) { multiplier = 1; _dec = 2; }
  else if ( _exponent == "-11" ) { multiplier = 1; _dec = 1; }
  else if ( _exponent == "-12" ) { multiplier = 1; _dec = 0; }

  else if ( _exponent == "-07" ) { multiplier = 2; _dec = 2; }
  else if ( _exponent == "-08" ) { multiplier = 2; _dec = 1; }
  else if ( _exponent == "-09" ) { multiplier = 2; _dec = 0; }

  else if ( _exponent == "-04" ) { multiplier = 3; _dec = 2; }
  else if ( _exponent == "-05" ) { multiplier = 3; _dec = 1; }
  else if ( _exponent == "-06" ) { multiplier = 3; _dec = 0; }

  else if ( _exponent == "-01" ) { multiplier = 4; _dec = 2; }
  else if ( _exponent == "-02" ) { multiplier = 4; _dec = 1; }
  else if ( _exponent == "-03" ) { multiplier = 4; _dec = 0; }

  else if ( _exponent == "+03" ) { multiplier = 5; _dec = 0; }
  else if ( _exponent == "+04" ) { multiplier = 5; _dec = 1; }
  else if ( _exponent == "+05" ) { multiplier = 5; _dec = 2; }

  else if ( _exponent == "+06" ) { multiplier = 6; _dec = 0; }
  else if ( _exponent == "+07" ) { multiplier = 6; _dec = 1; }
  else if ( _exponent == "+08" ) { multiplier = 6; _dec = 2; }

  else if ( _exponent == "+09" ) { multiplier = 7; _dec = 0; }
  else if ( _exponent == "+10" ) { multiplier = 7; _dec = 1; }
  else if ( _exponent == "+11" ) { multiplier = 7; _dec = 2; }

  if ( unit > 5 ) { multiplier = 0; _dec = 0; }

  if (_neg) digitalWrite(minusPin, LOW);   // Display "-" if value is negative:
  else      digitalWrite(minusPin, HIGH);  //  else, don't


  // Using 74*595 shift registers for 7-segment displays
  //  (because my displays have two leds per segment and
  //   MAX7219 doesn't work properly with these) 

  writeSevenSeg(_val, _dec);               // Write value to 7-segment display
  writeDotMatrix(multiplier, unit, acdc);  // Write multiplier, unit, AC/DC to dot matrix display
}


String get_value() {
  String response = "";           // Start with empty variable
  Serial1.println("MEAS1?");      // Request last measured value
  delay(50);                      // Wait
  while (Serial1.available()) {   // Get the entire response
    char c = Serial1.read();
    response += c;
  }
  response.trim();                // Strip leading and trailing spaces, CR's
  return (response);
}

String readSetting() {
  String response = "";           // Start with empty variable
  Serial1.println("FUNC?");       // Request current measuring function
  delay(50);                      // Wait
  while (Serial1.available()) {   // Get the entire response
    char c = Serial1.read();
    response += c;
  }
  response.trim();                // Strip leading and trailing spaces, CR's
  return (response);  
}

void show_dashes() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[10]);
  digitalWrite(latchPin, HIGH);
}

void writeSevenSeg(String _value, uint8_t _decimal) {
  digitalWrite(latchPin, LOW);    // Start writing out to the shift registers:
  // Write out the digits to the display. The decimal point/comma is "ANDed":
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[byte(_value.substring(0,1).toInt())] & decPoint[0][_decimal]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[byte(_value.substring(2,3).toInt())] & decPoint[1][_decimal]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[byte(_value.substring(3,4).toInt())] & decPoint[2][_decimal]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[byte(_value.substring(4,5).toInt())]);
  shiftOut(dataPin, clockPin, MSBFIRST, sevenSeg[byte(_value.substring(5,6).toInt())]);
  digitalWrite(latchPin, HIGH);   // Show the value
}

void writeDotMatrix(uint8_t a, uint8_t b, uint8_t c) {
  for (int n = 0; n < 8; n++) {
    dotMatrix.setRow(n+1, (letter1[a][n]  | letter2a[b][n]), 3);
    dotMatrix.setRow(n+1, (letter2b[b][n] | acdca[c][n])   , 2);
    dotMatrix.setRow(n+1, (letter2c[b][n] | acdcb[c][n])   , 1);
  }
}
