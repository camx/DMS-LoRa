// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
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

struct { //this structure has to be padded to size of largest data type.
  unsigned int fuelLevelReading;
} measuredData;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  //  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true.
  // Failure to do that will result in extremely low transmit powers.
  //  driver.setTxPower(14, true);
}
void loop()
{
  Serial.println("Sending to rf95_server");
  measuredData.fuelLevelReading = analogRead(FUELGAUGE); //ten bit integer (16 bits)
  rf95.send((char *) &measuredData, sizeof(measuredData));
  char snum[5];
  itoa(sizeof(measuredData), snum, 10);
  Serial.print("Sent ");
  Serial.print(snum);
  Serial.println(" bytes of data");

  rf95.waitPacketSent();
  delay(5000);
}
