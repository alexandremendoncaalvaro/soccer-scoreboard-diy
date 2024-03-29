# UNDER CONSTRUCTION

# Soccer Scoreboard (DIY)
A DIY soccer scoreboard project.

The idea is to build a Soccer Scoreboard with a RGB addressable LED strip to create the digits.  
The scoreboard should show the SCORE and TIME, that you can choose between a countdown clock or a real-time clock.  
There are two options to change parameters and control the game score:  
- Infrared Remote Controller
- Portal accessed by ad-hoc Wifi connection

# Board Construction

## Material
| Components                            | x     |
| -------------                         | ----- |
|ESP8266 Board                          | 1x    |
|DS1307 Tiny RTC I2C                    | 1x    |
|IR Remote Controller + IR Receptor     | 1x    |
|Micro USB cable                        | 1x    |
|5V 2.5A power supply                   | 1x    |
|WS2812B LED Strip 60 LED's per meter   | 3m    |

## Circuit General Connections

![](readme/basic-connections.png)

## LED Address Layout

This layout shows how the LEDs needs to be positioned on the scoreboard

```bash
      __ __ __        __ __ __          __ __ __        __ __ __  
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
      __ __ __        __ __ __          __ __ __        __ __ __  
    __       149    __       128      __       107    __        86
    __        __    __        __      __        __    __        __
    __        __    __        __      __        __    __        __
      __ __ __       __ __ __           __ __ __        __ __ __   

      __ __ __        __ __ __          __ __ __        12 13 14  
    __        __    __        __      __        __    11        15
    __        __    __        __      __        __    10        16
    __        __    __        __  42  __        __    _9        17
      __ __ __        __ __ __          __ __ __        20 19 18  
    __        65    __        44  43  __        21    _8        _0
    __        __    __        __      __        __    _7        _1
    __        __    __        __      __        __    _6        _2
      __ __ __       __ __ __           __ __ __        _5 _4 _3   
```

# Inspiration and attributions

We'd decided to make this project from the scratch, by using the project [7-Segment Digital Clock](https://github.com/leonvandenbeukel/7-Segment-Digital-Clock-V2) as a reference and inspiration.  
This project and [7-Segment Digital Clock](https://github.com/leonvandenbeukel/7-Segment-Digital-Clock-V2) project are licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-nc-sa/4.0/).  

Special thanks to [Leon van den Beukel](https://github.com/leonvandenbeukel) for the amazing work.

# Contributors
| [<img width="100px" src="https://avatars3.githubusercontent.com/u/41878170?s=115&v=4"><br><sub>Alexandre Alvaro</sub>](https://github.com/alexandremendoncaalvaro) | [<img  width="100px" src="https://avatars2.githubusercontent.com/u/3439161?s=400&v=4"><br><sub>Guilherme Goll</sub>](https://github.com/guilhermecgoll) |
| :---: | :---: |