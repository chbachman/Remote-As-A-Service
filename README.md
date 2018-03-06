# Remote as a Service
With a small payment of only 10$ per use you too can pay us to install software on your Arduino and Raspberry Pi.

```c
#define Raspberry-Pi Master
#define Arduino Slave
```

## Requirements
> Make use of two Arduino (or similar) micro-controllers

We have one Raspberry Pi and one Arduino. The Arduino will communicate with the Raspberry Pi over serial, and act as a Remote Control over Serial Communication. The Arduino will host a web-server with a REST Api that will allow control over the Arduino controller that it will power.

> Utilize at least four different external devices (16x2 display, LEDs, pushbuttons, touch sensors, etc)

* LED on the Arduino
* IR Emitter on the Arduino
* Computer that's running Python Script with Alfred.
* TV that is handling input/output

If those are not good enough:

* Phone running iOS App to control Arduino
* Webpage running Website to control Arduino

If those are not good enough:

* 16x2 Display to output signal name on Slave
* Pushbutton to emit some signal on Slave

> Utilize at least one communication mechanism (ethernet, bluetooth, serial, etc)

We have a Serial Communication between the Raspberry Pi and the Arduino, a Ethernet/Wi-Fi Communication between the Raspberry Pi and a python script on the computer that is hooked up to [Alfred 3](https://www.alfredapp.com) (Can you tell why I picked this project?) and a IR communication from the Arduino to the TV/Other.

> Involve some original work

We hope so!

## Details
### Master -> Slave Serial Interface
Since the Slave can't get success/failure or need to send any data back, we can have a one way communication to the Slave.

Command will be sent from the Master to the Slave using Serial Commands. The Arduino will listen for commands, and if any are received will immediately execute the corresponding command.

### Web-Server
A web-server running on the Master will let us control the remote easily from a variety of devices. Making HTTP Requests is easily handled, and even more so if I can get Bonjour to easily detect Remotes on the same Wi-Fi Network (Zero-Conf Detection).

This Web-Server will be written in:

* Go? (Never used it and would like to try)
* Rust? (Never used it and would like to try)
* Kotlin? (Used it a bunch, know it has WebServer libraries) (Might be too slow (JVM))
* Swift? (Linux Support isn't great)
* Node.js? (Might be too slow)


