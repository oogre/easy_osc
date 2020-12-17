# Easy OSC

## This repo purpose

We've build this repo to destination of students at ESA Brussel / Digital Art. This is a public repository, cause OSC communication between WebBrowsers, Processing, Arduino and Unity is not well documented on the web from our point of view. While it is a massive empowerment of our art projects. 

## Content

- [Arduino](./arduino)

- [Processing](./processing)

- [Unity](./unity)

- [WebBrowser](./webBrowser)

- [WusProxy](./wusProxy)

## Communication

- Arduino x Arduino
  
  - [oscSerial](./arduino#oscSerial) **x** [oscSerial](./arduino#oscSerial)

- Arduino x Processing
  
  - [oscSerial](./arduino#oscSerial) **x** [wusProxy/serial2udp](./wusProxy#serial2udp) **x** [oscUDP](./processing#oscudp)

- Arduino x Unity
  
  - [oscSerial](./arduino#oscSerial) **x** [wusProxy/serial2udp](./wusProxy#serial2udp) **x** [oscUnity](./unity#udp)

- Arduino x WebBrowser
  
  - [oscSerial](./arduino#oscSerial) **x** [wusProxy/serial2ws](./wusProxy#serial2ws) **x** [oscBrowser](./webBrowser)

- Processing x Processing
  
  - [oscUDP](./processing#oscudp) **x** [oscUDP](./processing#oscudp)

- Processing x Unity
  
  - [oscUDP](./processing#oscudp) **x** [oscUnity](./unity#udp)

- Processing x WebBrowser
  
  - [oscWS](./processing#oscws) **x** [oscBrowser](./webBrowser)

- Unity x Unity
  
  - [oscUnity](./unity#udp) **x** [oscUnity](./unity#udp)

- Unity x WebBrowser
  
  - [oscUnity](./unity#ws) **x** [oscBrowser](./webBrowser)

- WebBrowser x WebBrowser
  
  - [oscBrowser](./webBrowser) **x** [wusProxy/ws2ws](./wusProxy#ws2ws) **x** [oscBrowser](./webBrowser)
