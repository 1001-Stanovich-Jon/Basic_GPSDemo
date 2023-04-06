# Notes

- Chip confirmed working using Adafruits testing sketch.

# Sample Data Collected

I didn't feel like reading the datasheet so I captured the I2C communication that the Adafruit test sketch produces. The first transaction is shown below

## Chip Checkup and Reset

![image](https://user-images.githubusercontent.com/84261577/230263712-9395bade-81fe-4ee1-bb43-dfac5219babe.png)

Here we first see a write command to the `D0` register, which requests the ID of the chip, we then request a read and receive a value of `60` (which we indeed see). This is outlined in the datasheet

![image](https://user-images.githubusercontent.com/84261577/230264839-3320a73c-3130-4e6d-ba3f-9f89769a5a29.png)


Second, we see that we request a write to `E0` and then proceed to write `B6`. This resets the chip using hte complete power-on-reset procedure. If you write anything beside `0xB6`, nothing will happen.
If for some reason you read this register, it should return `0x00`, as described in the datasheet

![image](https://user-images.githubusercontent.com/84261577/230264886-483fee17-34d0-4df9-82cc-bce19302b193.png)


## Request Status

The beginning of the next sequence starts with a status request by writing to `F3` and reading a byte,

![image](https://user-images.githubusercontent.com/84261577/230264513-4f763d34-f946-452a-aa3c-5eba8d787d5a.png)

In this case it is `0x00`, which means...

![image](https://user-images.githubusercontent.com/84261577/230264646-1260c334-95aa-4517-bafd-513698e65b43.png)

... that the device is not gathering or writing data.

## Gather Calibration Data

The chip itself is provided with calibration data (that we *cannot change*) The next steps we see in the I2C capture is the request of all these values. There are too many reads to post a nice photo, but a table describing the registers is below.

![image](https://user-images.githubusercontent.com/84261577/230265330-888a8e5a-d9a7-4a94-90fa-02c9d26a17da.png)
![image](https://user-images.githubusercontent.com/84261577/230265479-6514c93f-3162-45d5-8fa8-ede63c78c4f3.png)

the actual data we collected is

![image](https://user-images.githubusercontent.com/84261577/230265570-385d1ee3-2d85-4586-ab05-85f1ac50bdf1.png)

Since these values don't change, we can avoid having to read them everytime, not that it's that big of a deal but it's a small shortcut.

## Setting Configuration and Other Settings

The last four transactions are

![image](https://user-images.githubusercontent.com/84261577/230265856-bce3dc3d-419f-488a-aef4-eef365b5de15.png)

and these set the device up for measurements.

### Register `0xF4` - `ctrl_meas`
![image](https://user-images.githubusercontent.com/84261577/230266212-e7b8f664-ab8c-45ef-8318-797806350fdb.png)

### Register `0xF2` - `ctrl_hum`
![image](https://user-images.githubusercontent.com/84261577/230266110-dbc1b473-5b81-4553-af7f-5bff625eb7e5.png)
![image](https://user-images.githubusercontent.com/84261577/230266162-75f1e9a2-d8db-4d27-b3f9-c629b4845889.png)


### Register `0xF5` - `config`
![image](https://user-images.githubusercontent.com/84261577/230266238-64aa21a2-1fd5-456c-8ad8-e0301c3c1740.png)

### So... what did we do?

Well, the first write to `0xF4` disabled oversampling for temperature and pressure, and set to sleep mode. However, I don't think this does anything except allow us to write to `ctrl_meas` since changes to this register don't take affect until after we've written to `ctrl_meas`, which we do next.

Then, the write to `0xF2` of `0x05` which sets oversampling to x16. (Change doesn't take affect until we write to `ctrl_meas`, which we did already. However, now we can change `ctrl_meas`)

Then we write to `0xF5` the value of `0x00`. This sets the filter off and sets $$t_{standby}$$ to 0.5ms.

Then, we write again to `0xF4` since it will take affect now (because we've written to `ctrl_hum`) and we write `B7`. This sets the oversampling for temperature and pressure to x16, and also enables normal mode.
