# Grafici GFX
Grafici GFX is a dataset plotting library for Adafruit GFX graphic libraries.

Ths modular and flexible library allows you to easily plot dataset on any arduino display that supports the Adafruit GFX library.

## Usage

## Documentation
The Grafici GFX library is composed of the following classes and structures 

### DATA

#### DataPoint
This class represents a 3D datapoint with values normalized between 0 and 1. Being GRAFICI-GFX a 2D plotting library, the third dimension is called value and is mostly used to change how a DataPoint is drawn (the color, shape and/or size of the plotted DataPoints should depend on their value field)

Parameters
* `float x` second dimension coordinate of the DataPoint, e.g. time
* `float y` first dimension coordinate of the DataPoint, e.g. sensor reading
* `float value` third dimension coordinate of the DataPoint, e.g. severity
  
#### DataSet
This interface is intended as a proxy between data sources and the plotting functions. This is achieved by implementing a class that converts the specific data source into more generic DataPoints via the DataSet interface.
  
Interface methods
* `Point getPoint(int index)` returns the DataPoin at a given index in the DataSet
* `int size(void)` returns the size of the dataset
* `void refresh()` refresh the dataset whenever the data source changes

Implememnted methods 
* `PointIterator beginIt()` returns a PointIterator pointing at the first element of the dataset
* `PointIterator endIt()` returns an PointIterator pointing at the end of the dataset (the first invalid DataPoint after the last element of the DataSet)


#### PointIterator
This class is a stripped-down implementation of C++ iterators intended to run on Arduino.
Use the PointIterator constructor to create an iterator for a class implementing the DataSet interface.
The operators supported by a PointIterator instance are *, ++, !=, =

### VIZ

#### Pixel
	Pixel(void);
	Pixel(float x, float y);
	Pixel(float x, float y, Color color);

	Pixel &setColor(Color color);
	Pixel &setColor(float value, Gradient gradient);

	Pixel &darkerColor(float percentage);

	Pixel &operator+=(const Pixel &b);
	Pixel &operator-=(const Pixel &b);

	float x;
	float y;
	Color color;
  
### Color
This structure represent a color in the classic RGB format. 

* `unsigned char red` red component of the color. Range from 0 to 255.
* `unsigned char green` green component of the color. Range from 0 to 255.
* `unsigned char blue` blue component of the color. Range from 0 to 255.

### ColorScheme
This structure describe a color theme that will be used by the Grafici GFX library. Different color schemes are available in the colorScheme directory of the library.

* `Color *colors` ordered Color sequence, i.e. gradient, used to rappresent differnt Point values. For example, if a Point has value 0, it will be drawn using the first Color of this list. If a Point has value 1, it will be drawn using the last Color of this list.
* `int size` size of the Color sequence
* `Color *lineColor` Color used to draw lines 
* `Color *markerColor` Color used to draw markers
* `Color *fillColor` Color used to fill shapes
* `Color *bkgColor` Color used as background

Driver

Widget

Object oriented patterns and concepts:

Visitors

Decorators
