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

## Customization
Now that we plotted our first dataset, let's make it look a bit nicer.

### Data
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

### Styles

### Colors 

### Geometry

## Contribute

### Object oriented patterns and concepts


