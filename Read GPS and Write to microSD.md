# Overview

OK, our goals for this session are:

- Review how the GPS Chip works
- Review saving data and out options
- Wire GPS Breakout Board, microSD Breakout Board, and Indicator LEDs
- Learn how to read GPS data in, parse it, and save it to file.
- Learn how to use Indicator LEDs

## Recap

OK, if you're following along, last time we went over some of our decisions, we won't go into super detail again [(if you want that click here)](https://github.com/1001-Stanovich-Jon/Basic_GPSDemo/blob/main/Outline.md), but here's a basic summary:

---

### Why use Adafruit products again?

We like Adafruit because they let us be lazy. They have designed breakoutboards for a large variety of sensors, which saves us the pain of reading datasheets, sourcing components, and designing PCBs. Also, this means we have a reference PCB for design in the future when we decide to make our own PCB (this is useful if the datasheet isn't good at describing external circuitry).

Also because they have a ton of documentation, code libraries, and tutorials available for pretty much *ALL* of their products. This means its unlikely that we'll get stuck getting something to work. 

Thanks Lady Ada.

---

### Why use Arduino?

Well, again, it has all the external circuitry done, it's relatively cheap, and has a programming IDE for it that makes it easier to program than having to learn C/C++ and use other programmers to flash the chip. Also, the Arduino IDE is what makes it super easy to share libraries for the breakout boards. It's a great introduction to microcontrollers, and will let you become comfortable with the basics before eventually (well, maybe) learning how to do it without the Arduino base, or even on another microcontroller like the RP2040.

Another reason is that it readily supports the most common communication protocols for hobby sensors:

- USART
- SPI
- I2C

Again, there is a huge community behind Arduino, just like Adafruit, and so it makes it incredibly easy to use Adafruits products and have a fairly painless experience getting off to a good start.

Thanks Italians.

---

## Recap

Besides our decision choices, we also covered the following last time:

1. Basics of the GPS chip
2. Basics of how the GPS communicates with the Arduino
3. Basics of the data format communicated by the GPS chip

We'll review these things again, and hopefully go a little more in depth this time. Now, let's get to it.

## GPS Chip

For those of you playing along at home, we are using the Adafruit Ultimate GPS breakout board [(click here for their product page)](https://www.adafruit.com/product/746)

![gpsBreakout](https://user-images.githubusercontent.com/84261577/221063977-b65a2597-8a97-4116-b8c2-38e17f40589a.png)

This chip allows us to receive GPS signals from the orbiting satellites. Last time we saw that signal reception can be drastically affected by your environment, as we lost the GPS signal once we walked inside. For this session, we'll only be concerned with the following pins:

> - TX
> - GND
> - VIN
> - FIX (Maybe)

and recall that it uses the USART communication protocol

## microSD

We're just using an Amazon special because I'm cheap (and I hope you are too). Also, because Adafruit also offers a *surface mounted SD flash card* - **amazing**. This means any code we write for these, will work with a surface mounted component - this gives us flexibility. We can use the card and holders for non-violent situations, and the surface mount for the violent situations (i.e. rockets taking off and hugging the ground at high speeds). The card slots are nice too because you can actualy remove the card to retrieve the data.

The pinout for the microSD card slot is below

---

## Wiring

It's good practice to leave your board unplugged until you have everything connected.

### Power Rails 

### GPS Chip

### microSD Card

### Indicator LEDs

---

## Code

### Reading GPS Data

### Parsing GPS Data

### Using microSD Breakout Board

### Indicator LEDS

---

### Putting it All Together

