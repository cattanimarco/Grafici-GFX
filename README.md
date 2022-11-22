# Grafici GFX
Grafici GFX is a data plotting library for Adafruit GFX graphic libraries. 
This modular library allows you to easily manage and plot data on any arduino display/lcd supporting the Adafruit GFX library.

## Quickstart

Download the Grafici library via Arduino IDE. This should download also the Adafruit_GFX library.
- `Sketch > Include Library > Manage Libraries` or `SHIFT + CMD + I`
- Search for "Grafici"
- Select `Grafici-GFX` and click `Install`, `Install all`

Open the _simple plot_ example
 - `File > Examples > Grafici-GFX > line_and_histogram`

If you are not using a standard Adafruit TFT shield, change the lines below to match your configuration
- `#include Adafruit_ILI9341.h` 
- `Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);`

Compile and upload the code to your Arduino
- `Edit > Upload` or `CMD + U`

The Arduino's display should show the following

![line_and_histogram image](https://raw.githubusercontent.com/cattanimarco/Grafici-Test/master/imgs/examples/line_and_histogram.bmp)

## Documentation
* Have a look at the [user documentation](https://github.com/cattanimarco/Grafici-GFX/wiki/Api-Main) provided with the library