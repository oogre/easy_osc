# Easy OSC

## This repo purpose

We've build this repo to destination of students at ESA Brussel / Digital Art. This is a public repository, cause OSC communication between WebBrowsers, Processing, Arduino and Unity is not well documented on the web from our point of view. While it is a massive empowerment of our art projects. 

## Content

- [Arduino](./arduino/README.md)

- [Processing](./processing/README.md)

- [Unity](./unity/README.md)

- [WebBrowser](./webBrowser/README.md)

## Communication

- Arduino x Arduino
  
  - [oscSerial](./arduino/README.md#oscSerial) **x** [oscSerial](./arduino/README.md#oscSerial)

- Arduino x Processing
  
  - [oscSerial](./arduino/README.md#oscSerial) **x** [wusProxy/serial2udp](./wusProxy/README.md#serial2udp) **x** [oscUDP](./processing/README.md#udp)

- Arduino x Unity
  
  - [oscSerial](./arduino/README.md#oscSerial) **x** [wusProxy/serial2udp](./wusProxy/README.md#serial2udp) **x** [oscUnity](./unity/README.md#udp)

- Arduino x WebBrowser
  
  - [oscSerial](./arduino/README.md#oscSerial) **x** [wusProxy/serial2ws](./wusProxy/README.md#serial2ws) **x** [oscBrowser](./webBrowser/README.md)

- Processing x Processing
  
  - [oscUDP](./processing/README.md#udp) **x** [oscUDP](./processing/README.md#udp)

- Processing x Unity
  
  - [oscUDP](./processing/README.md#udp) **x** [oscUnity](./unity/README.md#udp)

- Processing x WebBrowser
  
  - [oscWS](./processing/README.md#ws) **x** [oscBrowser](./webBrowser/README.md)

- Unity x Unity
  
  - [oscUnity](./unity/README.md#udp) **x** [oscUnity](./unity/README.md#udp)

- Unity x WebBrowser
  
  - [oscUnity](./unity/README.md#ws) **x** [oscBrowser](./webBrowser/README.md)

- WebBrowser x WebBrowser
  
  - [oscBrowser](./webBrowser/README.md) **x** [wusProxy/ws2ws](./wusProxy/README.md#ws2ws) **x** [oscBrowser](./webBrowser/README.md)
