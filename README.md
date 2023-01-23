<p align="center">
  <a href="" rel="noopener">

</p>

<h3 align="center">Arduino_gear_shifter</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Paddel shift automatic, build using an Arduino Nano.
    <br> 
</p>

## 📝 Table of Contents

- [📝 Table of Contents](#-table-of-contents)
- [🧐 About ](#-about-)
- [🏁 Getting Started ](#-getting-started-)
  - [Prerequisites](#prerequisites)
  - [Installing](#installing)
- [⛏️ Built for ](#️-built-for-)
- [✍️ Authors ](#️-authors-)
- [🎉 Acknowledgements ](#-acknowledgements-)

## 🧐 About <a name = "about"></a>

Paddel shift automatic, build using an Arduino Nano.

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

Working Arduino IDE, and the following libraries:

```
Adafruit SSD1306 2.5.3
Adafruit GFX Library V1.11.0
Adafruit TFTLCD Library V1.0.3
Adafruit Circuit Playground V1.11.3
Adafruit BusIO V1.11.6
Wire Built-In
avdweb_VirtualDelay
```

### Installing

Configure your in/outputs here:

```C++
// define relay's 
#define MB1_1 2 // MM1 out
#define MB1_2 3 // MM1 mid
#define MB1_3 4 // MM1 in
#define MB2_1 5 // MM2 out
#define MB2_2 6 // MM2 mid
#define MB2_3 7 // MM2 in
#define MB3_1 8 // MM3
// define buttons
#define Button_UP 10
#define Button_DOWN 11
#define Button_Reverse_unlock 12
#define Button_N 13
```

Configure your timings here

```C++
// Change timings here!
int clutch_push_delay = 1000;  //in ms
int clutch_release_delay = 1000;  //in ms
int between_piston_delay = 1000; //in ms
int between_valve_delay = 200; //in ms
int shift_delay = 50; //in ms
```

Configure your screen size here:

```C++
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
```

## ⛏️ Built for <a name = "built_for"></a>

- [Arduino](https://www.arduino.cc/) - Hardware

## ✍️ Authors <a name = "authors"></a>

- [@LukasL28](https://github.com/LukasL28) - Software Developer
- [@JanH.](https://github.com/JanH75) - Initial idea & project lead

## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- --

