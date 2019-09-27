# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Usage
Most use cases of this library involve the following three steps:

```
Adafruit_GFX gfx;
DataSetFloat dataset;
float dataArray[dataSize] = { 1, 0, 2, 0, 1};

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);

// Plot
grafici.clear();
grafici.plot(linePlot, dataset);
```

![simplest plot](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/usage.bmp)

Now that we plotted our first dataset, let's make it look a bit nicer.

### Data Interpolation
In order to make the plot smoother, it is possible to increase the number of datapoint using interpolation. In the example below, for example, spline interpolation increase the number od datapoints from 5 to 100.

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
float dataArray[dataSize] = { 1, 0, 2, 0, 1};

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(&dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
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
float dataArray[dataSize] = { 1, 0, 2, 0, 1};

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(&dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline
dataHist.begin(&dataSpline, 15); // generate an histogram (15 bars) of the 100 interpolated points

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
float dataArray[dataSize] = { 1, 0, 2, 0, 1};

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(&dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
grafici.clear();

// set boundaries to full screen, divide screen in 2 colums and select first one. Finnally apply an empty bordet
grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
grafici.plot(linePlot, dataSpline);

// set boundaries to full screen, divide screen in 2 colums and select second one. Finnally apply an empty bordet
grafici.boundaries.reset().crop(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
grafici.plot(barPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/subplot.bmp)

### Multiplot

```
Adafruit_GFX gfx;
DataSetFloat dataset;
DataSetSpline dataSpline;
float dataArray[dataSize] = { 1, 0, 2, 0, 1};

// Initialize library
grafici.begin(gfx);

// Prepare data
dataset.begin(dataArray, 1, dataSize);
dataSpline.begin(&dataset, 100); // interpolate 5 datapoints into 100 datapoint using spline

// Plot
grafici.clear();
grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); 
grafici.plot(linePlot, dataSpline); // keep the same boundaries and plot multiple times
grafici.plot(scatterPlot, dataSpline);
```

![interpolated data](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/multiplot.bmp)

### Styles

### Colors 

### Geometry

## Contribute

### Object oriented patterns and concepts


