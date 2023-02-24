# Overview

OK, our goals for this session are:

- Review how the GPS Chip works
- Review saving data and out options
- Wire GPS Breakout Board, microSD Breakout Board, and Indicator LEDs
- Learn how to read GPS data in, parse it, and save it to file.
- Learn how to use Indicator LEDs

## Recap

OK, if you're following along, last time we went over some of our decisions, we won't go into super detail again [(if you want that click here)](https://github.com/1001-Stanovich-Jon/Basic_GPSDemo/blob/main/Outline.md), but here's a basic summary:

> We're choosing to use hardware from Adafruit because they have created breakout boards for the various sensors we would like to use. These breakout boards are made for ease of use, and typically involve little extra work to use besides simply connecting them properly. Connect to what? Our microcontroller.
> Again, we are choosing to use the Arduino UNO platform because again it is made in a way that minimized our need for circuit design, 
> and lets us easily connect sensors to it. Additionally, there is a huge community for both Adafruit and Arduino products, meaning there is
> readily available documentation and troubleshooting, making it easy and quick to prototype many ideas without the need for in depth knowledge of 
> electronics or microcontrollers. Regarding our sensor choices, we're using the GPS chip because it is the only breakout board by Adafruit, we're using the micro
> SD cards because they are easily obtainable and relatively cheap.

Besides our decision choices, we also covered the following last time:

1. Basics of the GPS chip
2. Basics of how the GPS communicates with the Arduino
3. Basics of the data format communicated by the GPS chip

We'll review these things again, and hopefully go a little more in depth this time. Now, let's get to it.

## GPS Chip

For those of you playing along at home, we are using the Adafruit Ultimate GPS breakout board [(click here for their product page)](https://www.adafruit.com/product/746)

![gpsBreakout](https://user-images.githubusercontent.com/84261577/221063977-b65a2597-8a97-4116-b8c2-38e17f40589a.png)

This chip allows us to receive GPS signals from the orbiting satellites. Last time we saw that signal reception can be drastically affected by your environment, as we lost the GPS signal once we walked inside.

A quick pin overview:

> - 3.3V --> (OUTPUT) Can output 3.3V and is possible of 100mA+ output
> - EN --> (INPUT) This is the enable pin. Default pulled high, pull low to turn off GPS module.
> - VBAT --> (INPUT) This in an input for an external battery
> - FIX --> (OUTPUT) This is an indicator pin (it also drives the red LED). It pulses on off once a second if we **DO NOT** have a signal. It will remain off and pulse briefly once every 15 seconds if we **DO HAVE** a signal.
> - TX --> (OUTPUT) The GPS chip transmits (sends) its data out from this pin
> - RX --> (INPUT) The GPS chip receives data on this pin, can be used to request various NMEA sentences
> - GND --> (INPUT) Ground connection
> - VIN --> (INPUT) 3.3/5V Input (Has built in level shifter, 5V tolerant)
> - PPS --> (OUTPUT) Pulse Per Second, i.e. it pulses HIGH once a second for around 50 - 100ms

From the above, for now, we'll only be using 3 (maybe 4) of these pins, and they include

> - TX
> - GND
> - VIN
> - FIX (Maybe)

## Saving Data

For now we are simply using a microSD card to save our data. They aren't any specific brand, any microSD card slot will work, as well as any microSD card.
The main reason for this is because Adafruit also sells a *surface mounted SD card* breakout board, that will be compatible with the code we write here. Similarly, for non-violent uses the chip holder will suffice (e.g. RC Plane).

## Wiring

## Reading GPS Data

## Parsing GPS Data

## Using microSD Breakout Board

## Indicator LEDS

## Putting it All Together

