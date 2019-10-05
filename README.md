# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Simple plot
Given an Adafruit_GFX object and an array of floats, creating a plot with the Grafici GFX library only takes two simple steps:

1. Setup the library
```
DataSetFloat dataset;
float dataArray[5] = { 1, 0, 2, 1, 2 };

gfx.begin();
gfx.setRotation(1);
grafici.begin(gfx);
dataset.begin(dataArray, 1, 5);
```

2. Plot 
```
grafici.clear();
grafici.plot(linePlot, dataset);
```

The result is the following
![simplest plot](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/simple_plot.bmp)

Now that we plotted our first dataset, lets make it look better.

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
1. Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
DataSetHistogram dataHist;
grafici.begin(gfx);
```
2. Load/Analyze the data
```
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
dataHist.begin(dataSpline, 15); // generate an histogram (15 bars) of the 100 interpolated points
```
3. Plot
```
grafici.clear();
grafici.plot(barPlot, dataHist); // plot histogram using barplot
```

![histogram analisis](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/histogram.bmp)

### Subplot
It is also possible to compare data by having multiple plots side by side

1. Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
grafici.begin(gfx);
```
2. Load the data
```
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
```
3. Plot
```
grafici.clear();
```
First we reset our plotting libraries, i.e. set the boundaries to use the full screen display. Then, we divide the screen into sub boundaries by slicing the full screen into 1 row and 2 columns. Finally, we select the region with index 0 and add an empty border around the plot for elegance. 
Sub boundaries are indexed from bottom to top and from left to right. Thus, in this case index 0 meanse the leftmost sub boundary.
```
grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
grafici.plot(linePlot, dataSpline);
```
We repeat the same boundary transformation again. This time we select the rightmost sub boundary (with index = 1).
```
grafici.boundaries.reset().crop(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
grafici.plot(barPlot, dataSpline);
```


![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/subplot.bmp)

### Multiplot
It is possible to have draw multiple plot one over each other in a layered fashion. This can be achieved just by calling the plot function multiple times without changing the boundaries before
1. Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
grafici.begin(gfx);
```
2. Load data
```
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
```
3. Plot 

```
grafici.clear();
grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); 
```
By not changing the boundaries between the two plot calls, we overimpose the two plots.
```
grafici.plot(linePlot, dataSpline); // using the same boundaries, plot multiple times
grafici.plot(scatterPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/multiplot.bmp)

### Boundaries tranformation
Creating sub boundaries and adding empty boarders are just two of the tranformations available in Grafici GFX.
It is possible, for example, to mirror the boundaries both horizzontally and/or vertically in order to flip the plot accordingly.

1.Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
grafici.begin(gfx);
```

2. Load data
```
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
```

3. Plot
```
grafici.clear();
grafici.boundaries.reset().crop(2, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(barPlot, dataSpline);
```
Horizzontal flip
```
grafici.boundaries.reset().crop(2, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.horizzontalFlip();
grafici.plot(barPlot, dataSpline);
```
Vertical flip
```
grafici.boundaries.reset().crop(2, 2, 2).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.verticalFlip();
grafici.plot(barPlot, dataSpline);
```
Horizzontal and vertical flips
```
grafici.boundaries.reset().crop(2, 2, 3).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.boundaries.horizzontalFlip().verticalFlip();
grafici.plot(barPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/transformations.bmp)

### Circular boundaries
Boundaries transformations are not limited to rectangular displays. It is possible, for example, to produce circular plots just by using circular boundaries. All boundaries transformation still applies.

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/round_1.bmp)

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/round_2.bmp)

### Colors

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/colors.bmp)


### Plot types
1. Initialize
```
DataSetFloat dataset;
DataSetSpline dataSpline;
grafici.begin(gfx);
```
2. Load data
```
dataset.begin(dataArray, 1, 5);
dataSpline.begin(dataset, 30);
```
3. Plot
```
grafici.clear();
grafici.style.colorPalette = &csBright;
grafici.style.colorSource = ColorSource::computeFromY;

grafici.boundaries.reset().crop(2, 3, 0).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(linePlot, dataSpline);

grafici.boundaries.reset().crop(2, 3, 1).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(barPlot, dataSpline);

grafici.boundaries.reset().crop(2, 3, 2).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(scatterPlot, dataSpline);

grafici.boundaries.reset().crop(2, 3, 3).addBorder(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(barcodePlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/styles.bmp)

## Contribute

TODO Class diagram
TODO Object oriented patterns and concepts
TODO link to project to run library on computer


