# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Usage
Most use cases of this library involve the following three steps:

#### Initialize Adafruit GFX and Grafici GFX
```
Adafruit_GFX gfx;
DataSetFloat dataset;
float dataArray[dataSize] = { 0, 1, 2, 3, 4};

gfx.begin();
grafici.begin(gfx);
```
#### Import the dataset
```
dataset.begin(dataArray, dataSize);
```

#### Plot data on the display
```
grafici.clear();
grafici.plot(axisPlot, dataset);
```
## Customization

### Data

### Styles

### Colors 

### Geometry

## Contribute

### Object oriented patterns and concepts


