#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

void setup(){}

void loop()
{
  int k;
  uint8_t data[4];
  display.setBrightness(0x0f);

  data[0] = display.encodeDigit(4);
  data[1] = display.encodeDigit(5);
  data[2] = display.encodeDigit(6);
  data[3] = display.encodeDigit(7);
  display.setSegments(data);

  delay(3000);

  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);

  delay(3000);
 
}
