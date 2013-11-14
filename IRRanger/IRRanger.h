/**
 * Name: IRRanger
 * Author: Nick Lamprianidis (lampnick67@yahoo.com)
 * Version: 1.0
 * Description: A library for interfacing the Sharp IR range finders
 * License: Copyright (c) 2013 Nick Lamprianidis 
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: IRRanger.h
 * File description: Definitions and methods for the IRRanger library
 */

#include <Arduino.h>

#ifndef IRRanger_h
#define IRRanger_h

// In case of use of repeated measurements, NEXT_MEAS_DELAY is the number of
// milliseconds between two successive measurements
#define NEXT_MEAS_DELAY 50  // This is a constraint of the sensor
// Consider the resolution of your A/D Converter, and set its max value
#define AD_MAX_VALUE 1023.  // 10bit A/D Converter

// Part code
enum ir_ranger {
                 GP2D120XJ00F,  // Valid for a range from 3cm to 30cm
                 GP2Y0A21YK,    // Valid for a range from 6cm to 80cm
                 GP2Y0A02YK0F   // Valid for a range from 15cm to 150cm
               };

// a*exp(b*x) + c*exp(d*x)
#define model_GP2D120XJ00F(v) ( ( 75.59 * exp( -3.877 * v ) + 21.31 * exp( -0.6346 * v ) ) + _p_ref )
// a*exp(b*x) + c*exp(d*x)
#define model_GP2Y0A21YK(v) ( ( 223.9 * exp( -4.307 * v ) + 49.65 * exp( -0.7061 * v ) ) + _p_ref )
// a*x^5 + b*x^4 + c*x^3 + d*x^2 + e*x + f
#define model_GP2Y0A02YK0F(v) ( ( v * ( v * ( v * ( v * ( -15.01 * v + 136.9 ) - 495 ) + 896.9 ) - 846.8 ) + 385.7 ) + _p_ref )

// Class for interfacing the Sharp IR range finders
class IRRanger {
public:
    IRRanger(ir_ranger code, uint8_t pin);
    IRRanger(ir_ranger code, uint8_t pin, double p_ref);
    void setARef(double a_ref);
    void resetARef();
    void setPRef(double p_ref);
    void setRepeat(uint8_t repeat);
    void setThreshold(double threshold);
    int getRaw();
    double getV();
    double getCM();
    double getIN();
    double raw2CM(int value);
    double raw2IN(int value);
    boolean isClose();
    boolean isFar();

private:
    ir_ranger _code;    // Sensor's part code
    int _pin;           // Input pin
    double _a_ref;      // Voltage reference level
    double _p_ref;      // Distance (in cm) of the sensor from the point of reference
                        //   for the sensor's measurements
    uint8_t _repeat;    // Number of measurements per request for the sensor's output
    double _threshold;  // Threshold (in cm) for identifying whether an object is close or far
    double v2CM(double v);
};

#endif // IRRanger