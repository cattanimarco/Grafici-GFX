# Grafici GFX
Grafici GFX is a dataset plotting library for Adafruit GFX graphic libraries.

Ths modular and flexible library allows you to easily plot dataset on any arduino display that supports the Adafruit GFX library.

## Usage

## Documentation
The Grafici GFX library is composed of the following libraries 

### MODEL

#### Point

#### Dataset
This class is intended as an interface to uniform the dataset provided as source of the plotting library. Thus, datasets can only be plotted via a class implementing the Dataset class.
  
Class implementing the Dataset interface must provide the follwing methods:
* Point getPoint(int index): return the dataset point at a given index
* int size(void): return the size of the dataset
* void refresh(): needs to be called every time dataset points change

These methos are already implememnted 
* PointIterator beginIt() return an iterator pointing at the first element of the dataset
* PointIterator endIt() return an iterator pointing at the end of the dataset (invalid dataset point)


#### PointIterator
This class is a stripped-down implementation of C++ iterators intended to run on Arduino.
Use the PointIterator constructor to create an iterator for a class implementing the Dataset interface.
The operators supported by a PointIterator instance are *, ++, !=, =

### VIEW
Colors

Driver

Widget

Object oriented patterns and concepts:

Visitors

Decorators
