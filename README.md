# Grafici GFX
Grafici GFX is a dataset plotting library for Adafruit GFX graphic libraries.

Ths modular and flexible library allows you to easily plot dataset on any arduino display that supports the Adafruit GFX library.

## Usage

### line plot
 
### bar plot
 
### scatter plot
 
### spline plot
 
### histogram plot
 
### multiple plots overlaid
 
### multiplot on different areas
 
### circular plot
 
### mirror plot


## Documentation
The Grafici GFX library is composed of the following classes and structures 

### Data.h

#### DataPoint
This class represents a 3D datapoint with values normalized between 0 and 1. Being GRAFICI-GFX a 2D plotting library, the third dimension is called value and is mostly used to change how a DataPoint is drawn (the color, shape and/or size of the plotted DataPoints should depend on their value field)

Implemented methods
* `DataPoint(void)` initialize a datapoint with x = y = 0.0 and value = 1.0
* `DataPoint(float x, float y)` inizialize a DataPoint with given x and y and value = 1.0

Parameters
* `float x` second dimension coordinate of the DataPoint, e.g. time. It ranges from 0.0 to 1.0
* `float y` first dimension coordinate of the DataPoint, e.g. sensor reading. it ranges from 0.0 to 1.0
* `float value` third dimension coordinate of the DataPoint, e.g. severity. It ranges from 0.0 to 1.0

#### DataSet
This interface is intended as a proxy between data sources and the plotting functions. This is achieved by implementing a class that converts the specific data source into more generic DataPoints via the DataSet interface.
  
Interface methods
* `DataPoint getDataPoint(int index)` returns the DataPointPoin at a given index in the DataSet
* `int size(void)` returns the size of the dataset
* `void refresh()` refresh the dataset whenever the data source changes

Implememnted methods 
* `DataPointIterator beginIt()` returns a DataPointIterator pointing at the first element of the dataset
* `DataPointIterator endIt()` returns an DataPointIterator pointing at the end of the dataset (the first invalid DataPoint after the last element of the DataSet)

#### DataPointIterator
This class is a stripped-down implementation of C++ iterators intended to run on Arduino.
Use the DataPointIterator constructor to create an iterator for a class implementing the DataSet interface.
The operators supported by a DataPointIterator instance are `*`, `++`, `!=`, `=`

### Display.h

#### Color
This class represent a color in the classic RGB format. 

Parameters
* `unsigned char red` red component of the color. It ranges from 0 to 255
* `unsigned char green` green component of the color. It ranges from 0 to 255
* `unsigned char blue` blue component of the color. It ranges from 0 to 255

#### ColorScheme
This class describes a color scheme that will be used by the Grafici GFX library.

Parameters
* `Color *colors` ordered Color sequence, i.e. gradient, used to rappresent differnt DataPoint values. For example, if a DataPoint has value 0, it will be drawn using the first Color of this list. If a DataPoint has value 1, it will be drawn using the last Color of this list.
* `int size` size of the Color sequence
* `Color *lineColor` Color used to draw lines 
* `Color *markerColor` Color used to draw markers
* `Color *fillColor` Color used to fill shapes
* `Color *bkgColor` Color used as background

Implementations (in the colorschemes directory of the library)
* `colorSchemeHeat` classic heat colors ranging from white to orange, red, dark red, and black. These colors are good also for greyscale monitors

#### Pixel
This class represent a pixel on the 2D screen. Note that changing values to a Pixel color does not result in a change on the display. In order to be drawn, the Pixel class must be passed to a function of the DisplayDriver class.
The operators supported by a DataPointIterator instance are `+=` and `-=`.

Implemented methods 
* `Pixel(void)`
* `Pixel(float x, float y)`
* `Pixel(float x, float y, Color color)`
* `Pixel &setColor(Color color)` set the color of the pixel to a specific value. It returns a reference to the color itself
* `Pixel &setColor(float value, Color * colors, int size)` set the color of the pixel given a value between 0.0 and 1.0, e.g. the value of a DataPoint and an array of Color with specific size, e.g. the colors and size parameters of a ColorScheme object.  It returns a reference to the color itself
* `Pixel &fadeColor(float percentage, Color * otherColor)`

Parameters
* `unsigned int x` horizontal position of the pixel. It ranges from 0 (left side of the display) to the display width (right side of the display)
* `unsigned int y` vertical position of the pixel. It ranges from 0 (bottom of the display) to the display height (top of the display)
* `Color color` color of the pixel
  
#### Boundaries

Interface methods
* `Pixel project(DataPoint point)`
* `void applyBorder(int top, int bottom, int left, int right)`

Parameters
* `Pixel bl`
* `Pixel tr`

#### SquareBoundaries :: Boundaries

Implemented methods
* `Pixel project(DataPoint point)`
* `void applyBorder(int top, int bottom, int left, int* right)`

#### RoundBoundaries :: Boundaries

Implemented methods
* `void begin(Boundaries &boundaries)`
* `Pixel project(DataPoint point)`
* `void applyBorder(int top, int bottom, int left, int* right)`

Parameters
* `Pixel center`
* `float innerRadius`
* `float outerRadius`
* `float beginAngle`
* `float endAngle`

#### DisplayDriver

Implemented methods
* `void begin(Adafruit_GFX *tft)`
* `void drawPixel(Pixel c)`
* `void drawLine(Pixel a, Pixel b)`
* `void drawCircle(Pixel c, int r)`
* `void drawTriangle(Pixel a, Pixel b, Pixel c)`
* `void drawRectangle(Pixel bl, int w, int h)`
* `void drawRectangle(Pixel bl, Pixel tr)`
* `void drawRoundRectangle(Pixel bl, int w, int h, int r)`
* `void fillRectangle(Pixel bl, int w, int h)`
* `void fillCircle(Pixel c, int r)`
* `void fillTriangle(Pixel a, Pixel b, Pixel c)`
* `void fillRoundRectangle(Pixel bl, int w, int h, int r)`
* `void fillScreen(Color c)`
* `int width(void)`
* `int height(void)`

Parameters
* `Boundaries *fullScreen`

## Object oriented patterns and concepts

Visitors

Decorators
