# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Quickstart

1. Download the Grafici library via Arduino IDE. This should download also the Adafruit_GFX library.
    - `Sketch > Include Library > Manage Libraries` or `SHIFT + CMD + I`
    - Search for "Grafici"
    - Select `Grafici-GFX` and click `Install`
2. Open the _simple plot_ example
    - `File > Examples > Grafici-GFX > simple-plot`
3. If you are not using a standard Adafruit TFT shield, change the lines below to match your configuration
    - `#include Adafruit_ILI9341.h` 
    - `Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);`
4. Compile and upload the code to your Arduino
    - `Edit > Upload` or `CMD + U`
5. The Arduino's display should show the following
![simple plot](https://github.com/cattanimarco/Grafici-Test/blob/master/imgs/simple_plot.bmp)

## Documentation
Documentation available in the [wiki](https://github.com/cattanimarco/Grafici-GFX/wiki)


