3 Phase Notes
# From Notes

Want to go over:

1. Chips
2. Connections
3. Data storage
4. Protocols

Coding:
1. How to find libraries
2. How to learn from libraries by reading them

Potential Additional Items:

1. Basic overview of Arduino
2. SD card vs SMT memory
3. How GPS Works

# Big Picture

## The End Goal

The first part of any project, is knowing what the projects purpose is. Our project's purpose is clear: **to receive and store GPS data.** 

Now, how do we do this? Well, I think this can be separated into two main processes:

1. Hardware selection
2. Implementation

Now, I've already selected the hardware, but I'll step you through the process of why I chose what I did.

## Hardware Selection

### Choosing a Microcontroller

The first thing to note here is that we are going to assume we've chosen the Arduino UNO board (or rather a clone of it to keep costs down) to serve as our microcontroller. 

We could have chosen to use something else, however the Arduino boards are always a good choice for prototyping because they have a large community behind them, this means:

- Lots of documentation
- A lot of hardware already has libraries for it written by the community
- Certain companies make boards and guides specifically for use with Arduino (e.g. Adafruit)

The other important things to note about the UNO (and a lot of derivatives), is that they readily support the most common hardware communication protocols:

1. USART
2. I2C
3. SPI

This will be important to note when making hardware selection.

So, we've chosen a microcontroller, what's next?

### Component Selection

The next step is to research and choose the proper components we need for the project. Some of my go-to places for hardware searching are:

1. Digi-Key
2. Mouser Electronics
3. Adafruit
4. Amazon
5. Sparkfun

For now, we'll focus on Adafruit because they do a great job at making breakout boards and also supplying schematics and code libraries for all of their products, which are incredibly valuable when learning about designing projects. 

This project involves obtaining GPS data, and saving it to some meory, and potentially viewing it on some external display. So, we have to find components for each piece:

#### 1. Obtaining GPS Data

We'll need a GPS receiver to listen to GPS signals. If we go to Adafruit's website and search for GPS, and filter by sensors, we'll see a few different results. Notably, we'll see options for a **chipset** and for a **breakout**. These are important terms:

