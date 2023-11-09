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
  
  - [Arduino](./arduino) **x** [Arduino](./arduino)

- Arduino x Processing
  
  - [Arduino](./arduino) **x** [wusProxy/serial2udp](./wusProxy#serial2udp) **x** [oscUDP](./processing#oscudp)

- Arduino x Unity(udp)
  
  - [Arduino](./arduino) **x** [wusProxy/serial2udp](./wusProxy#serial2udp) **x** [oscUnity](./unity#udp)

- Arduino x WebBrowser
  
  - [Arduino](./arduino) **x** [wusProxy/serial2ws](./wusProxy#serial2ws) **x** [oscBrowser](./webBrowser)

- Processing(udp) x Processing(udp)
  
  - [oscUDP](./processing#oscudp) **x** [oscUDP](./processing#oscudp)

- Processing(udp) x Unity(udp)
  
  - [oscUDP](./processing#oscudp) **x** [oscUnity](./unity#udp)

- Processing(ws) x WebBrowser(ws)
  
  - [oscWS](./processing#oscws) **x** [oscBrowser](./webBrowser)

- Unity(udp) x Unity(udp)
  
  - [oscUnity](./unity#udp) **x** [oscUnity](./unity#udp)

- Unity(ws) x WebBrowser(ws)
  
  - [oscUnity](./unity#ws) **x** [oscBrowser](./webBrowser)

- WebBrowser(ws) x WebBrowser(ws)
  
  - [oscBrowser](./webBrowser) **x** [wusProxy/ws2ws](./wusProxy#ws2ws) **x** [oscBrowser](./webBrowser)
