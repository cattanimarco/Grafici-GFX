# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Simple plot
Given an Adafruit_GFX object and an array of floats, creating a plot with the Grafici GFX library only takes two simple steps:

1. Setup the library
```
DataSources::Float dataset;
float dataArray[5] = { 1, 0, 2, 1, 2 };

grafici.begin(gfx);
dataset.begin(dataArray, 1, 5);
```

2. Plot 
```
grafici.clear();
grafici.plot(Line, dataset);
```

The result is the following

![simplest plot](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/simple_plot.bmp)

Now that we plotted our first dataset, lets make it look better.

### Data Interpolation
In order to make the plot smoother, it is possible to increase the number of datapoint using interpolation. In the example below, for example, it is possible to use a spline interpolation to increase the number of datapoints from 5 to 100.

```
DataSources::Spline dataSpline;
dataSpline.begin(dataset, 100);
grafici.plot(Line, dataSpline);
```

The resulting plot line is much nicer and smoother. Note though that the spline interpolation can introduce new minimum and maximum, especially when there are drastic changes in the plot steepness.

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/interpolation.bmp)

### Data analisis
Grafici-GFX allows you to analyze the data with utlity such as the histogram tranformation, which takes as an input a dataset and outputs a new dataset of the datapoint frequencies. In the example below, we divide the data range into 15 buckets and count the number of occurences for each bucket sub-range.

```
DataSources::Histogram dataHist;
dataHist.begin(dataSpline, 15);
grafici.plot(barPlot, dataHist);
```

![histogram analisis](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/histogram.bmp)

### Subplot
It is also possible to compare data by having multiple plots side by side

1. Initialize
```
DataSources::Float dataset;
DataSources::Spline dataSpline;
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
First we fullScreen our plotting libraries, i.e. set the boundary to use the full screen display. Then, we divide the screen into sub boundary by slicing the full screen into 1 row and 2 columns. Finally, we select the region with index 0 and add an empty border around the plot for elegance. 
Sub boundary are indexed from bottom to top and from left to right. Thus, in this case index 0 meanse the leftmost sub boundary.
```
grafici.boundary.fullScreen().subBoundary(1, 2, 0).crop(0.04, 0.04, 0.04, 0.02);
grafici.plot(Line, dataSpline);
```
We repeat the same boundary transformation again. This time we select the rightmost sub boundary (with index = 1).
```
grafici.boundary.fullScreen().subBoundary(1, 2, 1).crop(0.04, 0.04, 0.02, 0.04);
grafici.plot(barPlot, dataSpline);
```


![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/subplot.bmp)

### Multiplot
It is possible to have draw multiple plot one over each other in a layered fashion. This can be achieved just by calling the plot function multiple times without changing the boundary before
1. Initialize
```
DataSources::Float dataset;
DataSources::Spline dataSpline;
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
grafici.boundary.fullScreen().crop(0.04, 0.04, 0.04, 0.04); 
```
By not changing the boundary between the two plot calls, we overimpose the two plots.
```
grafici.plot(Line, dataSpline); // using the same boundary, plot multiple times
grafici.plot(scatterPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/multiplot.bmp)

### Boundary tranformation
Creating sub boundary and adding empty boarders are just two of the tranformations available in Grafici GFX.
It is possible, for example, to mirror the boundary both horizzontally and/or vertically in order to flip the plot accordingly.

1.Initialize
```
DataSources::Float dataset;
DataSources::Spline dataSpline;
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
grafici.boundary.fullScreen().subBoundary(2, 2, 0).crop(0.02, 0.02, 0.02, 0.02);
grafici.plot(barPlot, dataSpline);
```
Horizzontal flip
```
grafici.boundary.fullScreen().subBoundary(2, 2, 1).crop(0.02, 0.02, 0.02, 0.02);
grafici.boundary.horizzontalFlip();
grafici.plot(barPlot, dataSpline);
```
Vertical flip
```
grafici.boundary.fullScreen().subBoundary(2, 2, 2).crop(0.02, 0.02, 0.02, 0.02);
grafici.boundary.verticalFlip();
grafici.plot(barPlot, dataSpline);
```
Horizzontal and vertical flips
```
grafici.boundary.fullScreen().subBoundary(2, 2, 3).crop(0.02, 0.02, 0.02, 0.02);
grafici.boundary.horizzontalFlip().verticalFlip();
grafici.plot(barPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/transformations.bmp)

### Circular boundary
Boundary transformations are not limited to rectangular displays. It is possible, for example, to produce circular plots just by using circular boundary. All boundary transformation still applies.

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/round_1.bmp)

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/round_2.bmp)

### Colors

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/colors.bmp)


### Plot types
1. Initialize
```
DataSources::Float dataset;
DataSources::Spline dataSpline;
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

grafici.boundary.fullScreen().subBoundary(2, 3, 0).crop(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(Line, dataSpline);

grafici.boundary.fullScreen().subBoundary(2, 3, 1).crop(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(barPlot, dataSpline);

grafici.boundary.fullScreen().subBoundary(2, 3, 2).crop(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(scatterPlot, dataSpline);

grafici.boundary.fullScreen().subBoundary(2, 3, 3).crop(0.02, 0.02, 0.02, 0.02);
grafici.plot(axisPlot, dataSpline);
grafici.plot(barcodePlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/styles.bmp)

## Contribute

TODO Class diagram
TODO Object oriented patterns and concepts
TODO link to project to run library on computer


