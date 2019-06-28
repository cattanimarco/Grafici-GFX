# Grafici GFX
Grafici GFX is a dataset plotting library for Adafruit GFX graphic libraries.

Ths modular and flexible library allows you to easily plot dataset on any arduino display that supports the Adafruit GFX library.

## Usage

## Documentation
The Grafici GFX library is composed of the following classes and structures 

### DATA

#### Point

#### Dataset
This class is intended as an interface to uniform the dataset provided as source of the plotting library. Thus, datasets can only be plotted via a class implementing the Dataset class.
  
Class implementing the Dataset interface must provide the follwing methods:
* `Point getPoint(int index)` returns the dataset point at a given index
* `int size(void)` returns the size of the dataset
* `void refresh()` refresh the dataset whenever the data source changes

These methos are already implememnted 
* `PointIterator beginIt()` returns an iterator pointing at the first element of the dataset
* `PointIterator endIt()` returns an iterator pointing at the end of the dataset (invalid dataset point)


#### PointIterator
This class is a stripped-down implementation of C++ iterators intended to run on Arduino.
Use the PointIterator constructor to create an iterator for a class implementing the Dataset interface.
The operators supported by a PointIterator instance are *, ++, !=, =

### VIEW

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
