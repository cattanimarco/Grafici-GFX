# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Usage
Given an Adafruit_GFX object and an array of floats
```
Adafruit_GFX gfx;
float dataArray[dataSize] = { 1, 0, 2, 1, 2 };
```
creating a plot with the Grafici GFX library only takes 3 small steps:
1. Initialize 
```
DataSetFloat dataset;
grafici.begin(gfx);
```
2. Load the data
```
dataset.begin(dataArray, 1, dataSize);
```
3. Plot
```
grafici.clear();
grafici.plot(linePlot, dataset);
```

![simplest plot](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/usage.bmp)

Now that we plotted our first dataset, let make it looks better.

### Data Interpolation
In order to make the plot smoother, it is possible to increase the number of datapoint using interpolation. In the example below, for example, it is possible to use a spline interpolation to increase the number of datapoints from 5 to 100.
1. Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
grafici.begin(gfx);
```
2. Load/Generate the data
```
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
```
3. Plot
```
grafici.clear();
grafici.plot(linePlot, dataSpline); // plot interpolated data instead of original source
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/interpolation.bmp)

### Data analisis
It is possible to analize the data in many different ways such as plotting an histogram (the frequency of occurence of each value) of the datya source.

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
DataSetHistogram dataHist;
float dataArray[dataSize] = { 1, 0, 2, 1, 2 };

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
dataHist.begin(dataSpline, 15); // generate an histogram (15 bars) of the 100 interpolated points

// Plot
grafici.clear();
grafici.plot(barPlot, dataHist); // plot histogram using barplot
```

![histogram analisis](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/histogram.bmp)

### Subplot

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
float dataArray[dataSize] = { 1, 0, 2, 1, 2 };

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
grafici.clear();

// Reset boundaries, i.e. set to full screen plotting, then divide screen in 1 row and 2 colums. 
// Select the first column and add a blank border
grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
grafici.plot(linePlot, dataSpline);

// same as before, but select the second column
grafici.boundaries.reset().crop(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
grafici.plot(barPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/subplot.bmp)

### Multiplot

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
float dataArray[dataSize] = { 1, 0, 2, 1, 2 };

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
grafici.clear();
grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); 
grafici.plot(linePlot, dataSpline); // using the same boundaries, plot multiple times
grafici.plot(scatterPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/multiplot.bmp)

### Boundaries tranformation

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
float dataArray[dataSize] = { 1, 0, 2, 1, 2 };

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
grafici.clear();

grafici.boundaries.reset().crop(2, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(barPlot, dataSpline);

grafici.boundaries.reset().crop(2, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.horizzontalFlip();
grafici.plot(barPlot, dataSpline);

grafici.boundaries.reset().crop(2, 2, 2).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.verticalFlip();
grafici.plot(barPlot, dataSpline);

grafici.boundaries.reset().crop(2, 2, 3).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.horizzontalFlip().verticalFlip();
grafici.plot(barPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/transformations.bmp)

### Colors 

## Contribute

TODO Class diagram
TODO Object oriented patterns and concepts
TODO link to project to run library on computer


