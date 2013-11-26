SharpIRLib
==========

This is an Arduino library for interfacing Sharp IR range finders.
Currently there are three models supported,
[GP2D120XJ00F](https://www.sparkfun.com/products/8959), 
[GP2Y0A21YK](https://www.sparkfun.com/products/242), 
[GP2Y0A02YK0F](https://www.sparkfun.com/products/8958).
Their transfer functions have been extracted from the datasheets, 
by fitting a model on a series of datapoints. These collections of data
are present for reference in the `curve_fitting` folder.


Curve Fitting
-------------
Apparently, not all units have the same response characteristic. So, I have also implemented a process to extract such a characteristic for your own sensor.

![Curve Fitting](http://i859.photobucket.com/albums/ab154/lampnick67/Untitled-1_zps00e26b29.png)

In the `curve_fitting` folder:
* There is a Python script `data_acquisition.py`, accompanied by an Arduino sketch `CurveFitting`, so as those two together, and with a little bit of your help, they are going to take some measurements, do a bit of processing, and put the data in a file `datapoints.csv`.
* Next, there is a Python script `curve_fitting.py` and a MATLAB script `curve_fitting.m`, and you can use either one (it's up to you which one), to fit a model to the data, evaluate the results, and compare the estimated model with the one from the datasheet.
You can find more details on the headers of the corresponding files.

It's not neccessary to execute this process, it might be that your sensor is already working pretty well. But if you think you need that extra accuracy for your project, now you can have it out of the box.


Basic Functionality
-------------------
* Get values from the sensor in `raw` form, in `volts`, and in units of length (`cm`, `in`).
* Set a model of your choice for the sensor (Sum of exponentials, 5th order polynomial.
* Set/Reset the voltage reference for the sensor's output measurement.
* Take multiple measurements that are averaged, in order to cancel out some of the sensor's output fluctuation.
* Set a point of reference for the sensor's measurements. You can measure the distance of an object from a point (on the same axis) other than the sensor's position.
* Operate the sensor in discrete mode by providing a threshold for the distances of objects.

Examples
--------
There is one sketch for the curve fitting process, `CurveFitting`, and two additional example sketches, `DistanceFromObject` and `StayAway`, that expose some of the interface and functionality of the library.
