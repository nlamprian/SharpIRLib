/**
 * An simple example showcasing the functionality of the library
 * The distance reported by the sensor, gets written on the serial port
 * and then sets the duty cycle of the onboard LED
 *
 * Notes:
 * AREF: If your project uses an external voltage reference, then you should
 *       to specify that reference to the IRRanger instance with the setARef method
 * resetARef: Resets the reference to the default internal voltage level
              Please read this first -> http://arduino.cc/en/Reference/AnalogReference
 * Repeated measurements: You can set a number of successive measurements to be made
 *                        and then take their average as the final result. This might be
 *                        desirable since the sensor's output varies a bit.
 *                        Don't overdo it! For every additional measurement, a default
 *                        50ms delay is applied in order for the sensor to refresh.
 * Point of reference: If you want to find the distance of an object, not from
 *                     the sensor, but from another point of reference (perhaps the
 *                     center of your robot), then you can state the distance (in cm)
 *                     of the sensor from that point of interest either during the
 *                     initialization of an instance by supplying a third argument,
 *                     or later with the setPRef method. From thereafter this
 *                     value will be getting added to every measurement you take.
 *                     This has a sensible meaning only when we are taking about
 *                     units of length, and hence it applies only when calling the
 *                     methods getCM and getIN.
 */

#include "IRRanger.h"  // Include the IRRanger library

int led = 13;

int pin = A0;  // Pin for sensor's output

// Initialize a library instance with the part code of your sensor
// { GP2D120XJ00F, GP2Y0A21YK, GP2Y0A02YK0F }, the input pin, and
// the value to be added on every measurement, as a distance of
// the sensor from the point of reference
IRRanger ir(GP2D120XJ00F, pin, 5);

void setup()
{
  Serial.begin(9600);  // Initialize serial port
  while (!Serial) ;  // Wait for serial port to connect. Needed for Leonardo only
  
  pinMode(led,OUTPUT);
}


void loop()
{
  double distance = ir.getCM();  // Get a distance in cm
  double duty_cycle = distance / 70;  // Define an arbitrary ratio
  
  Serial.print(distance);  // Write distance on the serial monitor
  Serial.println("cm");
  digitalWrite(led, HIGH);  // Blink the LED
  delay((int)(duty_cycle * 150));
  digitalWrite(led, LOW);
  delay((int)((1-duty_cycle) * 150));
}