- A chipset is simply the chip itself, for example, this is the [GPS chipset](https://www.adafruit.com/product/5186)

![gpschipset](https://user-images.githubusercontent.com/84261577/219500353-508e541a-96d8-4cfb-be5e-41c455d369ec.png)

- A breakout (aka breakout board) is the chip on a PCB with external components added to make it easy for use with a microcontroller, [this is the breakout board with the above chipset](https://www.amazon.com/Adafruit-Ultimate-GPS-Breakout-channel/dp/B01H1R8BK0/ref=asc_df_B01H1R8BK0?tag=bngsmtphsnus-20&linkCode=df0&hvadid=80333185695330&hvnetw=s&hvqmt=e&hvbmt=be&hvdev=c&hvlocint=&hvlocphy=&hvtargid=pla-4583932713646922&psc=1)

![gpsbreakout](https://user-images.githubusercontent.com/84261577/219500373-221fb4a2-10d7-410f-ba42-9c2d1acdfaf2.png)


We would want to choose the breakout board. Why? Well, if we were to buy the chipset, we are only getting the GPS receiver, and to actually interact with it we would need to go to the datasheet, find the applications notes and refrences for how to implement it into a design. After this, we would need to acquire those components, and then solder everything together before we could use it. For example, if we look at the datasheet for our GPS modules (PA1616S) we will see a section called "Reference Design"

[Click here for full datasheet, this is on page 21](https://cdn-shop.adafruit.com/product-files/5186/5186_PA1616D_Datasheet.pdf)

And this describes how we would need to design a circuit to integrate this chip. This is exactly what Adafruit has done for us, and we can simply connect it to the microcontroller. 

![diagram_GPSModule](https://user-images.githubusercontent.com/84261577/219500391-62e75822-9648-4a65-90ca-0bcf3b0867d1.png)


This is exactly what they have done for us with the breakout board, and it makes life easier. 

However it is important to note that we did not have to choose this chip, we could have gone to another website and found a different chip.

We'll get into the details of how to use the chip later, for now let's continue choosing our hardware.

#### 2. Saving Data to External Memory

We want to save and store the data for later use, so we'll definitely need non-volatile memory. While there are various memory types, we'll stick with one of the most common methods, which is simply using some sort of flash memory. 

Now, we have a design consideration here:

> Do we want to use on board memory or removable memory? 

By on-board I mean an IC that is standalone and needs to be connected to via jumpers/traces and we would have to extract the data via the microcontroller or other hardware, and example is below, 

[Click here to view on Adafruit's Website](https://learn.adafruit.com/adafruit-spi-flash-sd-card)
![sdflash](https://user-images.githubusercontent.com/84261577/219500414-2ddefe17-6fc3-49ed-a8ef-b21fbf50e2ba.png)


By removable I mean or do we want to use an SD card that can be removed. In this case, we would need to find an SD card holder, and simply buy an SD card to use with it. An example of a holder is below:

[Click here to view on Amazon](https://www.amazon.com/ANMBEST-Adapter-Interface-Conversion-Arduino/dp/B08CMLG4D6/ref=sr_1_4?crid=17V4B67UZN1PI&keywords=sd+card+breakout&qid=1676582161&sprefix=sd+card+breakou%2Caps%2C172&sr=8-4)
![sdcard_breakouts](https://user-images.githubusercontent.com/84261577/219500431-69a24735-158f-4f89-8407-b5062109d8a2.png)


And you can use any SD card with these.

What are the reasons we'd use one or the other? Well it will really come down to the project. Are you going for super small design? Are you going to be experience massive amounts of vibrations or impact? Is your device *ONLY* going to be interactable through a cable (e.g. USB) and not easy to access once assembled?Then on board memory is probably your friend, because they are less prone to errors during violent movements and can be hidden inside case.

Do you want the ability to remove the card? Do you want to be able to change memory size? Do you want to save the data but not have to interact with the device using a computer every time? If yes then you probably want an SD card slot since you can just remove the card to read it, and you can also upgrade or downgrade memory size.

There are other options, such as general flash storage, FRAM. If you search for a lot of these chips, you'll notice they typically use either SPI or I2C to communicate with, which as we saw is supported by the UNO, that's good.

#### 3. Displaying Data

The last piece of equipment we'll want would be a display. There are tons of ways to display data:

- Built-in Serial Monitor for Arduino
- 7-Segment Displays
- LCD Displays
- LED Displays
- OLED Displays
- e-ink Displays
- Custom built LED displays

and I'm sure there's more that I missed. The point is that you have options. If you go on any of the sites I mentioned and look for displays, you'll see a lot of options, it really isn't too important which one you choose, though it is preferrable (for smaller projects at least) to use ones that do not require massive amounts of connections. For example, if you worked with the LCD display or 7-Segment display for CPE 301, you know that without external hardware (which means more unnecessary work and time you have to spend on the project) they can use a lot of pins. For this reason I chose to go with some simple monochrome OLED displays

[Click here to visit Amazon page for them](https://www.amazon.com/gp/product/B09JWLDK9F/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
![oled](https://user-images.githubusercontent.com/84261577/219500451-1c619e48-81f6-441c-bdc8-b4f0c8912bbd.png)


## Implementation

OK, we've reviewed the hardware, now we need to start doing stuff.

Everyone has their preferred method of doing things, I personally like to make a brief list of protocols I need for everything, and then get connections down first before coding just to make sure I'm not going to run out of inputs/outputs.

So, we should do a quick review of our hardware and connections. 

#### GPS Connections

So, if we have a chip that has a bunch of connections that we don't know about, it's definitely time to go back to the datasheet/product page. If we go to Adafruit they outline what all the connections are [here](https://learn.adafruit.com/adafruit-ultimate-gps/pinouts), from this list we see that we only need a few connections

1. TX
2. RX
3. GND
4. VIN

The other connections are used for battery power, putting the chip to sleep, power out, fix status, and PPS (i'm not sure what this is for exactly, they mention it's for synchronizing with microcontroller).

#### Memory Connections

Looking at the bottom of the PCB, we see several connections:

- 3v3 (Really 5.5V, these are mislabelled I believe)
- CS
- MOSI
- MISO
- GND

We will need all of these, and we'll note that this will require the SPI communication connections.

#### Display Connections

Looking at teh display, we see it has only for pins, all of which we'll need:

- GND
- VCC
- SCL
- SDA

Note the last two pins indicate I2C communication.

## Making Connections

OK, now that we've identified what we have to hookup, lets make a plan to do so. 

Below is a reference for arduino connections:

![arduinopiinout](https://user-images.githubusercontent.com/84261577/219500478-d1aa4cbc-a3c3-4802-8532-28f68be76572.png)

So, let's do the GPS unit first. I do want to note somethign important first - even though there are UART In and Out Pins labelled on the Arduino, we will not be using these for now, and you will understand shortly. But for now, we need to pick two *other* pins for TX and RX, we can pick any other digital pins that are not needed for I2C or SPI communication, so D2 - D9. Let's pick D3 and D4.

The other two connections will be shared by all device, which are the 5V supply and GND connection, we will connect these to the side rails on the breadboard

So we will connect:

>- Pin D2 on Arduino --- RX Pin on GPS
>- Pin D3 on Arduino --- TX Pin on GPS
>- 5V Breadboard      --- VIN on GPS
>- GND Breadboard   --- GND on GPS

Next, the micro SD card Holder:

Starting from the top as 1 I'll refer to the pins on card holder

>- 5V Breadboard                    --- 3.3V Pin on card holder (TOP - 1)
>- Pin D10 (SS) on Arduino     --- CS Pin on card holder (2)
>- Pin D11 (MOSI) on Arduino --- MOSI Pin on card holder (3)
>- Pin D12 (MISO) on Arduino --- MISO Pin on card holder (5)
>- Pin D13 (SCK) on Arduino   --- CLK Pin on card holder (4)
>- GND Breadboard                 --- GND Pin on card holder (6)

Note, for the CS pin on the card holder, you could potentially use any other digital pin as well since chip select isn't part of the SPI hardware. You can use other pins for SPI as well, but this would involve Bit-Banging, and we don't wanna do that right now.

Finally, the OLED Display:

>- 5V Breadboard                   --- VCC on OLED
>- GND Breadboard                --- GND on OLED
>- SCL Pin on Arduino            --- SCL on OLED
>- SDA Pin on Arduino            --- SDA on OLED

## Code

OK, now that we've verified we can connect, we'll jump into the code. Once everythign is connected, I like to verify that each chip is working on it's own. To do this we will use the provided example files by Adafruit and other Arduino libraries.

After we've done this we can try some test code [here](https://github.com/1001-Stanovich-Jon/UNRAero-GPS-OLED/blob/main/FirstIteration.ino)

## Libraries we'll be using

We will use:

- Wire (for I2C) (Base)
- SD (for SD card - you do NOT want to try and implement this yourself) (Base)
- SPI (for SD card) (Base)
- OLED Display (For premade commands) (Adafruit)
- Software Serial (for separate Serial with GPS) (Base)
- Hardware Serial (this is included by default) (Not an import)

### Backwards Learning from Libraries

A great way to learn is to find the code they use, and read through it to figure out how they structure it andw hat exactly they're doing.

You can use the IDE to find the folder for exmaples.



