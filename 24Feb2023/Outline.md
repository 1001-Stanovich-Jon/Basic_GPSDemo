# Overview

OK, our goals for this session are:

- Quick Review of Last Time
- Build GPS logger
- Go over code for logger
- Look at processing data after retrieval
- Maybe bust out the logic analyzer?


If you want to see last times infor, you can [(click here)](https://github.com/1001-Stanovich-Jon/Basic_GPSDemo/blob/main/Outline.md)

Otherwise we'll do a basic recap real quick.

---

## Why are we using... well, what we're using?

![image](https://user-images.githubusercontent.com/84261577/222334914-0c9da662-3efd-4f5f-95be-bfeec5337455.png)


### Adafruit

We like Adafruit - they let us be lazy when prototyping. They let us be lazy because they design and sell breakout boards, which means:

- We don't have to read datasheets and designing external circuits for chips (much)
- We don't have to write code libraries ourselves
- We don't have to worry about level shifting

So, basically, they just save us time, money, and having to know stuff. Also they provide all their files and models! Which means they are a great tool for learning how to design around a chip because you can look at a working product, and refer to the datasheet to see why they designed the board the way they did (so that **you can do it one day**).

Also because they have a ton of documentation, code libraries, and tutorials available for pretty much *ALL* of their products. This means its unlikely that we'll get stuck getting something to work. 

Thanks Lady Ada.

![image](https://user-images.githubusercontent.com/84261577/222335177-da981c10-1317-4bb8-a26d-83a69026cc59.png)

### Arduino?

Well, again, premade PCB with USB interface, relatively cheap, and has a programming IDE for it that makes it easier to program than other microcontrollers (Like PIC or STM32s). Basically - **it's beginner and lazy-person friendly**.

The Arduino IDE makes it super easy to share libraries for the breakout boards. It's a great introduction to microcontrollers, and will let you become comfortable with the basics before eventually (well, if you're into it) learning how to do it without the Arduino base, or even on another microcontroller.

Again, there is a huge community behind Arduino, just like Adafruit, and so it makes it incredibly easy to use Adafruits products and have a fairly painless experience getting off to a good start.

Thanks Italians.

### Other Notes

Besides our decision choices, we also covered the following last time:

1. Basics of the GPS chips functionality, which included:
    - How it communicates (USART)
    - What it communicates (NMEA Sentences)

2. We also looked at using an OLED, that wasn't important really, I thought we'd get to more than we did though - we won't be using those this time. Those will be more important for final build and/or the ground station setup (we'll get to that later, once we can get some radios working).

We did *look* at some microSD cards last time, but we didn't get them working because I wasn't being careful about memory management. Today, we'll use the microSD cards.

---

# OK Moving on...

Today we have a simple goal:

- Assemble a GPS data logger
- Code the GPS data logger
- Interpret the data from the logger

Let's get started.

## Assembling the Data Logger

#### GPS Board

For future reference, we're are using the Adafruit Ultimate GPS breakout board [(click here for their product page)](https://www.adafruit.com/product/746)

![gpsBreakout](https://user-images.githubusercontent.com/84261577/221063977-b65a2597-8a97-4116-b8c2-38e17f40589a.png)

This chip allows us to receive GPS signals from the orbiting satellites. Last time we observed that signal quality can be drastically affected by your environment. We lost the GPS signal once we walked inside =( so we'll have to go outside for a little again if we want real data.

For this session, we'll only be concerned with the following pins:

> - TX
> - GND
> - VIN
> - FIX (Maybe)

Recall that it uses the USART communication protocol.

## microSD

We're using an Amazon special because I'm cheap (and I hope you are too). Also, because Adafruit also offers a *surface mounted SD flash card* - **amazing** (this means any code we write for these, will work with this component - this gives us flexibility)

We can use the card and holders for non-violent situations, and the surface mount for the violent situations (i.e. rockets taking off and hugging the ground at high speeds). The card slots are nice too because you can actualy remove the card to retrieve the data.

We will use all the pins on this board.

---

## Wiring

It's good practice to leave your board unplugged until you have everything connected. We'll start with the breadboard and Arduino. For wiring here, it's easier to have hte SD card above the GPS chip as shown below.

![photo1](https://user-images.githubusercontent.com/84261577/221133055-8ffa0d03-0c07-4ccb-9c67-d4a0866d2026.png)

First, wire power and ground to your rails as shown below

![powerwire](https://user-images.githubusercontent.com/84261577/221135365-4165a584-a811-447c-9f13-0014f680ff61.png)


Then connect power and ground for the GPS module and card slot as shown below

![chipPower](https://user-images.githubusercontent.com/84261577/221135392-d2899b30-2628-44c9-85f2-8da488c10415.png)

Then, we'll follow the wiring:

|Arduino Pin | microSD Slot Pin | GPS Pin|
|---|---|---|
|3 | NA | TX|
|10 |CS (Orange) | NA |
|11 |MOSI (Green)| NA |
|12 |MISO (Blue)| NA |
|13 |CLK (Yellow)| NA |

However, since the card slot isn't labelled, you should just follow the image below (the colors are the same as in the table above):

![commWires](https://user-images.githubusercontent.com/84261577/221135404-5d64de64-0f20-4f82-a5ee-53865af0372c.png)

### Indicator LEDs (Optional)

Sometimes its nice to have a low-memory-cost way of knowing what's happening, that's where indicator LEDs come into play since they require very little resources from the microcontroller to operate (unlike the OLED which used I2C and fancy libraries). 

ADD LATER

---

## Code

### Reading GPS Data

### Parsing GPS Data

### Using microSD Breakout Board

### Indicator LEDS

---

### Putting it All Together

