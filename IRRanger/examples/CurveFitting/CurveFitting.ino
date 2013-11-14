/**
 * This example is about the Sharp IR range finders
 * This example is supposed to be used in conjuction with the
 * data_acquisition.py script found here https://github.com/pAIgn10/SharpIRLib
 * As the first step, you're going to take some measurements with your sensor
 * Next, you will be utilize this data for fitting a curve for the
 * particular sensor in your possession
 *
 * Apparently not every sensor has the exact response indicated on the datasheet.
 * So, if you want a bit more accurate measurements, you can follow the instructions
 * on the data_acquisition and curve_fitting scripts to do a curve fitting.
 *
 * Load this code on your arduino, and then go to
 * https://github.com/pAIgn10/SharpIRLib for more details
 */

// Include the IRRanger library
#include "IRRanger.h"

// Pin for sensor's output
int pin = A0;

// Initialize a library instance with the part code of your sensor
// { GP2D120XJ00F, GP2Y0A21YK, GP2Y0A02YK0F } and the input pin
IRRanger ir(GP2D120XJ00F, pin);

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
  // Wait for serial port to connect. Needed for Leonardo only
  while (!Serial) ;
}


void loop()
{
  // If the host computer has sent a byte...
  if (Serial.available())
  {
    Serial.read();
    // take a measurement and send it to the host computer
    Serial.println(ir.getRaw());
    // Wait for sensor to refresh
    delay(50);
  }
}

