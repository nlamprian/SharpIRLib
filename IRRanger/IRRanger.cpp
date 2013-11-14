/**
 * Name: IRRanger
 * Author: Nick Lamprianidis (lampnick67@yahoo.com)
 * Version: 1.0
 * Description: A library for interfacing the Sharp IR range finders
 * License: Copyright (c) 2013 Nick Lamprianidis 
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: IRRanger.cpp
 * File description: Implementation of methods for the IRRanger library
 */

#include "IRRanger.h"

// Initializes an IRRanger instance with input the sensor's part code
// and the analog pin that the sensor is connected to
IRRanger::IRRanger(ir_ranger code, uint8_t pin)
{
	_code = code;
	_pin = pin;
	_a_ref = 5.0;
	_p_ref = 0.0;
	_repeat = 1;
	_threshold = 0.0;
}

// Same as the constructor above, but with an additional
//   input a value (*) to be added on every measurement
// * Valid only upon requesting a measurement in cm
IRRanger::IRRanger(ir_ranger code, uint8_t pin, double p_ref)
{
	_code = code;
	_pin = pin;
	_a_ref = 5.0;
	_p_ref = p_ref;
	_repeat = 1;
	_threshold = 0.0;
}

// Sets and utilizes the voltage level on the AREF pin
// Read this http://arduino.cc/en/Reference/AnalogReference before using the AREF pin
void IRRanger::setARef(double a_ref)
{
	analogReference(EXTERNAL);
	_a_ref = a_ref;
}

// Resets the reference to the default internally generated voltage level
// Use with Caution: Possible damage of the microcontroller
// Read this http://arduino.cc/en/Reference/AnalogReference
void IRRanger::resetARef()
{
	analogReference(DEFAULT);
	_a_ref = 5.0;
}

// Sets a value to be added on every measurement in cm
// Use: If you want to find the distance of an object, not from the sensor,
//      but from another point of reference (perhaps the center of a robot),
//      then you need state the distance of the sensor from that point of interest
void IRRanger::setPRef(double p_ref)
{
	_p_ref = p_ref;
}

// Sets the number of measurements to be averaged per request for the sensor's output
// Use: Don't overdo it. Every additional measurement will take NEXT_MEAS_DELAY ms (default is 50)
void IRRanger::setRepeat(uint8_t repeat)
{
	_repeat = repeat;
}

// Sets a threshold (in cm) for identifying whether an object is close or far
void IRRanger::setThreshold(double threshold)
{
	_threshold = threshold;
}

// Returns the raw value from the A/D converter
// If _repeat was set to > 1, an average of #(_repeat) measurements will be returned
int IRRanger::getRaw()
{
	if (_repeat == 1)
		return analogRead(_pin);

	int sum = 0;
	for (int i = 0; i < _repeat; ++i)
	{
		sum += analogRead(_pin);
		delay(NEXT_MEAS_DELAY);
	}
	return sum / _repeat;
}

// Returns the output voltage of the sensor
// Of course, this value is the one after discretization
double IRRanger::getV()
{
	int value = _repeat == 1 ? analogRead(_pin) : getRaw();
	return _a_ref * ( value / AD_MAX_VALUE );
}

// Returns the distance (in cm) of an object from the sensor, or if _p_ref was set
// this distance will be from the point of reference (_p_ref adds upon the immediate result)
double IRRanger::getCM()
{
	double v = getV();
	return v2CM(v);
}

// Same as getCM, but now the unit of length is inches
double IRRanger::getIN()
{
	return getCM() * 0.393701;
}

// Translates a raw value to cm
// Use: In conjunction with getRaw, to avoid adding _p_ref to the measurement
double IRRanger::raw2CM(int value)
{
	double v = _a_ref * ( value / AD_MAX_VALUE );
	double tmp = _p_ref;
	_p_ref = 0;
	double v_cm = v2CM(v);
	_p_ref = tmp;
	return v_cm;
}

// Translates a raw value to inches
// Use: See raw2CM
double IRRanger::raw2IN(int value)
{
	return raw2CM(value) * 0.393701;
}

// Translates volts to cm
double IRRanger::v2CM(double v)
{
	switch(_code)
	{
		case GP2D120XJ00F:
			return model_GP2D120XJ00F(v);
		case GP2Y0A21YK:
			return model_GP2Y0A21YK(v);
		case GP2Y0A02YK0F:
			return model_GP2Y0A02YK0F(v);
	}
}

// Checks whether an object is close (distance <= threshold)
boolean IRRanger::isClose()
{
	return getCM() > _threshold ? false : true;
}

// Checks whether an object is far (distance > threshold)
boolean IRRanger::isFar()
{
	return getCM() > _threshold ? true : false;
}
