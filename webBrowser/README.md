# Easy OSC

## Web Browser

Drop index.html from oscBrowser forlder into your webBrowser. It use [osc.js](https://github.com/colinbdclark/osc.js) library, you can find it into library folder.

#### Initialization

Setup *IP* *<u>Default</u> : 127.0.0.1*

Setup *PORT* for communication IN & OUT *<u>Default</u> : 6969*

Click *Connect*

#### Send :

You just have to setup html for sending data 

```html
<input type=ANY name=OSC.ADDRESS/>
```

```html
<li>
    <label for="title">Title : </label>
    <input id="title" type="text" name="/title"/>
</li>
<li>
    <label for="cube_x">Cube X : </label>
    <input id="cube_x" type="range" min="-5" max="5" step="0.1" name="/cube/x"/>
    <span></span><!-- if present, this span will automatically display the value of the input -->
</li>
```

#### Recieve :

Just implement this script into a new javascript file.

this is already present into scripts/sketch.js

```javascript
docReady(function(){
    oscPort.on("message", onMessage);    
});

function onMessage(oscMsg) {
    console.log("An OSC message just arrived!", oscMsg);
}
```
