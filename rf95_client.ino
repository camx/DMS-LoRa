// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.

#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
#define FUELGAUGE PIN_A0
#define BATTERY PIN_A1
#define FUELGAUGE_SUPPLY PIN_A3 //Not sure we neeed this - check whether the supply is decent.

int testVal;
char snum[22];

struct { //this structure has to be padded to size of largest data type.
  unsigned int fuelLevelReading;
} measuredData;

void setup()
{
  analogReference(EXTERNAL);//conect reference voltage to AREF
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
  else  Serial.println("Sending to rf95_client");
}

void loop()
{
  if (Serial.available())
  {
    testVal = Serial.parseInt();
    measuredData.fuelLevelReading = testVal; //ten bit integer (16 bits)
    rf95.send((char *) &measuredData, sizeof(measuredData));
    dtostrf(testVal * 3.33 / 1023, 4, 2, snum); //https://stackoverflow.com/questions/27651012/arduino-sprintf-float-not-formatting
    sprintf(snum, "%s Volts", snum);
    //  sprintf(snum, sizeof(snum), "%f", avgMeasure);
    Serial.println(snum);
    rf95.waitPacketSent();
  }
  delay(2000);
}